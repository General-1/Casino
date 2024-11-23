#include "genericPlayerClass.hpp"

GenericPlayer::GenericPlayer(const std::string& name) : m_Name(name) {}
GenericPlayer::~GenericPlayer() {}

bool GenericPlayer::IsBusted() const {
    return GetTotal() > 21;
}

void GenericPlayer::Bust() const {
    std::cout << m_Name << " busted!" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const GenericPlayer& aGenericPlayer) {
    os << aGenericPlayer.m_Name << " has " << aGenericPlayer.GetTotal() << " points";
    return os;
}
