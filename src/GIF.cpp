#include "GIF.hpp"

GIF::GIF(const std::vector<std::string> &ImagePaths) {
    m_Interval = 500;
    m_Loop = false;
    SetDrawable(std::make_shared<Util::Animation>(ImagePaths, false, m_Interval, m_Loop, 0));
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

std::size_t GIF::GetCurrentFrameIndex() const {
    auto temp = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
    return temp->GetCurrentFrameIndex();
}

void GIF::SetPosition(const glm::vec2 &Position) {
    m_Transform.translation = Position;
}

void GIF::SetInterval(int interval) {
    auto temp = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
    m_Interval = interval;
    temp->SetInterval(m_Interval);
}

void GIF::SetLooping(bool looping) {
    auto temp = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
    temp->SetLooping(looping);
}

void GIF::SetImagePaths(const std::vector<std::string> &ImagePaths) {
    SetDrawable(std::make_shared<Util::Animation>(ImagePaths, false, m_Interval, m_Loop, 0));
}

void GIF::SetCurrentFrame(std::size_t index) {
    auto temp = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
    temp->SetCurrentFrame(index);
}

void GIF::Play() {
    auto temp = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
    temp->Play();
}

void GIF::Pause() {
    auto temp = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
    temp->Pause();
}