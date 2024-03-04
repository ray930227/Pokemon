#ifndef POKEMON_CHARACTER_HPP
#define POKEMON_CHARACTER_HPP

#include "Object.hpp"

class Character:public Object{
private:
    std::string Name;
public:
    Character();
};

#endif
