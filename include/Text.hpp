#ifndef POKEMON_TEXT_HPP
#define POKEMON_TEXT_HPP

#include "Util/GameObject.hpp"
#include "Util/Text.hpp"

class Text:public Util::GameObject{
private:
    std::string m_Text;
public:
    Text();
    std::string& GetText();
    void SetText(const std::string &str);
    void SetPosition(const glm::vec2& Position);
};

#endif //POKEMON_TEXT_HPP
