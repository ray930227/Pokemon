#ifndef POKEMON_SHOPUI_HPP
#define POKEMON_SHOPUI_HPP

#include "Image.hpp"
#include "TFBox.hpp"
#include "TextBox.hpp"
#include "Util/Input.hpp"
#include <memory>

class ShopUI{
private:
    std::vector<std::shared_ptr<Image>> m_Arrows;
    std::shared_ptr<Image> m_ShopBG;
    std::shared_ptr<Image> m_ShopInsideBG;
    std::shared_ptr<TFBox> m_TFBox;
    std::shared_ptr<TextBox> m_TextBox;
public:
    ShopUI();

    void Start();

    void Run();

    std::vector<std::shared_ptr<Util::GameObject>> GetChildren();

    bool GetVisibile();
};

#endif //POKEMON_SHOPUI_HPP
