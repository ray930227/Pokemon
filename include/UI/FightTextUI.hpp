#ifndef POKEMON_FIGHTTEXTUI_HPP
#define POKEMON_FIGHTTEXTUI_HPP

#include "TextBox.hpp"
#include <cmath>

class FightTextUI {
private:
    std::shared_ptr<TextBox> m_PlayerTextBox;
    std::shared_ptr<TextBox> m_EnemyTextBox;
    std::shared_ptr<TextBox> m_DefeatTextBox;
    std::shared_ptr<TextBox> m_PokePackTextBox;
    std::shared_ptr<TextBox> m_FinishTextBox;
    std::shared_ptr<TextBox> m_GainEXPTextBox;
    std::shared_ptr<TextBox> m_RunTextBox;
    std::shared_ptr<TextBox> m_LevelUPTextBox;
    std::shared_ptr<TextBox> m_ChangePokeTextBox;
    std::shared_ptr<TextBox> m_ChangeFailTextBox;
    std::shared_ptr<TextBox> m_LoseTextBox;
public:
    FightTextUI();

    [[nodiscard]] std::vector<std::vector<std::shared_ptr<Util::GameObject>>> GetChildren() const;

    void SetPlayer(const std::string &PlayerName, const std::string &UseSkill, float DamageRate);

    void SetEnemy(const std::string &EnemyName, const std::string &UseSkill, float DamageRate);

    void SetDefeat(const std::string &PokeName);

    void SetPokePack();

    void SetFinish(const std::string &Winner,const std::string &Loser);

    void SetGainEXP(const std::string &PokeName,int EXP);

    void SetRun();

    void SetLevelUP(const std::string &PokeName,int NewLV);

    void SetChangePoke(const std::string &OldPokeName, const std::string &NewPokeName);

    void SetChangeFail(const std::string &PokeName);

    void SetLose(const std::string &PlayerName);

    [[nodiscard]] bool GetPlayerVisibility() const;

    [[nodiscard]] bool GetEnemyVisibility() const;

    [[nodiscard]] bool GetDefeatVisibility() const;

    [[nodiscard]] bool GetGainEXPVisibility() const;

    [[nodiscard]] bool GetRunVisibility() const;

    [[nodiscard]] bool GetLevelUPVisibility() const;

    [[nodiscard]] bool GetChangePokeVisibility() const;

    [[nodiscard]] bool GetChangeFailVisibility() const;
    void Next();
};

#endif //POKEMON_FIGHTTEXTUI_HPP
