#include "house.hpp"
#include <iostream>

House::House(const std::string& name) : GenericPlayer(name) {}

bool House::IsHitting() const {
    return GetTotal() < 17; // Example condition: hit if total is below 17
}

void House::FlipFirstCard() {
    if (!m_Cards.empty()) {
        m_Cards[0]->flip(); // Flip the first card
    }
}

std::ostream& operator<<(std::ostream& os, const House& aHouse) {
    os << static_cast<const GenericPlayer&>(aHouse);
    os << " (House)";
    return os;
}
