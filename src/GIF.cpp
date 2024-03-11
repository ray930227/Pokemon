#include "GIF.hpp"

GIF::GIF(const std::vector<std::string> &ImagePaths) {
    SetDrawable(std::make_shared<Util::Animation>(ImagePaths, false, 500, false, 0));
}

bool GIF::IsLooping() const {
    return std::dynamic_pointer_cast<Util::Animation>(m_Drawable)->GetLooping();
}

bool GIF::IsPlaying() const {
    return std::dynamic_pointer_cast<Util::Animation>(m_Drawable)->GetState() == Util::Animation::State::PLAY;
}

bool GIF::IsAnimationEnds() const {
    auto animation = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
    return animation->GetCurrentFrameIndex() == animation->GetFrameCount() - 1;
}

std::size_t GIF::GetFrameCount() const {
    auto temp = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
    return temp->GetFrameCount();
}

void GIF::SetInterval(int interval)  {
    auto temp = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
    temp->SetInterval(interval);
}

void GIF::SetLooping(bool looping) {
    auto temp = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
    temp->SetLooping(looping);
}

void GIF::Play() {
    auto temp = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
    temp->Play();
}

void GIF::SetPosition(const glm::vec2 &Position) {
    m_Transform.translation = Position;
}