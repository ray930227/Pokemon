#ifndef POKEMON_EVOLUTIONUI_HPP
#define POKEMON_EVOLUTIONUI_HPP

#include "GIF.hpp"
#include "TextBox.hpp"
#include <sstream>
#include <iomanip>
#include <fstream>

class EvolutionUI{
private:
    std::shared_ptr<GIF> m_PokemonGIF;
    std::shared_ptr<TextBox> m_TextBox;
    std::vector<std::string> m_Name;
public:
    EvolutionUI();

    [[nodiscard]] std::vector<std::shared_ptr<Util::GameObject>> GetChildren() const;

    void Setting(int PokemonID);


};

#endif //POKEMON_EVOLUTIONUI_HPP
