#ifndef HAND_H
#define HAND_H

#include <vector>
#include "card.hpp"

class Hand {
public:
    Hand();
    virtual ~Hand();

    void Add(Card* pCard);
    void Clear();
    int GetTotal() const;

protected:
    std::vector<Card*> m_Cards;
};

#endif
