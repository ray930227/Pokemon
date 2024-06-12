#include "UI/PokeFaintedUI.hpp"

PokeFaintedUI::PokeFaintedUI() {
    m_TextBox = std::make_shared<TextBox>();
    m_TextBox->SetZIndex(60);
    m_TextBox->SetVisible(false);
    m_TFBox = std::make_shared<TFBox>();
    m_TFBox->SetZIndex(60);
    m_TFBox->SetVisible(false);
}

std::vector<std::vector<std::shared_ptr<Util::GameObject>>> PokeFaintedUI::GetChildren() const {
    return {m_TextBox->GetChildren(), m_TFBox->GetChildren()};
}

void PokeFaintedUI::SetVisible(bool visible) {
    m_TextBox->SetVisible(visible);
    m_TFBox->SetVisible(visible);
}

void PokeFaintedUI::SetText(const std::string &PokeName) {
    m_TextBox->SetVisible(true);
    m_TextBox->Reload();
    m_TextBox->AddText(PokeName + "昏厥了!");
    m_TextBox->AddText("使用下一隻神奇寶貝?");
}

void PokeFaintedUI::SetTextBoxVisible(bool visible) {
    m_TextBox->SetVisible(visible);
}

void PokeFaintedUI::SetTFBoxVisible(bool visible) {
    m_TFBox->SetVisible(visible);
}

void PokeFaintedUI::Next() {
    m_TextBox->Next();
}

size_t PokeFaintedUI::GetCurrentIndex() {
    return m_TextBox->GetLineIndex();
}

bool PokeFaintedUI::TFBoxChoose() {
    return m_TFBox->Choose();
}

bool PokeFaintedUI::GetTF() {
    return m_TFBox->GetTF();
}

bool PokeFaintedUI::GetVisibility() const {
    return m_TextBox->GetVisibility();
}