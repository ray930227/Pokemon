#include "TextBox.hpp"
#include "Util/Root.hpp"
#include "Util/Input.hpp"
#include "Util/Text.hpp"
#include <fstream>

TextBox::TextBox() {
    m_BG = std::make_shared<Image>(RESOURCE_DIR"/Background/textbox.png");
    m_BG->SetPosition({0, -249});
    m_BG->SetZIndex(99);
    m_Text = std::make_shared<Text>();
    m_Text->SetPosition({0, -249});
    m_Text->SetZIndex(100);
}

size_t TextBox::GetLineIndex() {
    return m_LineIndex;
}

std::string TextBox::GetCurrentLine() {
    return m_AllText[m_LineIndex];
}

std::string TextBox::GetText() {
    return m_Text->GetText();
}

bool TextBox::GetVisibility() const {
    return m_BG->GetVisible();
}

std::vector<std::shared_ptr<Util::GameObject>> TextBox::GetChildren() const {
    return {m_BG, m_Text};
}

void TextBox::SetText(const std::string &str) {
    m_Text->SetText(str);
}

void TextBox::SetVisible(bool visible) {
    m_BG->SetVisible(visible);
    m_Text->SetVisible(visible);
}

void TextBox::SetScale(const glm::vec2 &scale) {
    m_BG->SetScale(scale);
}

void TextBox::SetPosition(const glm::vec2 &Position) {
    m_BG->SetPosition(Position);
    m_Text->SetPosition(Position);
}

void TextBox::SetZIndex(float index) {
    m_BG->SetZIndex(index);
    m_Text->SetZIndex(index + 1);
}

void TextBox::ReadLines(const std::string &LinesPath) {
    std::ifstream ifs(LinesPath, std::ios::in);
    std::string s;
    m_AllText.clear();
    while (std::getline(ifs, s)) {
        if (s.size() > 60) s.insert(s.begin() + (s.size() / 2 / 3 * 3), '\n');
        m_AllText.push_back(s);
    }
    ifs.close();
    SetText(m_AllText[0]);
    m_LineIndex = 1;
}

void TextBox::ReadLines(std::vector<std::string> &Lines) {
    m_AllText.clear();
    for (auto &i: Lines) {
        if (i.size() > 60) i.insert(i.begin() + (i.size() / 2 / 3 * 3), '\n');
        m_AllText.push_back(i);
    }
    SetText(m_AllText[0]);
    m_LineIndex = 1;
}

void TextBox::Next() {
    if (m_LineIndex < m_AllText.size()) {
        SetText(m_AllText[m_LineIndex]);
        m_LineIndex++;
    } else {
        SetVisible(false);
    }
}

void TextBox::InputString() {
    std::string tempStr = m_Text->GetText();
    if (Util::Input::IsKeyDown(Util::Keycode::A)) {
        if (tempStr == " ") tempStr = "A";
        else tempStr += "a";
    }
    if (Util::Input::IsKeyDown(Util::Keycode::B)) {
        if (tempStr == " ") tempStr = "B";
        else tempStr += "b";
    }
    if (Util::Input::IsKeyDown(Util::Keycode::C)) {
        if (tempStr == " ") tempStr = "C";
        else tempStr += "c";
    }
    if (Util::Input::IsKeyDown(Util::Keycode::D)) {
        if (tempStr == " ") tempStr = "D";
        else tempStr += "d";
    }
    if (Util::Input::IsKeyDown(Util::Keycode::E)) {
        if (tempStr == " ") tempStr = "E";
        else tempStr += "e";
    }
    if (Util::Input::IsKeyDown(Util::Keycode::F)) {
        if (tempStr == " ") tempStr = "F";
        else tempStr += "f";
    }
    if (Util::Input::IsKeyDown(Util::Keycode::G)) {
        if (tempStr == " ") tempStr = "G";
        else tempStr += "g";
    }
    if (Util::Input::IsKeyDown(Util::Keycode::H)) {
        if (tempStr == " ") tempStr = "H";
        else tempStr += "h";
    }
    if (Util::Input::IsKeyDown(Util::Keycode::I)) {
        if (tempStr == " ") tempStr = "I";
        else tempStr += "i";
    }
    if (Util::Input::IsKeyDown(Util::Keycode::J)) {
        if (tempStr == " ") tempStr = "J";
        else tempStr += "j";
    }
    if (Util::Input::IsKeyDown(Util::Keycode::K)) {
        if (tempStr == " ") tempStr = "K";
        else tempStr += "k";
    }
    if (Util::Input::IsKeyDown(Util::Keycode::L)) {
        if (tempStr == " ") tempStr = "L";
        else tempStr += "l";
    }
    if (Util::Input::IsKeyDown(Util::Keycode::M)) {
        if (tempStr == " ") tempStr = "M";
        else tempStr += "m";
    }
    if (Util::Input::IsKeyDown(Util::Keycode::N)) {
        if (tempStr == " ") tempStr = "N";
        else tempStr += "n";
    }
    if (Util::Input::IsKeyDown(Util::Keycode::O)) {
        if (tempStr == " ") tempStr = "O";
        else tempStr += "o";
    }
    if (Util::Input::IsKeyDown(Util::Keycode::P)) {
        if (tempStr == " ") tempStr = "P";
        else tempStr += "p";
    }
    if (Util::Input::IsKeyDown(Util::Keycode::Q)) {
        if (tempStr == " ") tempStr = "Q";
        else tempStr += "q";
    }
    if (Util::Input::IsKeyDown(Util::Keycode::R)) {
        if (tempStr == " ") tempStr = "R";
        else tempStr += "r";
    }
    if (Util::Input::IsKeyDown(Util::Keycode::S)) {
        if (tempStr == " ") tempStr = "S";
        else tempStr += "s";
    }
    if (Util::Input::IsKeyDown(Util::Keycode::T)) {
        if (tempStr == " ") tempStr = "T";
        else tempStr += "t";
    }
    if (Util::Input::IsKeyDown(Util::Keycode::U)) {
        if (tempStr == " ") tempStr = "U";
        else tempStr += "u";
    }
    if (Util::Input::IsKeyDown(Util::Keycode::V)) {
        if (tempStr == " ") tempStr = "V";
        else tempStr += "v";
    }
    if (Util::Input::IsKeyDown(Util::Keycode::W)) {
        if (tempStr == " ") tempStr = "W";
        else tempStr += "w";
    }
    if (Util::Input::IsKeyDown(Util::Keycode::X)) {
        if (tempStr == " ") tempStr = "X";
        else tempStr += "x";
    }
    if (Util::Input::IsKeyDown(Util::Keycode::Y)) {
        if (tempStr == " ") tempStr = "Y";
        else tempStr += "y";
    }
    if (Util::Input::IsKeyDown(Util::Keycode::Z)) {
        if (tempStr == " ") tempStr = "Z";
        else tempStr += "z";
    }
    if (Util::Input::IsKeyDown(Util::Keycode::BACKSPACE)) {
        if (tempStr.size() <= 1) tempStr = " ";
        else tempStr.pop_back();
    }

    m_Text->SetText(tempStr);
}

void TextBox::AddText(const std::string &str) {
    auto s = str;
    if (s.size() > 60) s.insert(s.begin() + (s.size() / 2 / 3 * 3), '\n');
    m_AllText.push_back(s);
    SetText(m_AllText[0]);
    m_LineIndex = 1;
}

void TextBox::Reload() {
    m_AllText.clear();
    m_LineIndex = 0;
}

int TextBox::GetSize() {
    return m_AllText.size();
}