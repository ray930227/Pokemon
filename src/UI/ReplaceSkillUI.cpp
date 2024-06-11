#include "UI/ReplaceSkillUI.hpp"


ReplaceSkillUI::ReplaceSkillUI(const std::shared_ptr<Character> &Player) {
    m_TextBox = std::make_shared<TextBox>();
    m_TextBox->SetZIndex(60);
    m_TextBox->SetVisible(false);
    m_TFBox = std::make_shared<TFBox>();
    m_TFBox->SetZIndex(60);
    m_TFBox->SetVisible(false);
    m_Player=Player;
}

std::vector<std::vector<std::shared_ptr<Util::GameObject>>> ReplaceSkillUI::GetChildren() const {
    return {m_TextBox->GetChildren(), m_TFBox->GetChildren()};
}

void ReplaceSkillUI::Run() {
    if (m_TextBox->GetSize()>1){
        if (!m_TFBox->GetVisible()){
            if (Util::Input::IsKeyDown(Util::Keycode::Z)){
                if (m_TextBox->GetLineIndex()==2){
                    m_TFBox->SetVisible(true);
                }
                m_TextBox->Next();
            }
        } else{
            if (m_TFBox->Choose()){
                m_TFBox->SetVisible(false);
                if (m_TFBox->GetTF()){
                    m_TextBox->Next();
                }
                else{
                    SetVisible(false);
                }
            }
        }
    } else{
        if (Util::Input::IsKeyDown(Util::Keycode::Z)){
            m_TextBox->Next();
        }
        if (!m_TextBox->GetVisibility()){
            SetVisible(false);
        }
    }
}

void ReplaceSkillUI::SetVisible(bool visible) {
    m_TextBox->SetVisible(visible);
    m_TFBox->SetVisible(visible);
}

void ReplaceSkillUI::SetText(int PokeIndex) {
    std::shared_ptr<Pokemon> PlayerPokemon=m_Player->GetPokemonBag()->GetPokemons()[PokeIndex];
    std::string PokeName = PlayerPokemon->GetName();
    std::string NewSkill=PlayerPokemon->NewSkill();
    m_TextBox->SetVisible(true);
    m_TextBox->Reload();
    m_TextBox->AddText(PokeName + "學習到了" + NewSkill + "!");
    if (PlayerPokemon->IsSkillFull()){
        m_TextBox->AddText("但" + PokeName + "不能學習超過四個技能");
        m_TextBox->AddText("你要讓" + PokeName + "學習新技能並取代舊技能嗎?");
        m_TextBox->AddText("你要移除掉哪個技能?");
    }
}

void ReplaceSkillUI::SetTextBoxVisible(bool visible) {
    m_TextBox->SetVisible(visible);
}

void ReplaceSkillUI::SetTFBoxVisible(bool visible) {
    m_TFBox->SetVisible(visible);
}

void ReplaceSkillUI::Next() {
    m_TextBox->Next();
}

size_t ReplaceSkillUI::GetCurrentIndex() {
    return m_TextBox->GetLineIndex();
}

bool ReplaceSkillUI::TFBoxChoose() {
    return m_TFBox->Choose();
}

bool ReplaceSkillUI::GetTF() {
    return m_TFBox->GetTF();
}

bool ReplaceSkillUI::GetVisibility() const {
    return m_TextBox->GetVisibility();
}