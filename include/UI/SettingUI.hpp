#ifndef POKEMON_SETTINGUI_HPP
#define POKEMON_SETTINGUI_HPP

#include "Image.hpp"
#include "Character.hpp"
#include "TextBox.hpp"
#include "Util/Input.hpp"
#include "UI/PokeBagUI.hpp"
#include "UI/ItemUI.hpp"
#include "UI/PokedexUI.hpp"

class SettingUI {
private:
    std::shared_ptr<Image> m_SettingBG;
    std::shared_ptr<Image> m_Arrow;
    std::shared_ptr<PokeBagUI> m_PokeBagUI;
    std::shared_ptr<ItemUI> m_ItemUI;
    std::shared_ptr<TextBox> m_TB;
    std::shared_ptr<Character> m_Player;
    std::shared_ptr<PokedexUI> m_PokedexUI;
public:
    SettingUI(const std::shared_ptr<Character> &Player,std::shared_ptr<ComputerUI> ComputerUI);

    void Start();

    void Run();

    std::vector<std::shared_ptr<Util::GameObject>> GetChildren();

    bool GetVisible();

    void SetVisible(bool Visible);
};

#endif //POKEMON_SETTINGUI_HPP
