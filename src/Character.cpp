#include "Character.hpp"

Character::Character(const std::vector<std::string> &ImagePaths) {
    m_Speed = 10;
    m_Image=std::make_shared<GIF>(ImagePaths);
}

std::string &Character::GetName() {
    return m_Name;
}

int Character::GetSpeed() {
    return m_Speed;
}

std::shared_ptr<GIF> Character::GetImage() {
    return m_Image;
}

void Character::SetName(const std::string &str) {
    m_Name = str;
}

void Character::SetSpeed(float value) {
    m_Speed = value;
}
