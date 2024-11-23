#include "player.hpp"
#include <iostream>

Player::Player(const std::string& name) : GenericPlayer(name) {}

bool Player::IsHitting() const {
    return GetTotal() < 17; // Example condition: hit if total is below 17
}

void Player::Win() const {
    std::cout << m_Name << " wins!" << std::endl;
}

void Player::Lose() const {
    std::cout << m_Name << " loses!" << std::endl;
}

void Player::Push() const {
    std::cout << m_Name << " pushes!" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Player& aPlayer) {
    os << static_cast<const GenericPlayer&>(aPlayer);
    os << " (Player)";
    return os;
}
