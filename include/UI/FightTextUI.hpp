#ifndef POKEMON_FIGHTTEXTUI_HPP
#define POKEMON_FIGHTTEXTUI_HPP

#include "TextBox.hpp"

class FightTextUI {
private:
    std::shared_ptr<TextBox> m_TextBox;
    std::shared_ptr<TextBox> m_PlayerTextBox;
    std::shared_ptr<TextBox> m_EnemyTextBox;
public:
    FightTextUI();

    [[nodiscard]] std::vector<std::vector<std::shared_ptr<Util::GameObject>>> GetChildren() const;

    void SetPlayer(const std::string &PlayerName, const std::string &UseSkill, float DamageRate);

    void SetEnemy(const std::string &EnemyName, const std::string &UseSkill, float DamageRate);

    [[nodiscard]] bool GetPlayerVisibility() const;

    [[nodiscard]] bool GetEnemyVisibility() const;

    void Next();
};

#endif //POKEMON_FIGHTTEXTUI_HPP
