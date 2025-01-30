#include <iostream>
#include <string>
#include <limits>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <random>
#include <algorithm>

#define RESET "\033[0m"
#define RED  "\033[31m"

int cash = 100;
int betType = 0, insideBetType = 0, outsideBetType = 0;
int choice = 0, num = 0, deposit = 0;

const int rows[] = { 1, 4, 7, 10, 13, 16, 19, 22, 25, 28, 31, 34 };
std::vector<int> reds = { 1, 3, 5, 7, 9, 12, 14, 16, 18, 19, 21, 23, 25, 27, 30, 32, 34, 36 };

std::string insideBets[] = {
    "Straight Up: Bet on a single number.",
    "Split: Bet on two adjacent numbers.",
    "Street: Bet on three numbers in a row.",
    "Corner: Bet on four numbers forming a square.",
    "Six Line: Bet on six numbers in two adjacent rows."
};

std::string outsideBets[] = {
    "Red or Black: Bet on the color of the number.",
    "Odd or Even: Bet on whether the number is odd or even.",
    "High or Low: Bet on whether the number is between 1-18 or 19-36.",
    "Dozens: Bet on one of the three groups of 12 numbers.",
    "Columns: Bet on one of the three columns."
};
void displayMenu0();
void displayMenu();
void placeBet();
void loadMoney();
void randomNum();
void win(int rate);
void lost();
void straightUp();
void split();
void street();
void corner();
void sixLine();
void redOrBlack();
void oddOrEven();
void highOrLow();
void dozens();
void columns();

// Define global variables for random number generation
std::mt19937 gen(static_cast<unsigned int>(time(0)));  // Mersenne Twister random number generator

void runManualOrSimulation();

void monteCarloSimulation() {
    int totalSimulations = 1000; // Number of simulations to run
    int simulationCash = 100;    // Starting cash for each simulation
    int totalWins = 0, totalLosses = 0;

    std::uniform_int_distribution<int> distChoice(0, 36);  // Random number for roulette (0-36)
    std::uniform_int_distribution<int> distBetAmount(1, 10);  // Random bet amount (1-10)
    std::uniform_int_distribution<int> distBetType(1, 2);  // Random bet type (1 for inside, 2 for outside)
    std::uniform_int_distribution<int> distWinLoss(0, 1);  // Random win/loss (0 for loss, 1 for win)

    for (int i = 0; i < totalSimulations; ++i) {
        // Simulate a random bet type (inside or outside)
        int betType = distBetType(gen); 
        int betAmount = distBetAmount(gen);  // Random bet amount
        int choice = distChoice(gen);  // Random number for the bet (0-36)
        int num = distChoice(gen);  // Simulate roulette number spin

        bool win = distWinLoss(gen) == 0;  // Random win or loss (0 for loss, 1 for win)

        // Simulate the betting process (could be simplified or expanded based on your bet types)
        if (win) {
            simulationCash += betAmount * 2; // Win case: double the bet
            totalWins++;
        } else {
            simulationCash -= betAmount; // Loss case: subtract the bet
            totalLosses++;
        }
    }

    std::cout << "\nMonte Carlo Simulation Results:\n";
    std::cout << "Total Wins: " << totalWins << "\n";
    std::cout << "Total Losses: " << totalLosses << "\n";
    std::cout << "Final Cash: " << simulationCash << "\n";

    // Return to menu or exit after the simulation
    do {
        std::cout << "\nPress 1 to return to the menu, press 2 to exit.\nINPUT: ";
        std::cin >> choice;
    } while (choice != 1 && choice != 2);

    if (choice == 1) {
        system("clear");
        displayMenu();  // Return to the main menu
    } else {
        system("clear");
        std::cout << "Press any key to exit.";
        exit(0);  // Exit the program
    }
}

void runManualOrSimulation() {
    int choice;
    std::cout << "Choose an option:\n";
    std::cout << "1) Play manually\n";
    std::cout << "2) Run another simulation\n";
    std::cout << "3) Exit\n";
    std::cout << "INPUT: ";
    std::cin >> choice;

    switch (choice) {
        case 1:
            system("clear");
            displayMenu();  // Call the menu for manual play
            break;
        case 2:
            monteCarloSimulation();  // Run another simulation
            break;
        case 3:
            std::cout << "Exiting...\n";
            exit(0);  // Exit the program
            break;
        default:
            std::cout << "Invalid option. Try again.\n";
            runManualOrSimulation();
    }
}
void displayBetMenu() {
    int betChoice;
    
    std::cout << "Please select the type of bet you want to place:\n";
    std::cout << "1) Inside Bets\n";
    std::cout << "2) Outside Bets\n";
    std::cout << "Input: ";
    std::cin >> betChoice;

    // You can handle the bet types here
    if (betChoice == 1) {
        // Inside bet logic (you can expand this with more options if needed)
        std::cout << "You selected Inside Bets.\n";
        // More logic to handle inside bets (numbers, amount, etc.)
    } else if (betChoice == 2) {
        // Outside bet logic
        std::cout << "You selected Outside Bets.\n";
        // More logic to handle outside bets (1-18, even, odd, etc.)
    } else {
        std::cout << "Invalid input. Please select 1 or 2.\n";
        displayBetMenu();  // Recursively ask again if the input is invalid
    }

    // After choosing bet type, you can prompt for more inputs (bet amount, number, etc.)
}


int main() {
    srand(static_cast<unsigned int>(time(0)));  // Random seed for the game
    displayMenu0(); // Show the main menu with options to play manually or run simulation
    return 0;
}


void displayMenu0() {
    while (true) {
        std::cout << "\nChoose an option:\n";
        std::cout << "1) Play manually\n";
        std::cout << "2) Run Monte Carlo Simulation\n";
        std::cout << "INPUT: ";
        std::cin >> choice;

        if (choice == 1) {
            system("clear");
            // Manual game
            displayBetMenu();
        } else if (choice == 2) {
            system("clear");
            monteCarloSimulation();  // Run simulation
        } else {
            std::cout << "Invalid input. Please try again.\n";
        }
    }
}


void displayMenu() {
    while (true) {
        std::cout << '\n';
        std::cout << "  | " << RED << "3 " << RESET << "6 " << RED << "9 12 " << RESET << "15 " << RED << "18 21 " << RESET << "24 " << RED << "27 30 " << RESET << "33 " << RED << "36" << RESET << " | 2 to 1 | \n";
        std::cout << "0 | " << "2 " << RED << "5 " << RESET << "8 " << "11 " << RED << "14 " << RESET << "17 " << "20 " << RED << "23 " << RESET << "26 " << "29 " << RED << "32 " << RESET << "35" << " | 2 to 1 | \n";
        std::cout << "  | " << RED << "1 " << RESET << "4 " << RED << "7 " << RESET << "10 " << "13 " << RED << "16 19 " << RESET << "22 " << RED << "25 " << RESET << "28 " << "31 " << RED << "34" << RESET << " | 2 to 1 | \n";
        std::cout << "    -------- ----------- -----------\n";
        std::cout << "   | 1st 12 |  2nd 12   |   3rd 12   |  Red  |\n";
        std::cout << "    -------- ----------- -----------\n";
        std::cout << "   | 1 to 18 | even | odd | 19 to 36 | Black |\n";
        std::cout << "    --------- ------ ----- ---------\n";

        std::cout << "\nCASH: " << cash << '\n';
        std::cout << "\nPlease select the type of bet you want to place (1 or 2):\n 1) Inside Bets\n 2) Outside Bets\n";
        std::cout << "INPUT: ";
        std::cin >> betType;

        if (betType == 1 || betType == 2) break;
        std::cout << "Invalid input, please try again.\n";
    }

    placeBet();
}

void placeBet() {
    if (betType == 1) {
        std::cout << "\nPlease select the inside bet you want to place (1-" << sizeof(insideBets) / sizeof(insideBets[0]) << ")\n";
        for (int i = 0; i < sizeof(insideBets) / sizeof(insideBets[0]); ++i) {
            std::cout << " " << i + 1 << ") " << insideBets[i] << '\n';
        }
        std::cout << "INPUT: ";
        std::cin >> insideBetType;

        if (insideBetType < 1 || insideBetType > sizeof(insideBets) / sizeof(insideBets[0])) {
            std::cout << "Invalid input, please try again.\n";
            placeBet();
        }
    }
    else if (betType == 2) {
        std::cout << "\nPlease select the outside bet you want to place (1-" << sizeof(outsideBets) / sizeof(outsideBets[0]) << ")\n";
        for (int i = 0; i < sizeof(outsideBets) / sizeof(outsideBets[0]); ++i) {
            std::cout << " " << i + 1 << ") " << outsideBets[i] << '\n';
        }
        std::cout << "INPUT: ";
        std::cin >> outsideBetType;

        if (outsideBetType < 1 || outsideBetType > sizeof(outsideBets) / sizeof(outsideBets[0])) {
            std::cout << "Invalid input, please try again.\n";
            placeBet();
        }
    }

    switch (insideBetType) {
    case 1: straightUp(); break;
    case 2: split(); break;
    case 3: street(); break;
    case 4: corner(); break;
    case 5: sixLine(); break;
    default: break;
    }

    switch (outsideBetType) {
    case 1: redOrBlack(); break;
    case 2: oddOrEven(); break;
    case 3: highOrLow(); break;
    case 4: dozens(); break;
    case 5: columns(); break;
    default: break;
    }

    displayMenu();
}

void loadMoney() {
    while (true) {
        std::cout << "\nPlease enter the amount of money you want to bet: \n";
        std::cout << "INPUT: ";
        std::cin >> deposit;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please try again.\n";
            continue;
        }

        if (deposit > cash) {
            std::cout << "You cannot bet more than your current cash. Please try again.\n";
            continue;
        }

        if (deposit < 0) {
            std::cout << "You cannot bet a negative amount. Please try again.\n";
            continue;
        }

        break;
    }
}

void randomNum() {
    num = rand() % 37;
}

void win(int rate) {
    cash += deposit * rate;
    std::cout << "\nCONGRATULATIONS! YOU WON " << rate * deposit << " CASH! \n";

    do {
        std::cout << "Press 1 to return to the menu, press 2 to exit.\nINPUT: ";
        std::cin >> choice;
    } while (choice != 1 && choice != 2);

    if (choice == 1) {
        system("clear");
        displayMenu();
    }
    else {
        system("clear");
        std::cout << "Press any key to exit.";
        exit(0);
    }
}

void lost() {
    cash -= deposit;
    do {
        std::cout << "\nThe number was: " << num << '\n';
        std::cout << "YOU LOST\n";
        std::cout << "Press 1 to return to the menu, press 2 to exit.\nINPUT: ";
        std::cin >> choice;
    } while (choice != 1 && choice != 2);

    if (choice == 1) {
        system("clear");
        displayMenu();
    }
    else {
        system("clear");
        std::cout << "Press any key to exit.";
        exit(0);
    }
}

void straightUp() {
    std::cout << "\nPlease enter the number you want to bet on (0-36)\nINPUT: ";
    std::cin >> choice;
    loadMoney();
    randomNum();

    if (num == choice) {
        win(35);
    }
    else {
        lost();
    }
}

void split() {
    int choice2;
    std::cout << "\nPlease enter the first number you want to bet on (0-36)\nINPUT: ";
    std::cin >> choice;
    std::cout << "\nPlease enter the second number you want to bet on (0-36)\nINPUT: ";
    std::cin >> choice2;
    loadMoney();
    randomNum();

    if (num == choice || num == choice2) {
        win(17);
    }
    else {
        lost();
    }
}

void street() {
    std::cout << "\nPlease enter the row you want to bet on (1, 2, or 3)\nINPUT: ";
    std::cin >> choice;
    loadMoney();
    randomNum();

    if (num % 3 == choice % 3 && num != 0) {
        win(11);
    }
    else {
        lost();
    }
}

void corner() {
    int choice2, choice3, choice4;
    std::cout << "\nPlease enter the first number you want to bet on (0-36)\nINPUT: ";
    std::cin >> choice;
    std::cout << "\nPlease enter the second number you want to bet on (0-36)\nINPUT: ";
    std::cin >> choice2;
    std::cout << "\nPlease enter the third number you want to bet on (0-36)\nINPUT: ";
    std::cin >> choice3;
    std::cout << "\nPlease enter the fourth number you want to bet on (0-36)\nINPUT: ";
    std::cin >> choice4;
    loadMoney();
    randomNum();

    if (num == choice || num == choice2 || num == choice3 || num == choice4) {
        win(8);
    }
    else {
        lost();
    }
}

void sixLine() {
    std::cout << "\nPlease enter the first number of the first row you want to bet on (1-34)\nINPUT: ";
    std::cin >> choice;
    loadMoney();
    randomNum();

    for (int i = 0; i < 6; ++i) {
        if (num == choice + i) {
            win(5);
            return;
        }
    }

    lost();
}

void redOrBlack() {
    std::cout << "\nPlease enter your choice (1 for Red, 2 for Black)\nINPUT: ";
    std::cin >> choice;
    loadMoney();
    randomNum();

    bool isRed = false;
    for (int i = 0; i < sizeof(reds) / sizeof(reds[0]); ++i) {
        if (reds[i] == num) {
            isRed = true;
            break;
        }
    }

    if ((choice == 1 && isRed) || (choice == 2 && !isRed && num != 0)) {
        win(1);
    }
    else {
        lost();
    }
}

void oddOrEven() {
    std::cout << "\nPlease enter your choice (1 for Odd, 2 for Even)\nINPUT: ";
    std::cin >> choice;
    loadMoney();
    randomNum();

    if ((num % 2 == 1 && choice == 1) || (num % 2 == 0 && choice == 2 && num != 0)) {
        win(1);
    }
    else {
        lost();
    }
}

void highOrLow() {
    std::cout << "\nPlease enter your choice (1 for Low (1-18), 2 for High (19-36))\nINPUT: ";
    std::cin >> choice;
    loadMoney();
    randomNum();

    if ((num >= 1 && num <= 18 && choice == 1) || (num >= 19 && num <= 36 && choice == 2)) {
        win(1);
    }
    else {
        lost();
    }
}

void dozens() {
    std::cout << "\nPlease enter your choice (1 for 1-12, 2 for 13-24, 3 for 25-36)\nINPUT: ";
    std::cin >> choice;
    loadMoney();
    randomNum();

    if ((num >= 1 && num <= 12 && choice == 1) || (num >= 13 && num <= 24 && choice == 2) || (num >= 25 && num <= 36 && choice == 3)) {
        win(2);
    }
    else {
        lost();
    }
}

void columns() {
    std::cout << "\nPlease enter your choice (1, 2, or 3)\nINPUT: ";
    std::cin >> choice;
    loadMoney();
    randomNum();

    for (int i = 0; i < sizeof(rows) / sizeof(rows[0]); ++i) {
        if ((num - rows[i]) % 3 == choice % 3 && num != 0) {
            win(2);
            return;
        }
    }

    lost();
}