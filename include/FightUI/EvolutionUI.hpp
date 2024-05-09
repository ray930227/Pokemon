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
    std::shared_ptr<Image> m_BG;
    std::shared_ptr<TextBox> m_TextBox;
    std::vector<std::string> m_Name;
    int m_Interval;
public:
    EvolutionUI();

    [[nodiscard]] std::vector<std::shared_ptr<Util::GameObject>> GetChildren() const;

    void Setting(int PokemonID);

    void SetVisible(bool visible);

    void SetPokeVisible(bool visible);

    void SetInterval(int interval);

    int GetTextIndex();

    void Play();

    void Pause();

    void Next();

    void StopEvolution();

    [[nodiscard]] bool GetVisibility() const;

    int GetInterval();

    void SetCurrentFrame(size_t index);

};

#endif //POKEMON_EVOLUTIONUI_HPP
