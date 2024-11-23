#ifndef PLAYER_H
#define PLAYER_H

#include "genericPlayerClass.hpp"

class Player : public GenericPlayer {
public:
    Player(const std::string& name);

    virtual bool IsHitting() const override;

    void Win() const;

    void Lose() const;

    void Push() const;

    friend std::ostream& operator<<(std::ostream& os, const Player& aPlayer);
};

#endif
