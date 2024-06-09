#ifndef POKEMON_SETTINGUI_HPP
#define POKEMON_SETTINGUI_HPP

#include "Image.hpp"
#include "Character.hpp"
#include "Util/Input.hpp"
#include "UI/PokeBagUI.hpp"

class SettingUI{
private:
    std::shared_ptr<Image> m_SettingBG;
    std::shared_ptr<Image> m_Arrow;
    std::shared_ptr<PokeBagUI> m_PokeBagUI;

    std::shared_ptr<Character> m_Player;
public:
    SettingUI(const std::shared_ptr<Character>& Player);

    void Start();

    void Run();

    std::vector<std::shared_ptr<Util::GameObject>> GetChildren();

    bool GetVisibile();

    void SetVisibile(bool Visibile);
};

#endif //POKEMON_SETTINGUI_HPP
