#ifndef POKEMON_FIGHTTEXTUI_HPP
#define POKEMON_FIGHTTEXTUI_HPP

#include "TextBox.hpp"

class FightTextUI {
private:
    std::shared_ptr<TextBox> m_FinishBox;
    std::shared_ptr<TextBox> m_PlayerTextBox;
    std::shared_ptr<TextBox> m_EnemyTextBox;
    std::shared_ptr<TextBox> m_DefeatTextBox;
public:
    FightTextUI();

    [[nodiscard]] std::vector<std::vector<std::shared_ptr<Util::GameObject>>> GetChildren() const;

    void SetFinish(const std::string &Winner,const std::string &Loser);

    void SetDefeat(const std::string &PokeName);

    void SetPlayer(const std::string &PlayerName, const std::string &UseSkill, float DamageRate);

    void SetEnemy(const std::string &EnemyName, const std::string &UseSkill, float DamageRate);

    [[nodiscard]] bool GetPlayerVisibility() const;

    [[nodiscard]] bool GetEnemyVisibility() const;

    void Next();
};

#endif //POKEMON_FIGHTTEXTUI_HPP
