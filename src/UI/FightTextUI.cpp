#include "UI/FightTextUI.hpp"

FightTextUI::FightTextUI(const std::shared_ptr<Character> &Player, const std::shared_ptr<Character> &Enemy) {
    m_PlayerTextBox = std::make_shared<TextBox>();
    m_PlayerTextBox->SetZIndex(60);
    m_PlayerTextBox->SetVisible(false);
    m_EnemyTextBox = std::make_shared<TextBox>();
    m_EnemyTextBox->SetZIndex(60);
    m_EnemyTextBox->SetVisible(false);
    m_DefeatTextBox = std::make_shared<TextBox>();
    m_DefeatTextBox->SetZIndex(60);
    m_DefeatTextBox->SetVisible(false);
    m_PokePackTextBox = std::make_shared<TextBox>();
    m_PokePackTextBox->SetZIndex(58);
    m_PokePackTextBox->SetVisible(false);
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
    m_ChangePokeTextBox = std::make_shared<TextBox>();
    m_ChangePokeTextBox->SetZIndex(60);
    m_ChangePokeTextBox->SetVisible(false);
    m_ChangeFailTextBox = std::make_shared<TextBox>();
    m_ChangeFailTextBox->SetZIndex(60);
    m_ChangeFailTextBox->SetVisible(false);
    m_LoseTextBox = std::make_shared<TextBox>();
    m_LoseTextBox->SetZIndex(60);
    m_LoseTextBox->SetVisible(false);
    m_Player = Player;
    m_Enemy = Enemy;
    m_DefeatWildTextBox = std::make_shared<TextBox>();
    m_DefeatWildTextBox->SetZIndex(60);
    m_DefeatWildTextBox->SetVisible(false);

}

std::vector<std::vector<std::shared_ptr<Util::GameObject>>> FightTextUI::GetChildren() const {
    return {m_PlayerTextBox->GetChildren(), m_EnemyTextBox->GetChildren(), m_FinishTextBox->GetChildren(),
            m_DefeatTextBox->GetChildren(), m_PokePackTextBox->GetChildren(), m_GainEXPTextBox->GetChildren(),
            m_RunTextBox->GetChildren(), m_LevelUPTextBox->GetChildren(), m_ChangePokeTextBox->GetChildren(),
            m_ChangeFailTextBox->GetChildren(), m_LoseTextBox->GetChildren(),m_DefeatWildTextBox->GetChildren()};
}

void FightTextUI::SetPlayer(int PokeIndex, int EnemyIndex, int SkillIndex) {
    std::vector<std::shared_ptr<Pokemon>> PlayerPokemons = m_Player->GetPokemonBag()->GetPokemons();
    std::string PokeName = PlayerPokemons[PokeIndex]->GetName();
    std::string UseSkill = PlayerPokemons[PokeIndex]->GetSkill()[SkillIndex];
    std::vector<std::string> EnemyType = m_Enemy->GetPokemonBag()->GetPokemons()[EnemyIndex]->GetType();
    float DamageRate = PokeFunction::TypeDamage(PlayerPokemons[PokeIndex]->GetSkillType()[SkillIndex],EnemyType) ;
    m_PlayerTextBox->SetVisible(true);
    m_PlayerTextBox->Reload();
    m_PlayerTextBox->AddText(PokeName + "使出了" + UseSkill);
    if (DamageRate == 0) {
        m_PlayerTextBox->AddText("沒有效果!");
    } else if (DamageRate >= 2.0) {
        m_PlayerTextBox->AddText("效果絕佳!");
    } else if (DamageRate <= 0.5) {
        m_PlayerTextBox->AddText("效果不好!");
    }
}

void FightTextUI::SetEnemy(int EnemyIndex, int PokeIndex, int SkillIndex) {
    std::vector<std::shared_ptr<Pokemon>> EnemyPokemons = m_Enemy->GetPokemonBag()->GetPokemons();
    std::string PokeName = EnemyPokemons[EnemyIndex]->GetName();
    std::string UseSkill = EnemyPokemons[EnemyIndex]->GetSkill()[SkillIndex];
    std::vector<std::string> PlayerType = m_Player->GetPokemonBag()->GetPokemons()[PokeIndex]->GetType();
    float DamageRate = PokeFunction::TypeDamage(EnemyPokemons[EnemyIndex]->GetSkillType()[SkillIndex],PlayerType); ;
    m_EnemyTextBox->SetVisible(true);
    m_EnemyTextBox->Reload();
    m_EnemyTextBox->AddText(PokeName + "使出了" + UseSkill);
    if (DamageRate == 0) {
        m_EnemyTextBox->AddText("沒有效果!");
    } else if (DamageRate >= 2.0) {
        m_EnemyTextBox->AddText("效果絕佳!");
    } else if (DamageRate <= 0.5) {
        m_EnemyTextBox->AddText("效果不好!");
    }
}

void FightTextUI::SetDefeatWild(int PokeIndex, int EnemyIndex, int EXP) {
    std::string PlayerPokeName = m_Player->GetPokemonBag()->GetPokemons()[PokeIndex]->GetName();
    std::string EnemyPokeName = m_Enemy->GetPokemonBag()->GetPokemons()[EnemyIndex]->GetName();
    m_DefeatWildTextBox->SetVisible(true);
    m_DefeatWildTextBox->Reload();
    m_DefeatWildTextBox->AddText("敵方" + EnemyPokeName + "被擊倒了!");
    m_DefeatWildTextBox->AddText(PlayerPokeName + "獲得了" + std::to_string(EXP) + "經驗值及基礎點數!");
}

bool FightTextUI::GetDefeatWildVisibility() const {
    return m_DefeatWildTextBox->GetVisibility();
}






void FightTextUI::SetDefeat(const std::string &PokeName) {
    m_DefeatTextBox->SetVisible(true);
    m_DefeatTextBox->Reload();
    m_DefeatTextBox->AddText("敵方" + PokeName + "被擊倒了!");
}

void FightTextUI::SetPokePack() {
    m_PokePackTextBox->SetVisible(true);
    m_PokePackTextBox->Reload();
    m_PokePackTextBox->AddText("要派出哪隻神奇寶貝上場?");
}

void FightTextUI::SetFinish(const std::string &Winner, const std::string &Loser) {
    m_FinishTextBox->SetVisible(true);
    m_FinishTextBox->Reload();
    m_FinishTextBox->AddText(Winner + "擊敗了" + Loser + "!");
}

void FightTextUI::SetGainEXP(const std::string &PokeName, int EXP) {
    m_GainEXPTextBox->SetVisible(true);
    m_GainEXPTextBox->Reload();
    m_GainEXPTextBox->AddText(PokeName + "獲得了" + std::to_string(EXP) + "經驗值及基礎點數!");
}

void FightTextUI::SetRun(bool isWildPokemon) {
    m_RunTextBox->SetVisible(true);
    m_RunTextBox->Reload();
    if (isWildPokemon) {
        m_RunTextBox->AddText("安全地逃跑了!");
    } else {
        m_RunTextBox->AddText("與訓練家的戰鬥不能逃離!");
    }

}

void FightTextUI::SetLevelUP(const std::string &PokeName, int NewLV) {
    m_LevelUPTextBox->SetVisible(true);
    m_LevelUPTextBox->Reload();
    m_LevelUPTextBox->AddText(PokeName + "升級到了等級" + std::to_string(NewLV) + "!");
}

void FightTextUI::SetChangePoke(const std::string &OldPokeName, const std::string &NewPokeName) {
    m_ChangePokeTextBox->SetVisible(true);
    m_ChangePokeTextBox->Reload();
    m_ChangePokeTextBox->AddText("回來吧!" + OldPokeName + "!");
    m_ChangePokeTextBox->AddText("上啊!" + NewPokeName + "!");
}

void FightTextUI::SetChangeFail(const std::string &PokeName) {
    m_ChangeFailTextBox->SetVisible(true);
    m_ChangeFailTextBox->Reload();
    m_ChangeFailTextBox->AddText(PokeName + "已經在場上了!");
}

void FightTextUI::SetLose(const std::string &PlayerName) {
    m_LoseTextBox->SetVisible(true);
    m_LoseTextBox->Reload();
    m_LoseTextBox->AddText(PlayerName + "沒有可使用的神奇寶貝!");
    m_LoseTextBox->AddText(PlayerName +"的眼前一片漆黑!");
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

bool FightTextUI::GetChangePokeVisibility() const {
    return m_ChangePokeTextBox->GetVisibility();
}

bool FightTextUI::GetChangeFailVisibility() const {
    return m_ChangeFailTextBox->GetVisibility();
}

bool FightTextUI::GetLoseVisibility() const {
    return m_LoseTextBox->GetVisibility();
}

void FightTextUI::Next() {
    if (m_PlayerTextBox->GetVisibility()) {
        m_PlayerTextBox->Next();
    } else if (m_EnemyTextBox->GetVisibility()) {
        m_EnemyTextBox->Next();
    } else if (m_DefeatTextBox->GetVisibility()) {
        m_DefeatTextBox->Next();
    } else if (m_GainEXPTextBox->GetVisibility()) {
        m_GainEXPTextBox->Next();
    } else if (m_RunTextBox->GetVisibility()) {
        m_RunTextBox->Next();
    } else if (m_LevelUPTextBox->GetVisibility()) {
        m_LevelUPTextBox->Next();
    } else if (m_ChangePokeTextBox->GetVisibility()) {
        m_ChangePokeTextBox->Next();
    } else if (m_ChangeFailTextBox->GetVisibility()) {
        m_ChangeFailTextBox->Next();
    } else if (m_PokePackTextBox->GetVisibility()){
        m_PokePackTextBox->Next();
    } else if (m_LoseTextBox->GetVisibility()) {
        m_LoseTextBox->Next();
    } else if (m_DefeatWildTextBox->GetVisibility()){
        m_DefeatWildTextBox->Next();
    }
}