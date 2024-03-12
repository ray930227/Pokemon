#include "Character.hpp"

Character::Character() {
    Speed=10;
}

std::string &Character::GetName() {
    return Name;
}

int Character::GetSpeed() {
    return Speed;
}

void Character::SetName(const std::string &str) {
    Name=str;
}

void Character::SetSpeed(float value) {
    Speed=value;
}

void Character::SetPosition(const glm::vec2 &Position) {
    m_Transform.translation = Position;
}
