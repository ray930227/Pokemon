#include "UI/FightTextUI.hpp"

FightTextUI::FightTextUI(const std::shared_ptr<Character> &Player, const std::shared_ptr<Character> &Enemy) {
    m_TB = std::make_shared<TextBox>();
    m_TB->SetZIndex(58);
    m_TB->SetVisible(false);
    m_Player = Player;
    m_Enemy = Enemy;

}

std::vector<std::vector<std::shared_ptr<Util::GameObject>>> FightTextUI::GetChildren() const {
    return {m_TB->GetChildren()};
}

void FightTextUI::SetPlayer(int PokeIndex, int EnemyIndex, int SkillIndex) {
    std::vector<std::shared_ptr<Pokemon>> PlayerPokemons = m_Player->GetPokemonBag()->GetPokemons();
    std::string PokeName = PlayerPokemons[PokeIndex]->GetName();
    std::string UseSkill;
    std::vector<std::string> EnemyType = m_Enemy->GetPokemonBag()->GetPokemons()[EnemyIndex]->GetType();
    float DamageRate;
    if (SkillIndex == 4) {
        UseSkill = "掙扎";
        DamageRate = 1;
    } else {
        UseSkill = PlayerPokemons[PokeIndex]->GetSkill()[SkillIndex];
        DamageRate = PokeFunction::TypeDamage(PlayerPokemons[PokeIndex]->GetSkillType()[SkillIndex], EnemyType);

    }
    m_TB->SetVisible(true);
    m_TB->Reload();
    m_TB->AddText(PokeName + "使出了" + UseSkill);
    if (SkillIndex != 4 && m_Player->GetPokemonBag()->GetPokemons()[PokeIndex]->GetSkillClass()[SkillIndex] != "變化") {
        if (DamageRate == 0) {
            m_TB->AddText("沒有效果!");
        } else if (DamageRate >= 2.0) {
            m_TB->AddText("效果絕佳!");
        } else if (DamageRate <= 0.5) {
            m_TB->AddText("效果不好!");
        }
    }

}

void FightTextUI::SetEnemy(int EnemyIndex, int PokeIndex, int SkillIndex) {
    std::vector<std::shared_ptr<Pokemon>> EnemyPokemons = m_Enemy->GetPokemonBag()->GetPokemons();
    std::string PokeName = EnemyPokemons[EnemyIndex]->GetName();
    std::string UseSkill;
    std::vector<std::string> EnemyType = m_Player->GetPokemonBag()->GetPokemons()[PokeIndex]->GetType();
    float DamageRate;
    if (SkillIndex == 4) {
        UseSkill = "掙扎";
        DamageRate = 1;
    } else {
        UseSkill = EnemyPokemons[EnemyIndex]->GetSkill()[SkillIndex];
        DamageRate = PokeFunction::TypeDamage(EnemyPokemons[EnemyIndex]->GetSkillType()[SkillIndex], EnemyType);
    }
    m_TB->SetVisible(true);
    m_TB->Reload();
    m_TB->AddText(PokeName + "使出了" + UseSkill);
    if (SkillIndex != 4 && m_Enemy->GetPokemonBag()->GetPokemons()[EnemyIndex]->GetSkillClass()[SkillIndex] != "變化") {
        if (DamageRate == 0) {
            m_TB->AddText("沒有效果!");
        } else if (DamageRate >= 2.0) {
            m_TB->AddText("效果絕佳!");
        } else if (DamageRate <= 0.5) {
            m_TB->AddText("效果不好!");
        }
    }
}

void FightTextUI::SetDefeatWild(int PokeIndex, int EnemyIndex, int EXP) {
    std::string PlayerPokeName = m_Player->GetPokemonBag()->GetPokemons()[PokeIndex]->GetName();
    std::string EnemyPokeName = m_Enemy->GetPokemonBag()->GetPokemons()[EnemyIndex]->GetName();
    m_TB->SetVisible(true);
    m_TB->Reload();
    m_TB->AddText("敵方" + EnemyPokeName + "被擊倒了!");
    m_TB->AddText(PlayerPokeName + "獲得了" + std::to_string(EXP) + "經驗值及基礎點數!");
}

void FightTextUI::SetDefeat(const std::string &PokeName) {
    m_TB->SetVisible(true);
    m_TB->Reload();
    m_TB->AddText("敵方" + PokeName + "被擊倒了!");
}

void FightTextUI::SetPokePack() {
    m_TB->SetVisible(true);
    m_TB->Reload();
    m_TB->AddText("要派出哪隻神奇寶貝上場?");
}

void FightTextUI::SetFinish(const std::string &Winner, const std::string &Loser) {
    m_TB->SetVisible(true);
    m_TB->Reload();
    m_TB->AddText(Winner + "擊敗了" + Loser + "!");
}

void FightTextUI::SetGainEXP(const std::string &PokeName, int EXP) {
    m_TB->SetVisible(true);
    m_TB->Reload();
    m_TB->AddText(PokeName + "獲得了" + std::to_string(EXP) + "經驗值及基礎點數!");
}

void FightTextUI::SetRun(bool isWildPokemon) {
    m_TB->SetVisible(true);
    m_TB->Reload();
    if (isWildPokemon) {
        m_TB->AddText("安全地逃跑了!");
    } else {
        m_TB->AddText("與訓練家的戰鬥不能逃離!");
    }

}

void FightTextUI::SetLevelUP(const std::string &PokeName, int NewLV) {
    m_TB->SetVisible(true);
    m_TB->Reload();
    m_TB->AddText(PokeName + "升級到了等級" + std::to_string(NewLV) + "!");
}

void FightTextUI::SetChangePoke(const std::string &OldPokeName, const std::string &NewPokeName) {
    m_TB->SetVisible(true);
    m_TB->Reload();
    m_TB->AddText("回來吧!" + OldPokeName + "!");
    m_TB->AddText("上啊!" + NewPokeName + "!");
}

void FightTextUI::SetChangeFail(const std::string &PokeName) {
    m_TB->SetVisible(true);
    m_TB->Reload();
    m_TB->AddText(PokeName + "已經在場上了!");
}

void FightTextUI::SetLose(const std::string &PlayerName) {
    m_TB->SetVisible(true);
    m_TB->Reload();
    m_TB->AddText(PlayerName + "沒有可使用的神奇寶貝!");
    m_TB->AddText(PlayerName + "的眼前一片漆黑!");
}

void FightTextUI::SetNoHit(const std::string &PokeName) {
    m_TB->SetVisible(true);

    auto temp = m_TB->GetText();
    m_TB->Reload();
    m_TB->AddText(temp);
    m_TB->AddText("技能沒有命中!");
}

void FightTextUI::SetCatch() {
    m_TB->SetVisible(true);
    m_TB->Reload();
    m_TB->AddText("與訓練家的戰鬥不能使用精靈球!");
}

void FightTextUI::SetPPRunOut(int PokeIndex, int SkillIndex) {
    m_TB->SetVisible(true);
    m_TB->Reload();
    m_TB->AddText(m_Player->GetPokemonBag()->GetPokemons()[PokeIndex]->GetSkill()[SkillIndex] + "的招式點數已用完!!");
}

void FightTextUI::AddText(const std::string &Text) {
    m_TB->AddText(Text);
}

bool FightTextUI::GetTBVisibility() const {
    return m_TB->GetVisibility();
}

void FightTextUI::Next() {
    if (m_TB->GetVisibility()) {
        m_TB->Next();
    }
}