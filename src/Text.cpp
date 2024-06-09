#include "Text.hpp"

Text::Text() {
    SetText(" ");
    m_Transform.translation = {0.0F, -270.F};
}

std::string &Text::GetText() {
    return m_Text;
}

void Text::SetText(const std::string &str) {
    m_Text = str;
    SetDrawable(std::make_unique<Util::Text>(RESOURCE_DIR"/text.ttf",
                                             m_Size,
                                             m_Text,
                                             Util::Color::FromName(Util::Colors::BLACK)));
}

void Text::SetPosition(const glm::vec2 &Position) { m_Transform.translation = Position; }

void Text::SetSize(int size) {
    m_Size = size;
    SetText(m_Text);
}

const glm::vec2 &Text::GetPosition() const { return m_Transform.translation; }

bool Text::GetVisible() {
    return m_Visible;
}