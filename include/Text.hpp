#ifndef POKEMON_TEXT_HPP
#define POKEMON_TEXT_HPP

#include "Util/GameObject.hpp"
#include "Util/Text.hpp"

class Text : public Util::GameObject {
private:
    std::string m_Text;
    int m_Size=30;
public:
    Text();

    std::string &GetText();

    void SetText(const std::string &str);

    void SetPosition(const glm::vec2 &Position);

    void SetSize(int size);

    [[nodiscard]] const glm::vec2 &GetPosition() const;
};

#endif //POKEMON_TEXT_HPP
