#ifndef POKEMON_IMAGE_HPP
#define POKEMON_IMAGE_HPP

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"

class Image:public Util::GameObject{
private:
    std::string m_ImagePath;
public:
    Image(const std::string& ImagePath);
    [[nodiscard]] bool GetVisibility() const;
    [[nodiscard]] const glm::vec2& GetPosition() const;
    void SetImage(const std::string& ImagePath);
    void SetPosition(const glm::vec2& Position);
    void SetScale(const glm::vec2& scale);
    void Move(const glm::vec2& Displacement);
};

#endif //POKEMON_IMAGE_HPP
