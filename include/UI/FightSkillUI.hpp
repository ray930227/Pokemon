#ifndef POKEMON_FIGHTSKILLUI_HPP
#define POKEMON_FIGHTSKILLUI_HPP

#include "Text.hpp"

class FightSkillUI {
private:
    std::vector<std::shared_ptr<Text>> m_Skills;
public:
    FightSkillUI();

    [[nodiscard]] std::vector<std::shared_ptr<Util::GameObject>> GetChildren() const;

    void SetText(const std::vector<std::string> PokeSkill);

    void SetVisible(bool visible);

};

#endif //POKEMON_FIGHTSKILLUI_HPP
