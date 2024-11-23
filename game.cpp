#include "game.hpp"
#include "deck.hpp"
#include "player.hpp"
#include "house.hpp"
#include <iostream>

Game::Game(const std::vector<std::string>& names) {
    for (auto& name : names) {
        m_Players.push_back(Player(name));
    }
}

Game::~Game() {}

void Game::Play() {
    m_Deck.Populate();
    m_Deck.Shuffle();

    // Deal cards to players and house
    for (auto& player : m_Players) {
        m_Deck.Deal(player);
        m_Deck.Deal(player);
    }
    m_Deck.Deal(m_House);
    m_Deck.Deal(m_House);

    // Reveal the house's first card
    m_House.FlipFirstCard();

    // Players' turns
    for (auto& player : m_Players) {
        m_Deck.AdditionalCards(player);
        if (player.IsBusted()) {
            player.Lose();
        } else {
            std::cout << player << std::endl;
        }
    }

    // House's turn
    m_House.FlipFirstCard();
    m_Deck.AdditionalCards(m_House);
    if (m_House.IsBusted()) {
        std::cout << m_House << std::endl;
        for (auto& player : m_Players) {
            player.Win();
        }
    } else {
        std::cout << m_House << std::endl;
        for (auto& player : m_Players) {
            if (player.GetTotal() > m_House.GetTotal()) {
                player.Win();
            } else if (player.GetTotal() < m_House.GetTotal()) {
                player.Lose();
            } else {
                player.Push();
            }
        }
    }
}
