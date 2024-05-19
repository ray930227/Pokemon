#ifndef POKEMON_FIGHTSKILLUI_HPP
#define POKEMON_FIGHTSKILLUI_HPP

#include "Text.hpp"
#include "Image.hpp"
#include "Util/Input.hpp"

class FightSkillUI {
private:
    int m_ArrowCount;
    std::vector<std::shared_ptr<Text>> m_Skills;
    std::shared_ptr<Text> m_SkillInfo;
    std::shared_ptr<Image> m_FightSkillBG;
    std::shared_ptr<Image> m_Arrow;
public:
    FightSkillUI();

    [[nodiscard]] std::vector<std::shared_ptr<Util::GameObject>> GetChildren() const;

    void SetText(const std::vector<std::string> PokeSkill);

    void SetVisible(bool visible);

    void GetArrowCount(int SkillSize);

    bool Choose();

    int GetDecision();

    void ShowSkillInfo(const std::vector<std::string>&SkillType,const std::vector<std::string>&CurrentPP,const std::vector<std::string>&PP);
};

#endif //POKEMON_FIGHTSKILLUI_HPP
