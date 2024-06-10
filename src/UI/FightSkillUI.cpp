#include "UI/FightSkillUI.hpp"

FightSkillUI::FightSkillUI(const std::shared_ptr<Character> &Player) {
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
    m_Player = Player;
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

void FightSkillUI::SetText(unsigned long long int PokeIndex) {
    std::vector<std::string> PokeSkill = m_Player->GetPokemonBag()->GetPokemons()[PokeIndex]->GetSkill();
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
//    m_Arrow->SetPosition({-170, -190});
    m_FightSkillBG->SetVisible(visible);
}

bool FightSkillUI::Choose(unsigned long long int PokeIndex) {
    int SkillSize = m_Player->GetPokemonBag()->GetPokemons()[PokeIndex]->GetSkill().size();
    if (Util::Input::IsKeyDown(Util::Keycode::UP) && m_Arrow->GetPosition().y < -190) {
        m_Arrow->SetPosition({-170, m_Arrow->GetPosition().y + 40});
    } else if (Util::Input::IsKeyDown(Util::Keycode::DOWN) &&
               m_Arrow->GetPosition().y >
               (-190 - (40 * (SkillSize - 1)))) {
        m_Arrow->SetPosition({-170, m_Arrow->GetPosition().y - 40});
    }
    if (Util::Input::IsKeyDown(Util::Keycode::Z)) {
        return true;
    }
    return false;
}

int FightSkillUI::GetDecision() {
    return ((-m_Arrow->GetPosition().y) - 190) / 40;
}

void FightSkillUI::ShowSkillInfo(unsigned long long int PokeIndex) {
    std::shared_ptr<Pokemon> Pokemon = m_Player->GetPokemonBag()->GetPokemons()[PokeIndex];
    std::vector<std::string> SkillType = Pokemon->GetSkillType();
    std::vector<std::string> CurrentPP = Pokemon->GetCurrentSkillPP();
    std::vector<std::string> PP = Pokemon->GetSkillPP();
    int Index = ((-m_Arrow->GetPosition().y) - 190) / 40;
    m_SkillInfo->SetText(
            "型態:" + SkillType[Index] + "\n" + CurrentPP[Index] + " / " + PP[Index]);
}

void FightSkillUI::ReSetArrow() {
    m_Arrow->SetPosition({-170, -190});
}