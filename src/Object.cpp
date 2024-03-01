#include "Object.hpp"
#include "Util/Image.hpp"
#include "Util/Text.hpp"


Object::Object(const std::string& ImagePath) {
    SetImage(ImagePath);

    ResetPosition();
}

Object::Object(const std::vector<std::string>& AnimationPaths) {
    m_Drawable = std::make_shared<Util::Animation>(AnimationPaths, false, 500, false, 0);
}

Object::Object(const std::shared_ptr<Core::Drawable> &drawable){
    SetDrawable(drawable);
}

void Object::SetImage(const std::string& ImagePath) {
    m_ImagePath = ImagePath;

    m_Drawable = std::make_shared<Util::Image>(m_ImagePath);
}

bool Object::IfCollides(const std::shared_ptr<Object>& other) const {
    float x1 = GetPosition().x;
    float x2 = other->GetPosition().x;
    float y1 = GetPosition().y;
    float y2 = other->GetPosition().y;
    glm::vec2 edge1=GetScaledSize();
    glm::vec2 edge2=other->GetScaledSize();

    bool x_overlap = (x1 <= x2 && x2 <= x1 + edge1.x) || (x2 <= x1 && x1 <= x2 + edge2.x);
    bool y_overlap = (y1 - edge1.y <= y2 && y2 <= y1) || (y2 - edge2.y <= y1 && y1 <= y2);

    return x_overlap && y_overlap;
}

bool Object::IfAnimationEnds() const {
    auto animation = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
    return animation->GetCurrentFrameIndex() == animation->GetFrameCount() - 1;
}
