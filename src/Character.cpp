#include "Character.hpp"

Character::Character() {
    m_Speed = 10;
}

std::string &Character::GetName() {
    return m_Name;
}

int Character::GetSpeed() {
    return m_Speed;
}

void Character::SetName(const std::string &str) {
    m_Name = str;
}

void Character::SetSpeed(float value) {
    m_Speed = value;
}

void Character::SetPosition(const glm::vec2 &Position) {
    m_Transform.translation = Position;
}
