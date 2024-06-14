#include "PokemonBag.hpp"

PokemonBag::PokemonBag() {
}

std::vector<std::shared_ptr<Pokemon>> PokemonBag::GetPokemons() {
    return m_Pokemons;
}

void PokemonBag::addPomekon(const std::shared_ptr<Pokemon> &pokemon) {
    if (!isFull())
        m_Pokemons.push_back(pokemon);
}

void PokemonBag::SetPokemons(std::vector<std::shared_ptr<Pokemon>> Pokemons) {
    m_Pokemons=Pokemons;
}

int PokemonBag::size() {
    return m_Pokemons.size();
}

bool PokemonBag::isFull() {
    return m_Pokemons.size() == 6;
}

bool PokemonBag::IsAllPokeDie() {
    for (const auto& pokemon: m_Pokemons) {
        if (!pokemon->IsPokemonDying())
            return false;
    }
    return true;
}