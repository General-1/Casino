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

    if (playerHand.GetTotal() > 21) return -1; // Player busts

    while (dealerHand.GetTotal() < 17) {
        deck.Deal(dealerHand);
    }

    if (dealerHand.GetTotal() > 21) return 1; // Dealer busts

    if (playerHand.GetTotal() > dealerHand.GetTotal()) return 1;  // Player wins
    if (playerHand.GetTotal() < dealerHand.GetTotal()) return -1; // Dealer wins
    return 0; // Tie
}

void MonteCarloSimulation(int numGames) {
    int wins = 0, losses = 0, ties = 0;
    double totalWinnings = 0.0;
    double baseBet = 10.0;  // Starting bet
    double currentBet = baseBet;

    for (int i = 0; i < numGames; ++i) {
        int result = SimulateBlackjackGame();

        if (result == 1) { 
            ++wins;
            totalWinnings += currentBet; 
            currentBet = baseBet; // Reset bet after a win
        } 
        else if (result == -1) { 
            ++losses;
            totalWinnings -= currentBet; 
            currentBet *= 2; // Double the bet after a loss
        } 
        else { 
            ++ties;
            // Bet remains the same on a tie
        }

        // If the player runs out of money, reset the bet
        if (totalWinnings < -1000) {  // You can change this threshold as needed
            currentBet = baseBet;
        }
    }

    std::cout << "Monte Carlo Simulation Results:\n";
    std::cout << "Games Played: " << numGames << "\n";
    std::cout << "Wins: " << wins << "\n";
    std::cout << "Losses: " << losses << "\n";
    std::cout << "Ties: " << ties << "\n";
    std::cout << "Final Winnings: $" << totalWinnings << "\n";
    std::cout << "Win Rate: " << (static_cast<double>(wins) / numGames) * 100 << "%\n";
    std::cout << "Loss Rate: " << (static_cast<double>(losses) / numGames) * 100 << "%\n";
    std::cout << "Tie Rate: " << (static_cast<double>(ties) / numGames) * 100 << "%\n";
}

int main() {
    int numGames = 10000;
    MonteCarloSimulation(numGames);
    return 0;
}
