#ifndef HOUSE_H
#define HOUSE_H

#include "genericPlayerClass.hpp"

class House : public GenericPlayer {
public:
    House(const std::string& name = "House");

    virtual bool IsHitting() const override;

    void FlipFirstCard();

    friend std::ostream& operator<<(std::ostream& os, const House& aHouse);
};

#endif
