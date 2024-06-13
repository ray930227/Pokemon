#ifndef POKEMON_FIGHTTEXTUI_HPP
#define POKEMON_FIGHTTEXTUI_HPP

#include "TextBox.hpp"
#include "Character.hpp"
#include <cmath>

class FightTextUI {
private:
    std::shared_ptr<TextBox> m_TB;
    std::shared_ptr<Character> m_Player;
    std::shared_ptr<Character> m_Enemy;
public:
    FightTextUI(const std::shared_ptr<Character> &Player, const std::shared_ptr<Character> &Enemy);

    [[nodiscard]] std::vector<std::vector<std::shared_ptr<Util::GameObject>>> GetChildren() const;

    void SetPlayer(int PokeIndex, int EnemyIndex, int SkillIndex);

    void SetEnemy(int EnemyIndex, int PokeIndex, int SkillIndex);

    void SetDefeatWild(int PokeIndex, int EnemyIndex, int EXP);

    void SetDefeat(const std::string &PokeName);

    void SetPokePack();

    void SetFinish(const std::string &Winner, const std::string &Loser);

    void SetGainEXP(const std::string &PokeName, int EXP);

    void SetRun(bool isWildPokemon);

    void SetLevelUP(const std::string &PokeName, int NewLV);

    void SetChangePoke(const std::string &OldPokeName, const std::string &NewPokeName);

    void SetChangeFail(const std::string &PokeName);

    void SetLose(const std::string &PlayerName);

    void SetNoHit(const std::string &PokeName);

    [[nodiscard]] bool GetTBVisibility() const;

    void Next();
};

#endif //POKEMON_FIGHTTEXTUI_HPP
