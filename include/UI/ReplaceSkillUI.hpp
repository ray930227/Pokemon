#ifndef POKEMON_REPLACESKILLUI_HPP
#define POKEMON_REPLACESKILLUI_HPP

#include "TextBox.hpp"
#include "TFBox.hpp"
#include "Character.hpp"
#include "Util/Input.hpp"

class ReplaceSkillUI {
private:
    std::shared_ptr<TextBox> m_TextBox;
    std::shared_ptr<TFBox> m_TFBox;
    std::shared_ptr<Character> m_Player;
public:
    ReplaceSkillUI(const std::shared_ptr<Character> &Player);

    [[nodiscard]] std::vector<std::vector<std::shared_ptr<Util::GameObject>>> GetChildren() const;

    void Run();

    void SetVisible(bool visible);

    void SetText(int PokeIndex);

    void SetTextBoxVisible(bool visible);

    void SetTFBoxVisible(bool visible);

    void Next();

    size_t GetCurrentIndex();

    bool TFBoxChoose();

    bool GetTF();

    [[nodiscard]] bool GetVisibility() const;
};

#endif //POKEMON_REPLACESKILLUI_HPP
