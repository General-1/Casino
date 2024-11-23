#include "deck.hpp"
#include <random>
#include <algorithm>

Deck::Deck() {
    Populate();
}

Deck::~Deck() {}

void Deck::Populate() {
    Clear();
    for (int s = Card::CLUBS; s <= Card::SPADES; ++s) {
        for (int r = Card::ACE; r <= Card::KING; ++r) {
            Add(new Card(static_cast<Card::rank>(r), static_cast<Card::suit>(s)));
        }
    }
}

void Deck::Shuffle() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::shuffle(m_Cards.begin(), m_Cards.end(), mt);
}

void Deck::Deal(Hand& aHand) {
    if (!m_Cards.empty()) {
        aHand.Add(m_Cards.back());
        m_Cards.pop_back();
    } else {
        std::cerr << "Out of cards!\n";
    }
}

void Deck::AdditionalCards(GenericPlayer& aGenericPlayer) {
    while (!aGenericPlayer.IsBusted() && aGenericPlayer.IsHitting()) {
        Deal(aGenericPlayer);
        if (aGenericPlayer.IsBusted()) {
            aGenericPlayer.Bust();
        }
    }
}
