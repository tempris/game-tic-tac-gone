#ifndef PLAYER_H
#define PLAYER_H

#include "Shared.h"

class Player {
public:
    Player(PlayerType type) : type(type) {}

    PlayerType getType() const {
        return type;
    }

private:
    PlayerType type;
};

#endif // PLAYER_H
