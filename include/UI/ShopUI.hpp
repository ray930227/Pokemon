#ifndef POKEMON_SHOPUI_HPP
#define POKEMON_SHOPUI_HPP

#include "Image.hpp"
#include "TFBox.hpp"
#include "TextBox.hpp"
#include "Character.hpp"
#include "Util/Input.hpp"
#include <memory>

class ShopUI {
private:
    std::vector<std::shared_ptr<Image>> m_Arrows;
    std::shared_ptr<Image> m_ShopBG;
    std::shared_ptr<Image> m_ShopInsideBG;
    std::shared_ptr<TFBox> m_TFBox;
    std::shared_ptr<TextBox> m_TextBox;
    std::vector<std::pair<std::shared_ptr<Text>, int>> m_ItemRow;
    std::shared_ptr<Character> m_Player;
    std::vector<std::pair<std::string, int>> m_BuyList;
    std::vector<std::pair<std::string, int>> m_SellList;
    std::vector<int> m_SellMoneyList;
    std::shared_ptr<Text> m_Money;
    size_t m_RowTopIndex = 0;


public:
    ShopUI(std::shared_ptr<Character> &Player);

    void Start();

    void Run();

    std::vector<std::shared_ptr<Util::GameObject>> GetChildren();

    bool GetVisibile();
};

#endif //POKEMON_SHOPUI_HPP
