#include "TextBox.hpp"
#include "Util/Root.hpp"
#include "Util/Input.hpp"
#include "Util/Text.hpp"
#include <fstream>

TextBox::TextBox(){
    m_BG=std::make_shared<Object>(RESOURCE_DIR"/Background/textbox.png");
    m_BG->SetPosition({0,-249});
    m_BG->SetZIndex(99);
    m_Text=std::make_shared<Object>(std::make_unique<Util::Text>(RESOURCE_DIR"/text.ttf", 20,
                                                                 " ",
                                                                 Util::Color::FromName(Util::Colors::BLACK)));
    m_Text->SetPosition({0,-249});
    m_Text->SetZIndex(100);
}

size_t TextBox::GetLineIndex() {
    return m_LineIndex;
}

std::string TextBox::GetCurrentLine() {
    return m_AllText[m_LineIndex];
}

bool TextBox::GetVisibility() const {
    return m_BG->GetVisibility();
}

void TextBox::SetText(const std::string &str){
    m_Text->SetDrawable(std::make_unique<Util::Text>(RESOURCE_DIR"/text.ttf", 30,
                                                     str,
                                                     Util::Color::FromName(Util::Colors::BLACK)));
}

void TextBox::SetVisible(bool visible) {
    m_BG->SetVisible(visible);
    m_Text->SetVisible(visible);
}

void TextBox::SetScale(const glm::vec2 &scale) {
    m_BG->SetScale(scale);
}

void TextBox::SetPosition(const glm::vec2 &Position)  {
    m_BG->SetPosition(Position);
    m_Text->SetPosition(Position);
}

void TextBox::ReadLines(const std::string &LinesPath) {
    std::ifstream ifs(LinesPath, std::ios::in);
    std::string s;
    while (std::getline(ifs, s)) {
        if(s.size()>60) s.insert(s.begin()+(s.size()/2/3*3),'\n');
        m_AllText.push_back(s);
    }
    ifs.close();
    SetText(m_AllText[0]);
    m_LineIndex=1;
}

void TextBox::Next() {
    if(m_LineIndex<m_AllText.size()){
        SetText(m_AllText[m_LineIndex]);
        m_LineIndex++;
    }
    else{
        SetVisible(false);
    }
}

std::vector<std::shared_ptr<Util::GameObject>> TextBox::GetChildren() const{
    return {m_BG,m_Text};
}
