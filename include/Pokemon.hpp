#ifndef POKEMON_POKEMON_HPP
#define POKEMON_POKEMON_HPP

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"
#include <string>

class Pokemon:public Util::GameObject{
private:
    std::string m_ImagePath;
    int m_Hp;
    int m_Attack;
    int m_Defence;
    int m_Special;
    int m_Speed;
    int m_IV;
    int m_EV;
public:
    Pokemon(const std::string& ID,int choose);
    [[nodiscard]] bool GetVisibility() const;
    [[nodiscard]] const glm::vec2& GetPosition() const;
    void SetImage(const std::string& path);
    void SetPosition(const glm::vec2& Position);
};

#endif //POKEMON_POKEMON_HPP
