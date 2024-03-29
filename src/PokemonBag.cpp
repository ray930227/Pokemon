#include "PokemonBag.hpp"

PokemonBag::PokemonBag() {

}

std::vector<std::shared_ptr<Pokemon>> PokemonBag::GetPokemons() {
    return Pokemons;
}

void PokemonBag::addPomekon(const std::shared_ptr<Pokemon> &pokemon) {
    if (!isFull())
        Pokemons.push_back(pokemon);
}

bool PokemonBag::isFull() {
    return Pokemons.size() == 6;
}
