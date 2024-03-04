#include "Text.hpp"

Text::Text(){
    SetText(" ");
    m_Transform.translation = {0.0F, -270.F};
}

void Text::SetText(const std::string &str) {
    SetDrawable(std::make_unique<Util::Text>(RESOURCE_DIR"/text.ttf",
                                             30,
                                             str,
                                             Util::Color::FromName(Util::Colors::BLACK)));
}

void Text::SetPosition(const glm::vec2 &Position)  { m_Transform.translation = Position; }