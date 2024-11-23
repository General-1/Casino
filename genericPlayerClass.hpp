#ifndef GENERICPLAYERCLASS_H
#define GENERICPLAYERCLASS_H

#include "hand.hpp"
#include <string>
#include <iostream>

class GenericPlayer : public Hand {
public:
    GenericPlayer(const std::string& name);
    virtual ~GenericPlayer();

    virtual bool IsHitting() const = 0;

    bool IsBusted() const;

    void Bust() const;

    friend std::ostream& operator<<(std::ostream& os, const GenericPlayer& aGenericPlayer);

protected:
    std::string m_Name;
};

#endif
