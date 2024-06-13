#ifndef POKEMON_ITEMUI_HPP
#define POKEMON_ITEMUI_HPP

#include "Image.hpp"
#include "Character.hpp"
#include "UI/PokeBagUI.hpp"

class ItemUI {
private:
    std::shared_ptr<Image> m_ItemBG;
    std::shared_ptr<PokeBagUI> m_PokeBagUI;
    std::shared_ptr<Character> m_Player;
    std::shared_ptr<Image> m_Arrow;
    std::shared_ptr<Image> m_Arrow2;
    std::vector<std::shared_ptr<Text>> m_Texts;
    std::shared_ptr<TextBox> m_TB;
    int m_RowTopIndex;
    std::vector<std::pair<std::string, int>> m_Items;
    unsigned m_mode=0;
public:
    ItemUI(const std::shared_ptr<Character> &Player);

    void Start(unsigned mode);

    void Run();

    std::vector<std::shared_ptr<Util::GameObject>> GetChildren();

    bool GetVisible();

    void SetVisible(bool Visibile);

    int GetDecision();

protected:
    void Updata();

    void ChooseItem();

    void ChangeSkill();

    void Action();
};

#endif //POKEMON_ITEMUI_HPP
