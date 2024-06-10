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
    std::vector<std::shared_ptr<Text>> m_Texts;
    std::shared_ptr<TextBox> m_TB;
    int m_RowTopIndex;
    std::vector<std::pair<std::string, int>> m_Items;
    std::vector<std::string> m_useItem={"精靈球","超級球","高級球","傷藥","好傷藥",
                                      "厲害傷藥","全滿藥","全複藥","解毒藥",
                                      "灼傷藥","解凍藥","解眠藥","解麻藥"};

public:
    ItemUI(const std::shared_ptr<Character>& Player);

    void Start();

    void Run(unsigned mode);

    std::vector<std::shared_ptr<Util::GameObject>> GetChildren();

    bool GetVisible();

    void SetVisible(bool Visibile);

    int GetDecision();
protected:
    void Updata();

    void ChooseItem();

    void Action(unsigned mode);
};

#endif //POKEMON_ITEMUI_HPP
