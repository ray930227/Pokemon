#include "PokemonBag.hpp"

PokemonBag::PokemonBag() {
}

std::vector<std::shared_ptr<Pokemon>> PokemonBag::GetPokemons() {
    return m_Pokemons;
}

void PokemonBag::AddPomekon(const std::shared_ptr<Pokemon> &pokemon) {
    if (!IsFull())
        m_Pokemons.push_back(pokemon);
}

void PokemonBag::SetPokemons(std::vector<std::shared_ptr<Pokemon>> Pokemons) {
    m_Pokemons=Pokemons;
}

int PokemonBag::Size() {
    return m_Pokemons.size();
}

bool PokemonBag::IsFull() {
    return m_Pokemons.size() == 6;
}

bool PokemonBag::IsAllPokeDie() {
    for (const auto& pokemon: m_Pokemons) {
        if (!pokemon->IsPokemonDying())
            return false;
    }
    return true;
}