#include "hand.hpp"
#include <algorithm>

Hand::Hand() {}

Hand::~Hand() {
    Clear();
}

void Hand::Add(Card* pCard) {
    m_Cards.push_back(pCard);
}

void Hand::Clear() {
    for (auto card : m_Cards) {
        delete card;
    }
    m_Cards.clear();
}

int Hand::GetTotal() const {
    if (m_Cards.empty()) {
        return 0;
    }

    int total = 0;
    bool containsAce = false;

    for (auto card : m_Cards) {
        total += card->GetValue();
        if (card->GetValue() == Card::ACE) {
            containsAce = true;
        }
    }

    if (containsAce && total <= 11) {
        total += 10;  // Add 10 to treat ACE as 11
    }

    return total;
}
