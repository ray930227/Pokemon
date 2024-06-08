#include "Block.hpp"

Block::Block(bool traversable, bool event, int eventID) {
    SetTraversable(traversable);
    SetEvent(event);
    m_EventID = eventID;
    m_Displayable = true;
    switch (eventID) {
        case 5:
            SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR"/Blocks/weektree.png"));
            break;
        case 6:
            SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR"/Blocks/ball.png"));
            break;
        default:
            m_Displayable= false;
    }

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
    return m_EventID;
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

void Block::SetEventID(int EventID) {
    m_EventID=EventID;
}

bool Block::isDisplayable() {
    return m_Displayable;
}