#ifndef IPLAYER_H
#define IPLAYER_H

#include "Shared.h"

class IPlayer {
public:
    virtual ~IPlayer() = default;
    virtual PlayerType getType() const = 0;
};

#endif // IPLAYER_H
