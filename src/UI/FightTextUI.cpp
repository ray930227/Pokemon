#include "UI/FightTextUI.hpp"

FightTextUI::FightTextUI() {
    m_PlayerTextBox = std::make_shared<TextBox>();
    m_PlayerTextBox->SetZIndex(60);
    m_PlayerTextBox->SetVisible(false);
    m_EnemyTextBox = std::make_shared<TextBox>();
    m_EnemyTextBox->SetZIndex(60);
    m_EnemyTextBox->SetVisible(false);
    m_DefeatTextBox = std::make_shared<TextBox>();
    m_DefeatTextBox->SetZIndex(60);
    m_DefeatTextBox->SetVisible(false);
    m_LoseTextBox = std::make_shared<TextBox>();
    m_LoseTextBox->SetZIndex(60);
    m_LoseTextBox->SetVisible(false);
    m_FinishTextBox = std::make_shared<TextBox>();
    m_FinishTextBox->SetZIndex(60);
    m_FinishTextBox->SetVisible(false);
    m_GainEXPTextBox = std::make_shared<TextBox>();
    m_GainEXPTextBox->SetZIndex(60);
    m_GainEXPTextBox->SetVisible(false);
    m_RunTextBox = std::make_shared<TextBox>();
    m_RunTextBox->SetZIndex(60);
    m_RunTextBox->SetVisible(false);
    m_LevelUPTextBox = std::make_shared<TextBox>();
    m_LevelUPTextBox->SetZIndex(60);
    m_LevelUPTextBox->SetVisible(false);
}

std::vector<std::vector<std::shared_ptr<Util::GameObject>>> FightTextUI::GetChildren() const {
    return {m_PlayerTextBox->GetChildren(), m_EnemyTextBox->GetChildren(), m_FinishTextBox->GetChildren(),
            m_DefeatTextBox->GetChildren(), m_LoseTextBox->GetChildren(), m_GainEXPTextBox->GetChildren(),
            m_RunTextBox->GetChildren(),m_LevelUPTextBox->GetChildren()};
}

void FightTextUI::SetPlayer(const std::string &PokeName, const std::string &UseSkill, float DamageRate) {
    m_PlayerTextBox->SetVisible(true);
    m_PlayerTextBox->Reload();
    m_PlayerTextBox->AddText(PokeName + "使出了" + UseSkill);
    if (DamageRate >= 2.0) {
        m_PlayerTextBox->AddText("效果絕佳!");
    } else if (DamageRate <= 0.5) {
        m_PlayerTextBox->AddText("效果不好!");
    }
}

void FightTextUI::SetEnemy(const std::string &EnemyName, const std::string &UseSkill, float DamageRate) {
    m_EnemyTextBox->SetVisible(true);
    m_EnemyTextBox->Reload();
    m_EnemyTextBox->AddText(EnemyName + "使出了" + UseSkill);
    if (DamageRate >= 2.0) {
        m_EnemyTextBox->AddText("效果絕佳!");
    } else if (DamageRate <= 0.5) {
        m_EnemyTextBox->AddText("效果不好!");
    }
}

void FightTextUI::SetDefeat(const std::string &PokeName) {
    m_DefeatTextBox->SetVisible(true);
    m_DefeatTextBox->Reload();
    m_DefeatTextBox->AddText("敵方" + PokeName + "被擊倒了!");
}

void FightTextUI::SetLose(const std::string &PlayerName) {
    m_LoseTextBox->SetVisible(true);
    m_LoseTextBox->Reload();
}

void FightTextUI::SetFinish(const std::string &Winner, const std::string &Loser) {
    m_FinishTextBox->SetVisible(true);
    m_FinishTextBox->Reload();
    m_FinishTextBox->AddText(Winner + "擊敗了" + Loser + "!");
}

void FightTextUI::SetGainEXP(const std::string &PokeName, int EXP) {
    m_GainEXPTextBox->SetVisible(true);
    m_GainEXPTextBox->Reload();
    m_GainEXPTextBox->AddText(PokeName+"獲得了"+std::to_string(EXP)+"經驗值");
}

void FightTextUI::SetRun() {
    m_RunTextBox->SetVisible(true);
    m_RunTextBox->Reload();
    m_RunTextBox->AddText("安全地逃跑了!");
}

void FightTextUI::SetLevelUP(const std::string &PokeName, int NewLV) {
    m_LevelUPTextBox->SetVisible(true);
    m_LevelUPTextBox->Reload();
    m_LevelUPTextBox->AddText(PokeName+"升級到了等級"+std::to_string(NewLV)+"!");
}

bool FightTextUI::GetPlayerVisibility() const {
    return m_PlayerTextBox->GetVisibility();
}

bool FightTextUI::GetEnemyVisibility() const {
    return m_EnemyTextBox->GetVisibility();
}

bool FightTextUI::GetDefeatVisibility() const {
    return m_DefeatTextBox->GetVisibility();
}

bool FightTextUI::GetGainEXPVisibility() const {
    return m_GainEXPTextBox->GetVisibility();
}

bool FightTextUI::GetRunVisibility() const {
    return m_RunTextBox->GetVisibility();
}

bool FightTextUI::GetLevelUPVisibility() const {
    return m_LevelUPTextBox->GetVisibility();
}

void FightTextUI::Next() {
    if (m_PlayerTextBox->GetVisibility()) {
        m_PlayerTextBox->Next();
    } else if (m_EnemyTextBox->GetVisibility()) {
        m_EnemyTextBox->Next();
    } else if (m_DefeatTextBox->GetVisibility()) {
        m_DefeatTextBox->Next();
    } else if (m_GainEXPTextBox->GetVisibility()){
        m_GainEXPTextBox->Next();
    } else if (m_RunTextBox->GetVisibility()){
        m_RunTextBox->Next();
    } else if (m_LevelUPTextBox->GetVisibility()){
        m_LevelUPTextBox->Next();
    }
}