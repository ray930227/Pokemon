#include "UI/FightSkillUI.hpp"

FightSkillUI::FightSkillUI() {
    for (size_t i = 0; i < 4; i++) {
        m_Skills.push_back(std::make_shared<Text>());
        m_Skills[i]->SetZIndex(55);
        m_Skills[i]->SetVisible(false);
    }
    m_SkillInfo = std::make_shared<Text>();
    m_SkillInfo->SetZIndex(55);
    m_SkillInfo->SetVisible(false);
    m_SkillInfo->SetPosition({-150, -60});
    m_Arrow = std::make_shared<Image>(RESOURCE_DIR"/Fight/arrow.png");
    m_Arrow->SetZIndex(55);
    m_Arrow->SetVisible(false);
    m_Arrow->SetPosition({-170, -190});
    m_FightSkillBG = std::make_shared<Image>(RESOURCE_DIR"/Fight/Fightskillbox.png");
    m_FightSkillBG->SetZIndex(54);
    m_FightSkillBG->SetVisible(false);
    m_ArrowCount = 0;
}

std::vector<std::shared_ptr<Util::GameObject>> FightSkillUI::GetChildren() const {
    std::vector<std::shared_ptr<Util::GameObject>> temp;
    for (const auto &Skill: m_Skills) {
        temp.push_back(Skill);
    }
    temp.push_back(m_SkillInfo);
    temp.push_back(m_Arrow);
    temp.push_back(m_FightSkillBG);
    return temp;
}

void FightSkillUI::SetText(const std::vector<std::string> PokeSkill) {
    int SkillNum = PokeSkill.size();
    for (size_t i = 0; i < SkillNum; i++) {
        m_Skills[i]->SetText(PokeSkill[i]);
    }
    int SkillOfY = -190;
    for (size_t i = 0; i < 4; i++) {
        m_Skills[i]->SetPosition({((PokeSkill[i].length() / 3 - 1) * 16), SkillOfY});
        m_Skills[i]->SetPosition({m_Skills[i]->GetPosition().x - 120, SkillOfY});
        SkillOfY -= 40;
    }
}


void FightSkillUI::SetVisible(bool visible) {
    for (size_t i = 0; i < 4; i++) {
        m_Skills[i]->SetVisible(visible);
    }
    m_SkillInfo->SetVisible(visible);
    m_Arrow->SetVisible(visible);
    m_Arrow->SetPosition({-170, -190});
    m_FightSkillBG->SetVisible(visible);
}

void FightSkillUI::GetArrowCount(int SkillSize) {
    m_ArrowCount = SkillSize;
}

bool FightSkillUI::Choose() {
    if (Util::Input::IsKeyDown(Util::Keycode::UP) && m_Arrow->GetPosition().y != -190) {
        m_Arrow->SetPosition({-170, m_Arrow->GetPosition().y + 40});
        m_ArrowCount++;
    } else if (Util::Input::IsKeyDown(Util::Keycode::DOWN) && m_ArrowCount != 1) {
        m_Arrow->SetPosition({-170, m_Arrow->GetPosition().y - 40});
        m_ArrowCount--;
    }
    if (Util::Input::IsKeyDown(Util::Keycode::Z)) {
        return true;
    }
    return false;
}

int FightSkillUI::GetDecision() {
    if (m_Arrow->GetPosition().y == -190) {
        return 0;
    } else if (m_Arrow->GetPosition().y == -230) {
        return 1;
    } else if (m_Arrow->GetPosition().y == -270) {
        return 2;
    } else if (m_Arrow->GetPosition().y == -310) {
        return 3;
    }
    return -1;
}

void FightSkillUI::ShowSkillInfo(const std::vector<std::string> &SkillType, const std::vector<std::string> &CurrentPP,
                                 const std::vector<std::string> &PP) {
    if (m_Arrow->GetPosition().y == -190) {
        m_SkillInfo->SetText(
                "型態:" + SkillType[0] + "\n" + CurrentPP[0] + " / " + PP[0]);
    } else if (m_Arrow->GetPosition().y == -230) {
        m_SkillInfo->SetText(
                "型態:" + SkillType[1] + "\n" + CurrentPP[1] + " / " + PP[1]);
    } else if (m_Arrow->GetPosition().y == -270) {
        m_SkillInfo->SetText(
                "型態:" + SkillType[2] + "\n" + CurrentPP[2] + " / " + PP[2]);
    } else if (m_Arrow->GetPosition().y == -310) {
        m_SkillInfo->SetText(
                "型態:" + SkillType[3] + "\n" + CurrentPP[3] + " / " + PP[3]);
    }
}
