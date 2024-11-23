#include <iostream>
#include <string>
#include <iomanip>
#include <random>

using namespace std;

// Constants
const int MIN_NUMBER = 1, MAX_NUMBER = 36;

// Function to simulate Monte Carlo games
double simulateMonteCarlo(int numSimulations, int startingMoney);

int main() {
    int number;
    int random;
    int my_money;
    int starting_money;

    double bet, winnings = 0;

    char gametype;
    char evenodd;
    char blackred;
    char stop = 'N';

    // Random number generator using Mersenne Twister
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> rouletteDist(MIN_NUMBER, MAX_NUMBER);

    cout << "Welcome to ROULETTE\n\n";
    cout << "With how much money do you want to start?\n";
    cin >> starting_money;
    my_money = starting_money;

    while (my_money > 0 && stop != 'Y') {
        my_money += winnings;
        winnings = 0;

        cout << "How much would you like to bet?\n";
        cin >> bet;

        while (bet > my_money) {
            cout << "Insufficient funds! How much would you like to bet?\n";
            cin >> bet;
        }

        cout << "Would you like to bet on a specific number (N), on odd/even (O), or on Black/Red (B)? ";
        cin >> gametype;

        random = rouletteDist(mt); // Generate a random roulette outcome

        if (gametype == 'n' || gametype == 'N') {
            cout << "What number would you like to bet on? ";
            cin >> number;

            if (number == random) {
                cout << "The ball landed on " << random << "\n";
                cout << "You win $" << 35 * bet << endl;
                winnings += 35 * bet;
            } else {
                cout << "The ball landed on " << random << "\n";
                cout << "You lose $" << bet << "\n";
                winnings -= bet;
            }
        }

        if (gametype == 'o' || gametype == 'O') {
            cout << "Would you like to bet on even (E) or odd (O)? ";
            cin >> evenodd;

            cout << "The ball landed on " << random << endl;

            if ((evenodd == 'E' && random % 2 == 0) || (evenodd == 'O' && random % 2 != 0)) {
                cout << "You win $" << bet << endl;
                winnings += bet;
            } else {
                cout << "You lose $" << bet << endl;
                winnings -= bet;
            }
        }

        if (gametype == 'B' || gametype == 'b') {
            cout << "Would you like to bet on black (B) or red (R)? ";
            cin >> blackred;

            // Black numbers on the roulette table
            bool isBlack = random == 2 || random == 4 || random == 6 || random == 8 || random == 10 ||
                           random == 11 || random == 13 || random == 15 || random == 17 || random == 20 ||
                           random == 22 || random == 24 || random == 26 || random == 28 || random == 29 ||
                           random == 31 || random == 33 || random == 35;

            cout << "The ball landed on " << random << endl;

            if ((blackred == 'B' || blackred == 'b') && isBlack || 
                (blackred == 'R' || blackred == 'r') && !isBlack) {
                cout << "You win $" << bet << endl;
                winnings += bet;
            } else {
                cout << "You lose $" << bet << endl;
                winnings -= bet;
            }
        }

        cout << "Do you want to stop, yes (Y) or no (N)? ";
        cin >> stop;
    }

    my_money += winnings;
    cout << "You won a total of $" << my_money - starting_money
         << "\nAnd you currently have a total of $" << my_money << endl;

    // Monte Carlo Simulation
    int numSimulations = 1000;
    double averageWinnings = simulateMonteCarlo(numSimulations, starting_money);
    cout << "\nMonte Carlo Simulation over " << numSimulations << " games:\n";
    cout << "Average winnings: $" << fixed << setprecision(2) << averageWinnings << endl;

    return 0;
}

// Monte Carlo simulation function
double simulateMonteCarlo(int numSimulations, int startingMoney) {
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> rouletteDist(MIN_NUMBER, MAX_NUMBER);
    uniform_int_distribution<int> betDist(1, startingMoney / 10); // Random bets
    uniform_int_distribution<int> gameTypeDist(1, 3); // 1 = Number, 2 = Even/Odd, 3 = Black/Red

    double totalWinnings = 0;

    for (int i = 0; i < numSimulations; ++i) {
        int money = startingMoney;
        double winnings = 0;
        double bet = betDist(mt);
        int randomOutcome = rouletteDist(mt);

        switch (gameTypeDist(mt)) {
            case 1: { // Specific number
                int number = rouletteDist(mt);
                if (number == randomOutcome) winnings += 35 * bet;
                else winnings -= bet;
                break;
            }
            case 2: { // Even/Odd
                bool isEven = randomOutcome % 2 == 0;
                if (isEven) winnings += bet;
                else winnings -= bet;
                break;
            }
            case 3: { // Black/Red
                bool isBlack = randomOutcome == 2 || randomOutcome == 4 || randomOutcome == 6 || randomOutcome == 8 ||
                               randomOutcome == 10 || randomOutcome == 11 || randomOutcome == 13 || randomOutcome == 15 ||
                               randomOutcome == 17 || randomOutcome == 20 || randomOutcome == 22 || randomOutcome == 24 ||
                               randomOutcome == 26 || randomOutcome == 28 || randomOutcome == 29 || randomOutcome == 31 ||
                               randomOutcome == 33 || randomOutcome == 35;
                if (isBlack) winnings += bet;
                else winnings -= bet;
                break;
            }
        }

        totalWinnings += winnings;
    }

    return totalWinnings / numSimulations; // Average winnings
}
