#ifndef POKEMON_POKEMONBAG_HPP
#define POKEMON_POKEMONBAG_HPP

#include "Pokemon.hpp"

class PokemonBag {
private:
    std::vector<std::shared_ptr<Pokemon>> m_Pokemons;
public:
    PokemonBag();

    std::vector<std::shared_ptr<Pokemon>> GetPokemons();

    void addPomekon(const std::shared_ptr<Pokemon> &pokemon);

    void SetPokemons(std::vector<std::shared_ptr<Pokemon>> Pokemons);

    int size();

    bool isFull();

    bool IsAllPokeDie();
};

#endif //POKEMON_POKEMONBAG_HPP