#ifndef TORRENTDOWNLOADER_H
#define TORRENTDOWNLOADER_H

#include <QObject>
#include <QString>
#include <QTimer>
#include <libtorrent/session.hpp>

class TorrentDownloader : public QObject
{
    Q_OBJECT

public:
    TorrentDownloader(const QString& magnetLink, const QString& downloadDir);

public slots:
    void download();
    void cancelDownload();

signals:
    void progress(int percent);
    void working();
    void finished(int code);
    void internalFinish();
    void sendLine(QString line);

private:
    lt::session session;
    bool exitBool=false;
    const QString magnetLink;
    const QString downloadDir;
    QTimer *timer;

private slots:
    void processLibtorrentEvents();

};

#endif // TORRENTDOWNLOADER_H
