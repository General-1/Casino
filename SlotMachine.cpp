#include <iostream>
#include <random>
#include <vector>
#include <string>
using namespace std;

// Function prototypes
void displaySlots(int slot1, int slot2, int slot3, const vector<string>& symbols);
double calculateWinnings(double money, int slot1, int slot2, int slot3);
void monteCarloSimulation(int numSimulations, double betAmount, const vector<string>& symbols);

int main() {
    mt19937 rng(random_device{}()); // Mersenne Twister RNG
    uniform_int_distribution<int> dist(0, 5); // For slot machine symbols (0 to 5)

    vector<string> symbols = {"Cherries", "Oranges", "Plums", "Bells", "Melons", "Bars"};
    double money, totalWinnings = 0, totalInserted = 0;
    string playAgain;

    cout << "Welcome to the Slot Machine Game!\n";

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

    // Monte Carlo Simulation
    int numSimulations;
    double betAmount;

    cout << "\n--- Monte Carlo Simulation ---\n";
    cout << "Enter the number of simulated games: ";
    cin >> numSimulations;

    cout << "Enter the bet amount for each game: $";
    cin >> betAmount;

    if (numSimulations > 0 && betAmount > 0) {
        monteCarloSimulation(numSimulations, betAmount, symbols);
    } else {
        cout << "Invalid simulation parameters. Exiting.\n";
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

// Function to run a Monte Carlo simulation for slot games
void monteCarloSimulation(int numSimulations, double betAmount, const vector<string>& symbols) {
    mt19937 rng(random_device{}());
    uniform_int_distribution<int> dist(0, 5);

    double totalWinnings = 0;
    int wins = 0, losses = 0;
    double maxWin = 0, minWin = betAmount;

    for (int i = 0; i < numSimulations; ++i) {
        // Generate random slots
        int slot1 = dist(rng);
        int slot2 = dist(rng);
        int slot3 = dist(rng);

        // Calculate winnings for this simulation
        double winnings = calculateWinnings(betAmount, slot1, slot2, slot3);
        totalWinnings += winnings;

        if (winnings > 0) {
            wins++;
            if (winnings > maxWin) maxWin = winnings;
        } else {
            losses++;
        }

        if (winnings < minWin) minWin = winnings;
    }

    // Display simulation results
    cout << "\nMonte Carlo Simulation Results:\n";
    cout << "Total games simulated: " << numSimulations << "\n";
    cout << "Total winnings: $" << totalWinnings << "\n";
    cout << "Average winnings per game: $" << totalWinnings / numSimulations << "\n";
    cout << "Number of wins: " << wins << " (" << (static_cast<double>(wins) / numSimulations) * 100 << "%)\n";
    cout << "Number of losses: " << losses << " (" << (static_cast<double>(losses) / numSimulations) * 100 << "%)\n";
    cout << "Maximum win in a single game: $" << maxWin << "\n";
    cout << "Minimum win in a single game: $" << minWin << "\n";
}
