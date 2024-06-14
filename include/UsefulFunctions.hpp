#ifndef POKEMON_USEFULFUNCTIONS_HPP
#define POKEMON_USEFULFUNCTIONS_HPP

#include <vector>
#include <string>
#include <algorithm>

namespace useful {
    std::vector<std::string> Split(std::string &str, char interval);
}

namespace PokeFunction {
    int FindIndex(std::string MyType);

    float TypeDamage(std::string MyType, std::vector<std::string> EnemyType);
}
#endif //POKEMON_USEFULFUNCTIONS_HPP
