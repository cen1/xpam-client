#include "torrentdownloader.h"
#include <libtorrent/session.hpp>
#include <libtorrent/session_params.hpp>
#include <libtorrent/add_torrent_params.hpp>
#include <libtorrent/torrent_handle.hpp>
#include <libtorrent/alert_types.hpp>
#include <libtorrent/magnet_uri.hpp>
#include "QDebug"
#include "QThread"
#include "QTimer"

TorrentDownloader::TorrentDownloader(const QString& magnetLink, const QString& downloadDir) : magnetLink(magnetLink), downloadDir(downloadDir)
{
    lt::settings_pack settings;
    settings.set_int(lt::settings_pack::alert_mask,
                        lt::alert_category::error
                        | lt::alert_category::storage
                        | lt::alert_category::file_progress
                        | lt::alert_category::status);

    session.apply_settings(settings);
}

void TorrentDownloader::cancelDownload() {
    emit sendLine("tdl cancelled by user");
    timer->stop();
    session.pause();
    int tries = 0;
    while (!session.is_paused()) {
        QThread::sleep(1);
        tries++;
        if (tries > 10) {
            session.abort();
            break;
        }
    }
    emit finished(2);
}

void TorrentDownloader::download()
{
    emit sendLine("Starting tdl download");
    lt::add_torrent_params params = lt::parse_magnet_uri(magnetLink.toStdString());
    params.save_path = downloadDir.toStdString();

    boost::system::error_code ec;
    lt::torrent_handle handle = session.add_torrent(params, ec);

    timer = new QTimer(this);
    timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(processLibtorrentEvents()));
    timer->start();
}

void TorrentDownloader::processLibtorrentEvents() {
    std::vector<lt::alert*> alerts;
    session.pop_alerts(&alerts);

    for (lt::alert const* a : alerts) {
        //qDebug() << QString::fromStdString(a->message());

        if (lt::alert_cast<lt::torrent_finished_alert>(a)) {
            //qDebug() << "TORRENT FINISHED";
            emit sendLine("tdl finished");
            exitBool=true;
            emit finished(0);
        }

        if (auto st = lt::alert_cast<lt::state_update_alert>(a)) {
            if (st->status.empty()) continue;

            lt::torrent_status const& s = st->status[0];
            if (s.state == lt::torrent_status::downloading) {
                int percent = s.progress_ppm / 10000;
                emit progress(percent);
            }
        }

        if (lt::alert_cast<lt::torrent_error_alert>(a)) {
            emit sendLine("tdl error");
            exitBool=true;
            emit finished(1);
        }

    }
    emit working(exitBool);
    session.post_torrent_updates();
    //qDebug() << "processLibtorrentEvents";
}
