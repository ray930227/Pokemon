#ifndef POKEMON_POKEMONBAG_HPP
#define POKEMON_POKEMONBAG_HPP

#include "Pokemon.hpp"

class PokemonBag {
private:
    std::vector<std::shared_ptr<Pokemon>> Pokemons;
public:
    PokemonBag();

    std::vector<std::shared_ptr<Pokemon>> GetPokemons();

    void addPomekon(const std::shared_ptr<Pokemon> &pokemon);

    bool isFull();
};

#endif //POKEMON_POKEMONBAG_HPP
