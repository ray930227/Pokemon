#ifndef POKEMON_POKEFAINTEDUI_HPP
#define POKEMON_POKEFAINTEDUI_HPP

#include "TextBox.hpp"
#include "TFBox.hpp"

class PokeFaintedUI {
private:
    std::shared_ptr<TextBox> m_TextBox;
    std::shared_ptr<TFBox> m_TFBox;
public:
    PokeFaintedUI();

    [[nodiscard]] std::vector<std::vector<std::shared_ptr<Util::GameObject>>> GetChildren() const;

    void SetVisible(bool visible);

    void SetText(const std::string &PokeName);

    void SetTextBoxVisible(bool visible);

    void SetTFBoxVisible(bool visible);

    void Next();

    size_t GetCurrentIndex();

    bool TFBoxChoose();

    bool GetTF();

    [[nodiscard]] bool GetVisibility() const;
};

#endif //POKEMON_POKEFAINTEDUI_HPP
