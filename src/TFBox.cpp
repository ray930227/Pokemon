#include "TFBox.hpp"

TFBox::TFBox() {
    m_Box = std::make_shared<Image>(RESOURCE_DIR"/Background/TFBox.png");
    m_Arrow = std::make_shared<Image>(RESOURCE_DIR"/Fight/arrow.png");
    m_Box->SetZIndex(98);
    m_Arrow->SetZIndex(99);
    SetVisible(false);
    SetPosition({247.5, -27});
}

bool TFBox::GetVisible() const {
    return m_Box->GetVisible();
}

const glm::vec2 &TFBox::GetPosition() const {
    return m_Box->GetPosition();
}

std::vector<std::shared_ptr<Util::GameObject>> TFBox::GetChildren() const {
    return {m_Arrow, m_Box};
}

bool TFBox::GetTF() {
    return m_Arrow->GetPosition().y == m_Box->GetPosition().y + 37;
}

void TFBox::SetVisible(const bool visible) {
    m_Box->SetVisible(visible);
    m_Arrow->SetVisible(visible);
    if (visible) m_Arrow->SetPosition({m_Arrow->GetPosition().x, m_Box->GetPosition().y + 37});
}

void TFBox::SetPosition(const glm::vec2 &Position) {
    m_Box->SetPosition(Position);
    m_Arrow->SetPosition({Position.x - 50, Position.y + 37});
}

void TFBox::SetZIndex(int index) {
    m_Box->SetZIndex(index);
    m_Arrow->SetZIndex(index + 1);
}

bool TFBox::Choose() {
    if (Util::Input::IsKeyDown(Util::Keycode::UP)) {
        m_Arrow->SetPosition({m_Arrow->GetPosition().x, m_Box->GetPosition().y + 37});
    }

    if (Util::Input::IsKeyDown(Util::Keycode::DOWN)) {
        m_Arrow->SetPosition({m_Arrow->GetPosition().x, m_Box->GetPosition().y - 35});
    }

    if (Util::Input::IsKeyDown(Util::Keycode::Z)) {
        return true;
    }

    return false;
}