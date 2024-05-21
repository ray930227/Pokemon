#include "UI/FightTextUI.hpp"

FightTextUI::FightTextUI() {
    m_PlayerTextBox=std::make_shared<TextBox>();
    m_PlayerTextBox->SetZIndex(60);
    m_PlayerTextBox->SetVisible(false);
    m_EnemyTextBox=std::make_shared<TextBox>();
    m_EnemyTextBox->SetZIndex(60);
    m_EnemyTextBox->SetVisible(false);
}

std::vector<std::vector<std::shared_ptr<Util::GameObject>>> FightTextUI::GetChildren() const {
    return {m_PlayerTextBox->GetChildren(),m_EnemyTextBox->GetChildren()};
}

void FightTextUI::SetPlayer(const std::string& PokeName, const std::string& UseSkill,float DamageRate) {
    m_PlayerTextBox->SetVisible(true);
    m_PlayerTextBox->Reload();
    m_PlayerTextBox->AddText(PokeName + "使出了" + UseSkill);
    if (DamageRate>=2.0){
        m_PlayerTextBox->AddText("效果絕佳!");
    }
    else if (DamageRate<=0.5){
        m_PlayerTextBox->AddText("效果不好!");
    }
}

void FightTextUI::SetEnemy(const std::string &EnemyName, const std::string &UseSkill, float DamageRate) {
    m_EnemyTextBox->SetVisible(true);
    m_EnemyTextBox->Reload();
    m_EnemyTextBox->AddText(EnemyName + "使出了" + UseSkill);
    if (DamageRate>=2.0){
        m_EnemyTextBox->AddText("效果絕佳!");
    }
    else if (DamageRate<=0.5){
        m_EnemyTextBox->AddText("效果不好!");
    }
}

bool FightTextUI::GetPlayerVisibility() const {
    return m_PlayerTextBox->GetVisibility();
}

bool FightTextUI::GetEnemyVisibility() const {
    return m_EnemyTextBox->GetVisibility();
}

void FightTextUI::Next() {
    if (m_PlayerTextBox->GetVisibility()){
        m_PlayerTextBox->Next();
    }
    else if(m_EnemyTextBox->GetVisibility()){
        m_EnemyTextBox->Next();
    }
}