#ifndef POKEMON_CHARACTER_HPP
#define POKEMON_CHARACTER_HPP

#include "Util/GameObject.hpp"

class Character:public Util::GameObject{
private:
    std::string Name;
    float Speed;
public:
    Character();
    std::string& GetName();
    int GetSpeed();
    void SetName(const std::string &str);
    void SetSpeed(float value);
    void SetPosition(const glm::vec2& Position);
};

#endif
