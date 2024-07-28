#ifndef PLAYER_H
#define PLAYER_H

#include "IPlayer.h"

class Player : public IPlayer {
public:
    Player(PlayerType type) : type(type) {}

    PlayerType getType() const override {
        return type;
    }

private:
    PlayerType type;
};

#endif // PLAYER_H
