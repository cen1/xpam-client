#ifndef W3EXTRACTOR_H
#define W3EXTRACTOR_H

#include <QObject>
#include <QString>

// Extracts a downloaded W3 archive into a target directory. The archives wrap
// everything in a single root folder (named differently per version), which is
// stripped so the game files land directly in the target.
class W3Extractor : public QObject
{
    Q_OBJECT

public:
    W3Extractor(const QString& zipPath, const QString& targetDir);

public slots:
    void extract();

signals:
    void progress(int percent);
    void sendLine(QString line);
    void finished(bool ok, QString error);

private:
    const QString zipPath;
    const QString targetDir;

    QString doExtract();
};

#endif // W3EXTRACTOR_H
