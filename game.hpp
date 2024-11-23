#ifndef GAME_H
#define GAME_H

#include "deck.hpp"
#include "player.hpp"
#include "house.hpp"
#include <vector>

class Game {
public:
    Game(const std::vector<std::string>& names);
    ~Game();

    void Play();

private:
    Deck m_Deck;
    House m_House;
    std::vector<Player> m_Players;
};

#endif
