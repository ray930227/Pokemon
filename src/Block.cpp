#include "Block.hpp"

Block::Block(bool traversable, bool event, int eventID) {
    SetTraversable(traversable);
    SetEvent(event);
    m_eventID = eventID;
    m_Displayable=eventID==6;
    if(m_Displayable)
        SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR"/Blocks/ball.png"));
}

bool Block::GetVisibility() const {
    return m_Visible;
}

const glm::vec2 &Block::GetPosition() const {
    return m_Transform.translation;
}

bool Block::GetTraversable() const {
    return m_Traversable;
}

bool Block::GetEvent() const {
    return m_Event;
}

int Block::GetEventID() const {
    return m_eventID;
}

void Block::SetImage(const std::string &ImagePath) {
    SetDrawable(std::make_shared<Util::Image>(ImagePath));
}

void Block::SetPosition(const glm::vec2 &Position) {
    m_Transform.translation = Position;
}

void Block::SetTraversable(bool traversable) {
    m_Traversable = traversable;
}

void Block::SetEvent(bool event) {
    m_Event = event;
}

bool Block::isDisplayable() {
    return m_Displayable;
}