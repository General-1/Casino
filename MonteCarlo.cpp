#include <iostream>
#include <vector>
#include <random>
#include "game.hpp"
#include "deck.hpp"
#include "player.hpp"
#include "house.hpp"
#include "hand.hpp"

int SimulateBlackjackGame() {
    Deck deck;
    deck.Populate();
    deck.Shuffle();

    Hand playerHand;
    Hand dealerHand;

    deck.Deal(playerHand);
    deck.Deal(dealerHand);
    deck.Deal(playerHand);
    deck.Deal(dealerHand);

    while (playerHand.GetTotal() < 17) {
        deck.Deal(playerHand);
    }

    if (playerHand.GetTotal() > 21) return -1;

    while (dealerHand.GetTotal() < 17) {
        deck.Deal(dealerHand);
    }

    if (dealerHand.GetTotal() > 21) return 1;

    if (playerHand.GetTotal() > dealerHand.GetTotal()) return 1;
    if (playerHand.GetTotal() < dealerHand.GetTotal()) return -1;
    return 0;
}

void MonteCarloSimulation(int numGames) {
    int wins = 0, losses = 0, ties = 0;

    for (int i = 0; i < numGames; ++i) {
        int result = SimulateBlackjackGame();
        if (result == 1) ++wins;
        else if (result == -1) ++losses;
        else ++ties;
    }

    std::cout << "Monte Carlo Simulation Results:\n";
    std::cout << "Games Played: " << numGames << "\n";
    std::cout << "Wins: " << wins << "\n";
    std::cout << "Losses: " << losses << "\n";
    std::cout << "Ties: " << ties << "\n";
    std::cout << "Win Rate: " << (static_cast<double>(wins) / numGames) * 100 << "%\n";
    std::cout << "Loss Rate: " << (static_cast<double>(losses) / numGames) * 100 << "%\n";
    std::cout << "Tie Rate: " << (static_cast<double>(ties) / numGames) * 100 << "%\n";
}

int main() {
    int numGames = 10000;
    MonteCarloSimulation(numGames);
    return 0;
}
