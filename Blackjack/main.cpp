#include "game.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

const int SIMULATION_ROUNDS = 100000;
const int BASE_BET = 10;

// Simulate a single round of Blackjack using basic strategy
bool playBasicStrategy(Dealer& dealer, Player& player) {
    dealer.Hit();
    dealer.Hit();
    player.Hit();
    player.Hit();
    
    while (player.CheckHand() < 17) {
        player.Hit();
    }
    
    if (player.CheckHand() > 21) return false; // Player busts

    while (dealer.CheckHand() < 17) {
        dealer.Hit();
    }

    return player.CheckHand() <= 21 && (player.CheckHand() > dealer.CheckHand() || dealer.CheckHand() > 21);
}

void simulateMartingaleStrategy(int rounds) {
    init_deck();
    shuffler();

    Dealer dealer;
    Player player;
    int balance = 1000;
    int bet = 10;
    int maxBet = 320; 

    for (int i = 0; i < rounds; i++) {
        if (is_deck_empty()) { 
            cout << "Deck empty, reshuffling..." << endl;
            init_deck();
            shuffler();
        }

        dealer = Dealer();
        player = Player();

        if (balance < bet) break;

        bool won = playBasicStrategy(dealer, player);

        if (won) {
            balance += bet;
            bet = 10;
        } else {
            balance -= bet;
            bet = min(bet * 2, maxBet);
        }
    }

    cout << "Final Balance (Martingale): " << balance << endl;
}

void simulateBasicStrategy(int rounds) {
    init_deck();
    shuffler();

    Dealer dealer;
    Player player;
    int wins = 0;

    for (int i = 0; i < rounds; i++) {
        if (is_deck_empty()) { 
            cout << "Deck empty, reshuffling..." << endl;
            init_deck();
            shuffler();
        }

        dealer = Dealer();
        player = Player();

        bool win = playBasicStrategy(dealer, player);
        if (win) wins++;
    }

    cout << "Final Win Rate (Basic Strategy): " << (wins * 100.0 / rounds) << "%" << endl;
}

void playManually() {
    addDealer();
    addPlayer();
    start();
    turn();
    checkWin();
}

int main() {
    srand(time(0));
    int choice;
    cout << "Choose an option:\n1. Play Manually\n2. Run Monte Carlo Simulation\nEnter choice: ";
    cin >> choice;

    if (choice == 1) {
        playManually();
    } else if (choice == 2) {
        int strategy;
        cout << "Choose Monte Carlo Strategy:\n1. Basic Strategy\n2. Martingale (Doubling Strategy)\nEnter choice: ";
        cin >> strategy;
        
        cout << "Running Monte Carlo Simulation..." << endl;
        if (strategy == 1) {
            simulateBasicStrategy(SIMULATION_ROUNDS);
        } else if (strategy == 2) {
            simulateMartingaleStrategy(SIMULATION_ROUNDS);
        } else {
            cout << "Invalid strategy choice!" << endl;
        }
    } else {
        cout << "Invalid choice!" << endl;
    }

    return 0;
}
