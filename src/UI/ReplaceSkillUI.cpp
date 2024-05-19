#include "UI/ReplaceSkillUI.hpp"


ReplaceSkillUI::ReplaceSkillUI() {
    m_TextBox=std::make_shared<TextBox>();
    m_TextBox->SetZIndex(60);
    m_TextBox->SetVisible(false);
    m_TFBox=std::make_shared<TFBox>();
    m_TFBox->SetZIndex(60);
    m_TFBox->SetVisible(false);
}

std::vector<std::vector<std::shared_ptr<Util::GameObject>>> ReplaceSkillUI::GetChildren() const {
    return {m_TextBox->GetChildren(),m_TFBox->GetChildren()};
}

void ReplaceSkillUI::SetVisible(bool visible) {
    m_TextBox->SetVisible(visible);
    m_TFBox->SetVisibility(visible);
}

void ReplaceSkillUI::SetText(const std::string& PlayerPokemon, const std::string& NewSkill) {
    m_TextBox->SetVisible(true);
    m_TextBox->Reload();
    m_TextBox->AddText(PlayerPokemon+"學習到了"+NewSkill+"!");
    m_TextBox->AddText("但"+PlayerPokemon+"不能學習超過四個技能");
    m_TextBox->AddText("你要讓"+PlayerPokemon+"學習新技能並取代舊技能嗎?");
    m_TextBox->AddText("你要移除掉哪個技能?");
}

void ReplaceSkillUI::SetTextBoxVisible(bool visible) {
    m_TextBox->SetVisible(visible);
}

void ReplaceSkillUI::SetTFBoxVisible(bool visible) {
    m_TFBox->SetVisibility(visible);
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