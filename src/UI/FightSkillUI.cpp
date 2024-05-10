#include "UI/FightSkillUI.hpp"

FightSkillUI::FightSkillUI() {
    for (size_t i = 0; i < 4; i++) {
        m_Skills.push_back(std::make_shared<Text>());
        m_Skills[i]->SetZIndex(55);
        m_Skills[i]->SetVisible(false);
    }
}

std::vector<std::shared_ptr<Util::GameObject>> FightSkillUI::GetChildren() const {
    std::vector<std::shared_ptr<Util::GameObject>> temp;
    for (const auto &Skill: m_Skills) {
        temp.push_back(Skill);
    }
    return temp;
}

void FightSkillUI::SetText(const std::vector<std::string> PokeSkill) {
    int SkillNum = PokeSkill.size();
    for (size_t i = 0; i < SkillNum; i++) {
        m_Skills[i]->SetText(PokeSkill[i]);
    }
    int SkillOfY = -190;
    for (size_t i = 0; i < 4; i++) {
        m_Skills[i]->SetPosition({(PokeSkill[i].length() / 4 * 17), SkillOfY});
        m_Skills[i]->SetPosition({m_Skills[i]->GetPosition().x - 120, SkillOfY});
        SkillOfY -= 40;
    }
}

void FightSkillUI::SetVisible(bool visible) {
    for (size_t i = 0; i < 4; i++) {
        m_Skills[i]->SetVisible(visible);
    }
}