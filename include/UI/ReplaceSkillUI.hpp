#ifndef POKEMON_REPLACESKILLUI_HPP
#define POKEMON_REPLACESKILLUI_HPP

#include "TextBox.hpp"
#include "TFBox.hpp"
#include "Util/Input.hpp"

class ReplaceSkillUI{
private:
    std::shared_ptr<TextBox> m_TextBox;
    std::shared_ptr<TFBox> m_TFBox;
public:
    ReplaceSkillUI();

    [[nodiscard]] std::vector<std::vector<std::shared_ptr<Util::GameObject>>> GetChildren() const;

    void SetVisible(bool visible);

    void SetText(const std::string& PlayerPokemon,const std::string& NewSkill);

    void SetTextBoxVisible(bool visible);

    void SetTFBoxVisible(bool visible);

    void Next();

    size_t GetCurrentIndex();

    bool TFBoxChoose();

    bool GetTF();

    [[nodiscard]] bool GetVisibility() const;
};

#endif //POKEMON_REPLACESKILLUI_HPP
