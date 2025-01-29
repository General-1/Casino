#include <iostream>
#include <string>
#include <iomanip>
#include <random>

using namespace std;

const int MIN_NUMBER = 1, MAX_NUMBER = 36;

// Function to simulate Monte Carlo games
double simulateMonteCarlo(int numSimulations, int startingMoney);
void playRoulette();

int main() {
    char mode;
    cout << "Welcome to ROULETTE\n\n";
    cout << "Would you like to play manually (M) or run a Monte Carlo simulation (S)? ";
    cin >> mode;

    if (mode == 'M' || mode == 'm') {
        playRoulette();
    } else if (mode == 'S' || mode == 's') {
        int numSimulations;
        int startingMoney;
        cout << "Enter the number of simulations: ";
        cin >> numSimulations;
        cout << "Enter the starting money: ";
        cin >> startingMoney;
        double averageWinnings = simulateMonteCarlo(numSimulations, startingMoney);
        cout << "\nMonte Carlo Simulation over " << numSimulations << " games:\n";
        cout << "Average winnings: $" << fixed << setprecision(2) << averageWinnings << endl;
    } else {
        cout << "Invalid choice!" << endl;
    }
    return 0;
}

void playRoulette() {
    int number, random, my_money, starting_money;
    double bet, winnings = 0;
    char gametype, evenodd, blackred, stop = 'N';

    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> rouletteDist(MIN_NUMBER, MAX_NUMBER);

    cout << "With how much money do you want to start?\n";
    cin >> starting_money;
    my_money = starting_money;

    while (my_money > 0 && stop != 'Y' && stop != 'y') {
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
        random = rouletteDist(mt);

        if (gametype == 'N' || gametype == 'n') {
            cout << "What number would you like to bet on? ";
            cin >> number;
            cout << "The ball landed on " << random << "\n";
            if (number == random) {
                cout << "You win $" << 35 * bet << endl;
                winnings += 35 * bet;
            } else {
                cout << "You lose $" << bet << "\n";
                winnings -= bet;
            }
        }
        else if (gametype == 'O' || gametype == 'o') {
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
        else if (gametype == 'B' || gametype == 'b') {
            cout << "Would you like to bet on black (B) or red (R)? ";
            cin >> blackred;
            bool isBlack = (random % 2 == 0);
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
    cout << "You won a total of $" << my_money - starting_money << "\nAnd you currently have a total of $" << my_money << endl;
}

double simulateMonteCarlo(int numSimulations, int startingMoney) {
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> rouletteDist(MIN_NUMBER, MAX_NUMBER);
    uniform_int_distribution<int> betDist(1, startingMoney / 10);
    uniform_int_distribution<int> gameTypeDist(1, 3);

    double totalWinnings = 0;
    for (int i = 0; i < numSimulations; ++i) {
        int money = startingMoney;
        double winnings = 0;
        double bet = betDist(mt);
        int randomOutcome = rouletteDist(mt);

        switch (gameTypeDist(mt)) {
            case 1: {
                int number = rouletteDist(mt);
                if (number == randomOutcome) winnings += 35 * bet;
                else winnings -= bet;
                break;
            }
            case 2: {
                bool isEven = randomOutcome % 2 == 0;
                if (isEven) winnings += bet;
                else winnings -= bet;
                break;
            }
            case 3: {
                bool isBlack = (randomOutcome % 2 == 0);
                if (isBlack) winnings += bet;
                else winnings -= bet;
                break;
            }
        }
        totalWinnings += winnings;
    }
    return totalWinnings / numSimulations;
}
