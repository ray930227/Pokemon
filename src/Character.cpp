#include "Character.hpp"

Character::Character() {
    m_PokemonBag = std::make_shared<PokemonBag>();
    m_ItemBag = std::make_shared<ItemBag>();
}

Character::Character(const std::vector<std::vector<std::string>> &ImagePathses) {
    m_Image = std::make_shared<GIF>(ImagePathses[0]);
    SetImagePathses(ImagePathses);
    m_CurrentImagePath = 0;
    SetSpeed(15);
    m_PokemonBag = std::make_shared<PokemonBag>();
    m_ItemBag = std::make_shared<ItemBag>();
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

std::shared_ptr<PokemonBag> Character::GetPokemonBag() {
    return m_PokemonBag;
}

std::shared_ptr<ItemBag> Character::GetItemBag() {
    return m_ItemBag;
}

int Character::GetMoney() {
    return m_Money;
}

void Character::SetName(const std::string &str) {
    m_Name = str;
}

void Character::SetSpeed(float value) {
    m_Speed = value;
    m_Image->SetInterval((int) value * 15);
}

void Character::SetImagePathses(const std::vector<std::vector<std::string>> &ImagePathses) {
    m_ImagePathses = ImagePathses;
}

void Character::SetCurrentImagePath(size_t index) {
    m_CurrentImagePath = index;
    if (m_Image->IsPlaying() == false)
        m_Image->SetImagePaths(m_ImagePathses[m_CurrentImagePath]);
}

void Character::SetMoney(int money) {
    m_Money = money;
}