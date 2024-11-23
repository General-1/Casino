#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<ctime>
#include "card.hpp"
#include "deck.hpp"
#include "game.hpp"
#include "GenericPlayerClass.hpp"
#include "hand.hpp"
#include "house.hpp"
#include "player.hpp"


Card::Card(rank r, suit s, bool ifu) : m_Rank(r), m_Suit(s), m_IsFaceUp(ifu) {}

int Card::GetValue() const {
    if (!m_IsFaceUp) {
        return 0;
    }

    return (m_Rank > 10) ? 10 : m_Rank;
}

void Card::flip() {
    m_IsFaceUp = !m_IsFaceUp;
}

std::ostream& operator<<(std::ostream& os, const Card& aCard) 
{
    const char* rankStrings[] = { "", "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };
    const char* suitStrings[] = { "C", "D", "H", "S" };

    if (aCard.m_IsFaceUp) {
        os << rankStrings[aCard.m_Rank] << suitStrings[aCard.m_Suit];
    } else {
        os << "XX"; 
    
    return os;
}
