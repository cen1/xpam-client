#ifndef PATCHER_H
#define PATCHER_H

#include "QString"
#include "config.h"

class Patcher {

public:
    static bool patch(Config * config);
    static QString getCurrentW3Version(Config * config);
    static void cleanMetadata(Config * config);
};

#endif // PATCHER_H


