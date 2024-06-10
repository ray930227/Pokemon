#ifndef POKEMON_FIGHTSKILLUI_HPP
#define POKEMON_FIGHTSKILLUI_HPP

#include "Text.hpp"
#include "Image.hpp"
#include "Character.hpp"
#include "Util/Input.hpp"

class FightSkillUI {
private:
    std::vector<std::shared_ptr<Text>> m_Skills;
    std::shared_ptr<Text> m_SkillInfo;
    std::shared_ptr<Image> m_FightSkillBG;
    std::shared_ptr<Image> m_Arrow;
    std::shared_ptr<Character> m_Player;
public:
    FightSkillUI(const std::shared_ptr<Character> &Player);

    [[nodiscard]] std::vector<std::shared_ptr<Util::GameObject>> GetChildren() const;

    void SetText(unsigned long long int PokeIndex);

    void SetVisible(bool visible);

    bool Choose(unsigned long long int PokeIndex);

    int GetDecision();

    void ShowSkillInfo(unsigned long long int PokeIndex);

    void ReSetArrow();
};

#endif //POKEMON_FIGHTSKILLUI_HPP
