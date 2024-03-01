#ifndef POKEMON_OBJECT_HPP
#define POKEMON_OBJECT_HPP

#include <string>

#include "Util/GameObject.hpp"
#include "Util/Animation.hpp"

class Object : public Util::GameObject {
public:
    explicit Object(const std::string& ImagePath);

    explicit Object(const std::vector<std::string>& AnimationPaths);

    Object(const std::shared_ptr<Core::Drawable> &drawable);

    Object(const Object&) = delete;

    Object(Object&&) = delete;

    Object& operator=(const Object&) = delete;

    Object& operator=(Object&&) = delete;

    [[nodiscard]] const std::string& GetImagePath() const { return m_ImagePath; }

    [[nodiscard]] const glm::vec2& GetPosition() const { return m_Transform.translation; }

    [[nodiscard]] bool GetVisibility() const { return m_Visible; }

    void SetImage(const std::string& ImagePath);

    void SetPosition(const glm::vec2& Position) { m_Transform.translation = Position; }

    void SetScale(const glm::vec2& scale){m_Transform.scale = scale;}

    [[nodiscard]] bool IfCollides(const std::shared_ptr<Object>& other) const;

    [[nodiscard]] bool IsLooping() const {
        return std::dynamic_pointer_cast<Util::Animation>(m_Drawable)->GetLooping();
    }

    [[nodiscard]] bool IsPlaying() const {
        return std::dynamic_pointer_cast<Util::Animation>(m_Drawable)->GetState() == Util::Animation::State::PLAY;
    }

    void SetLooping(bool looping) {
        auto temp = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
        temp->SetLooping(looping);
    }

    void Play() {
        auto temp = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
        temp->Play();
    }

    void SetInterval(int interval) {
        auto temp = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
        temp->SetInterval(interval);
    }

    [[nodiscard]] bool IfAnimationEnds() const;

private:
    void ResetPosition() { m_Transform.translation = {0, 0}; }

    std::string m_ImagePath;
};

#endif //POKEMON_OBJECT_HPP
