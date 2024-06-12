#ifndef POKEMON_POKEDEXUI_HPP
#define POKEMON_POKEDEXUI_HPP

#include "Image.hpp"
#include "Text.hpp"
#include "Util/Input.hpp"
#include "SFXSystem.hpp"
#include "Character.hpp"
#include "UI/ComputerUI.hpp"
#include <fstream>

class PokedexUI {
private:
    std::shared_ptr<Image> m_PokedexBG;
    std::shared_ptr<Image> m_Arrow;
    std::shared_ptr<Image> m_PokeImage;
    std::vector<std::shared_ptr<Text>> m_NameTexts;
    std::vector<std::shared_ptr<Text>> m_IDTexts;
    std::shared_ptr<Text> m_GetText;
    bool m_PokeGet[151] = {false};
    std::vector<std::string> m_PokeNames;
    int m_RowTopIndex = 0;
    SFXSystem m_SFXSystem;
    std::shared_ptr<Character> m_Player;
    std::shared_ptr<ComputerUI> m_ComputerUI;
public:
    PokedexUI(const std::shared_ptr<Character> &Player, std::shared_ptr<ComputerUI> ComputerUI);

    void Start();

    void Run();

    std::vector<std::shared_ptr<Util::GameObject>> GetChildren();

    bool GetVisible();

    void SetVisible(bool Visible);

protected:
    void Update();
};

#endif //POKEMON_POKEDEXUI_HPP
