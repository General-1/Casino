#ifndef DECK_H
#define DECK_H

#include "hand.hpp"
#include "genericPlayerClass.hpp"
#include <vector>

class Deck : public Hand {
public:
    Deck();
    virtual ~Deck();

    void Populate();
    void Shuffle();
    void Deal(Hand& aHand);
    void AdditionalCards(GenericPlayer& aGenericPlayer);
};

#endif
