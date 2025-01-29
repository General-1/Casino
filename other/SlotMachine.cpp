#include <iostream>
#include <random>
#include <vector>
#include <string>
using namespace std;

// Function prototypes
void displaySlots(int slot1, int slot2, int slot3, const vector<string>& symbols);
double calculateWinnings(double money, int slot1, int slot2, int slot3);
void monteCarloMartingale(int numSimulations, double initialBet, double balance, const vector<string>& symbols);

int main() {
    vector<string> symbols = {"Cherries", "Oranges", "Plums", "Bells", "Melons", "Bars"};
    string choice;
    
    cout << "Welcome to the Slot Machine Game!\n";
    cout << "Choose mode: (manual / montecarlo): ";
    cin >> choice;
    
    if (choice == "manual") {
        mt19937 rng(random_device{}());
        uniform_int_distribution<int> dist(0, 5);
        double money, totalWinnings = 0, totalInserted = 0;
        string playAgain;

        do {
            cout << "\nEnter the amount of money you'd like to insert: $";
            cin >> money;

            if (money <= 0) {
                cout << "Invalid amount. Please enter a positive value.\n";
                continue;
            }

            totalInserted += money;

            // Generate slot values
            int slot1 = dist(rng);
            int slot2 = dist(rng);
            int slot3 = dist(rng);

            // Display slot results
            displaySlots(slot1, slot2, slot3, symbols);

            // Calculate winnings
            double winnings = calculateWinnings(money, slot1, slot2, slot3);
            totalWinnings += winnings;

            cout << "You " << (winnings > 0 ? "won" : "lost") << " $" << winnings << " in this round.\n";

            // Prompt for replay
            cout << "Would you like to play again? (yes/no): ";
            cin >> playAgain;

        } while (playAgain == "yes");

        // Display summary
        cout << "\nGame Over!\n";
        cout << "Total money inserted: $" << totalInserted << "\n";
        cout << "Total money won: $" << totalWinnings << "\n";
        cout << (totalWinnings >= totalInserted ? "Congratulations, you made a profit!" : "Better luck next time!") << endl;
    } 
    else if (choice == "montecarlo") {
        int numSimulations;
        double initialBet, balance;
        
        cout << "\n--- Monte Carlo Simulation with Martingale ---\n";
        cout << "Enter the number of simulated games: ";
        cin >> numSimulations;
        cout << "Enter the initial bet amount: $";
        cin >> initialBet;
        cout << "Enter starting balance: $";
        cin >> balance;

        if (numSimulations > 0 && initialBet > 0 && balance > 0) {
            monteCarloMartingale(numSimulations, initialBet, balance, symbols);
        } else {
            cout << "Invalid simulation parameters. Exiting.\n";
        }
    }
    else {
        cout << "Invalid option. Exiting.\n";
    }

    return 0;
}

// Function to display the slot results
void displaySlots(int slot1, int slot2, int slot3, const vector<string>& symbols) {
    cout << "\nThe slot machine shows:\n";
    cout << symbols[slot1] << " | " << symbols[slot2] << " | " << symbols[slot3] << "\n";
}

// Function to calculate winnings based on slot results
double calculateWinnings(double money, int slot1, int slot2, int slot3) {
    if (slot1 == slot2 && slot2 == slot3) {
        return money * 3; // All three match
    } else if (slot1 == slot2 || slot1 == slot3 || slot2 == slot3) {
        return money * 2; // Any two match
    }
    return 0; // No match
}

// Function to run a Monte Carlo simulation using the Martingale betting system
void monteCarloMartingale(int numSimulations, double initialBet, double balance, const vector<string>& symbols) {
    mt19937 rng(random_device{}());
    uniform_int_distribution<int> dist(0, 5);
    
    int wins = 0, losses = 0;
    double totalWinnings = 0;
    double maxBet = initialBet;
    
    for (int i = 0; i < numSimulations; ++i) {
        double bet = initialBet;
        double sessionBalance = balance;
        
        while (sessionBalance >= bet) {
            // Generate random slots
            int slot1 = dist(rng);
            int slot2 = dist(rng);
            int slot3 = dist(rng);
            
            // Calculate winnings
            double winnings = calculateWinnings(bet, slot1, slot2, slot3);
            
            if (winnings > 0) {
                sessionBalance += winnings - bet;
                wins++;
                bet = initialBet; // Reset bet after a win
            } else {
                sessionBalance -= bet;
                losses++;
                bet *= 2; // Double the bet after a loss (Martingale)
            }
            
            if (bet > maxBet) maxBet = bet; // Track max bet used
            if (sessionBalance < bet) break; // Stop if balance is insufficient
        }
        totalWinnings += (sessionBalance - balance);
    }

    // Display simulation results
    cout << "\nMonte Carlo Martingale Results:\n";
    cout << "Total games simulated: " << numSimulations << "\n";
    cout << "Total profit/loss: $" << totalWinnings << "\n";
    cout << "Average profit/loss per session: $" << totalWinnings / numSimulations << "\n";
    cout << "Total wins: " << wins << "\n";
    cout << "Total losses: " << losses << "\n";
    cout << "Max bet placed: $" << maxBet << "\n";
}
