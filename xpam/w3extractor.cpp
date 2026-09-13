#ifndef QUAZIP_STATIC
    #define QUAZIP_STATIC
#endif

#include "w3extractor.h"
#include "quazip.h"
#include "quazipfile.h"
#include "QDir"
#include "QFile"
#include "QFileInfo"

W3Extractor::W3Extractor(const QString& zipPath, const QString& targetDir) : zipPath(zipPath), targetDir(targetDir)
{
}

void W3Extractor::extract()
{
    QString error = doExtract();
    emit finished(error.isEmpty(), error);
}

// Returns an empty string on success, otherwise the error message
QString W3Extractor::doExtract()
{
    QuaZip zip(zipPath);
    if (!zip.open(QuaZip::mdUnzip)) {
        return "Could not open "+zipPath+" (zip error "+QString::number(zip.getZipError())+")";
    }

    const QList<QuaZipFileInfo64> entries = zip.getFileInfoList64();
    if (entries.isEmpty()) {
        return "Archive "+zipPath+" is empty";
    }

    // Strip the root folder only if every entry lives under the same one
    QString root = QString(entries.first().name).replace('\\', '/').section('/', 0, 0);
    qint64 totalBytes = 0;
    for (const QuaZipFileInfo64 &e : entries) {
        const QString name = QString(e.name).replace('\\', '/');
        if (!root.isEmpty() && (!name.contains('/') || name.section('/', 0, 0) != root)) {
            root.clear();
        }
        totalBytes += e.uncompressedSize;
    }
    if (!root.isEmpty()) {
        emit sendLine("Stripping archive root folder: "+root);
    }

    QDir target(targetDir);
    if (!target.mkpath(".")) {
        return "Could not create "+targetDir;
    }

    QByteArray buffer(1024*1024, Qt::Uninitialized);
    qint64 doneBytes = 0;
    int lastPercent = -1;

    for (bool more = zip.goToFirstFile(); more; more = zip.goToNextFile()) {
        QString name = zip.getCurrentFileName().replace('\\', '/');
        if (!root.isEmpty()) {
            name = name.mid(root.length()+1);
        }
        if (name.isEmpty()) continue; // the root folder entry itself

        const bool isDir = name.endsWith('/');
        const QString rel = QDir::cleanPath(name);
        if (QDir::isAbsolutePath(rel) || rel == ".." || rel.startsWith("../") || rel.contains(':')) {
            return "Refusing to extract unsafe path "+name;
        }
        const QString dstPath = target.filePath(rel);

        if (isDir) {
            if (!QDir().mkpath(dstPath)) return "Could not create "+dstPath;
            continue;
        }
        if (!QDir().mkpath(QFileInfo(dstPath).absolutePath())) {
            return "Could not create "+QFileInfo(dstPath).absolutePath();
        }

        QuaZipFile src(&zip);
        if (!src.open(QIODevice::ReadOnly)) {
            return "Could not read "+name+" from archive (zip error "+QString::number(src.getZipError())+")";
        }
        QFile dst(dstPath);
        if (!dst.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
            return "Could not write "+dstPath+": "+dst.errorString();
        }

        emit sendLine("Extracting "+rel);

        qint64 n;
        while ((n = src.read(buffer.data(), buffer.size())) > 0) {
            if (dst.write(buffer.constData(), n) != n) {
                return "Could not write "+dstPath+": "+dst.errorString();
            }
            doneBytes += n;
            int percent = totalBytes > 0 ? int(doneBytes*100/totalBytes) : 0;
            if (percent != lastPercent) {
                lastPercent = percent;
                emit progress(percent);
            }
        }
        if (n < 0) {
            return "Failed reading "+name+" from archive";
        }

        dst.close();
        src.close(); // verifies CRC
        if (src.getZipError() != UNZ_OK) {
            return "Corrupted archive entry "+name+" (zip error "+QString::number(src.getZipError())+")";
        }
    }

    zip.close();
    return QString();
}
