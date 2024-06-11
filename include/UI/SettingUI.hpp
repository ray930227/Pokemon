#ifndef POKEMON_SETTINGUI_HPP
#define POKEMON_SETTINGUI_HPP

#include "Image.hpp"
#include "Character.hpp"
#include "TextBox.hpp"
#include "MapSystem.hpp"
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
    std::shared_ptr<TFBox> m_TFBox;
    std::shared_ptr<Character> m_Player;
    std::shared_ptr<PokedexUI> m_PokedexUI;
    bool m_isSave = false;
public:
    SettingUI(const std::shared_ptr<Character> &Player, const std::shared_ptr<ComputerUI> &ComputerUI);

    void Start();

    void Run();

    std::vector<std::shared_ptr<Util::GameObject>> GetChildren();

    bool GetVisible();

    void SetVisible(bool Visible);

    void Save(const std::shared_ptr<Character> &player, const std::shared_ptr<Character> &Bromance,
              const std::shared_ptr<ComputerUI> &ComputerUI, const std::shared_ptr<MapSystem> &mapSystem);

    void Read(const std::shared_ptr<Character> &player, const std::shared_ptr<Character> &Bromance,
              const std::shared_ptr<ComputerUI> &ComputerUI, const std::shared_ptr<MapSystem> &mapSystem);

    bool IsSave();

protected:
    void SavePokemons(const std::string &path, const std::vector<std::shared_ptr<Pokemon>> &pokemons);

    std::vector<std::shared_ptr<Pokemon>> ReadPokemons(const std::string &path);
};

#endif //POKEMON_SETTINGUI_HPP
