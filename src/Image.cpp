#include "Image.hpp"

Image::Image(const std::string &ImagePath) {
    SetImage(ImagePath);
    m_Transform.translation = {0, 0};
}

bool Image::GetVisibility() const { return m_Visible; }

void Image::SetImage(const std::string &ImagePath) {
    SetDrawable(std::make_shared<Util::Image>(ImagePath));
}

void Image::SetPosition(const glm::vec2 &Position) {
    m_Transform.translation = Position;
}

void Image::SetScale(const glm::vec2 &scale) {m_Transform.scale = scale;}