#ifndef POKEMON_CHARACTER_HPP
#define POKEMON_CHARACTER_HPP

#include "Util/GameObject.hpp"
#include "PokemonBag.hpp"

class Character : public Util::GameObject {
private:
    std::string m_Name;
    float m_Speed;
    PokemonBag m_PokemonBag;
public:
    Character();

    std::string &GetName();

    int GetSpeed();

    void SetName(const std::string &str);

    void SetSpeed(float value);

    void SetPosition(const glm::vec2 &Position);
};

#endif
