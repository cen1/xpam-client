#ifndef LOGGER_H
#define LOGGER_H

#endif // LOGGER_H

#include <QTextStream>

namespace Logger
{
    inline void log(QString line, Config * config) {

        QFile log(config->EUROPATH+"\\xpam.log");
        log.open(QFile::WriteOnly | QFile::Append | QFile::Text);
        if (log.isOpen()) {
            QTextStream out(&log);
            out << line << "\n";
            log.close();
        }
    }
}
