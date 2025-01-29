#include "game.hpp"
#include <iostream>
#include <vector>
#include "game.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

void runMonteCarloSimulation();

int main() {
    std::cout << "Welcome to Blackjack!" << std::endl;

    int choice = 0;
    do {
        std::cout << "Choose an option:\n";
        std::cout << "1. Play a game of Blackjack\n";
        std::cout << "2. Run Monte Carlo simulation\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (choice == 1) {
            std::vector<std::string> playerNames;
            int numPlayers;

            std::cout << "Enter the number of players (1-4): ";
            std::cin >> numPlayers;
            for (int i = 0; i < numPlayers; ++i) {
                std::string playerName;
                std::cout << "Enter name for player " << (i + 1) << ": ";
                std::cin >> playerName;
                playerNames.push_back(playerName);
            }

            Game blackjackGame(playerNames);
            blackjackGame.Play();
        } 
        else if (choice == 2) {
            // Run Monte Carlo simulation
            runMonteCarloSimulation();
        } 
        else if (choice == 3) {
            std::cout << "Thank you for playing! Goodbye.\n";
        } 
        else {
            std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 3);

    return 0;
}
