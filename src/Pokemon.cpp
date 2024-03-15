#include "Pokemon.hpp"

Pokemon::Pokemon(const std::string& ID,int choose){
    if (choose==0){
        SetImage(RESOURCE_DIR"/Pokemon/Pokemonback/Pokemonback"+ID+".png");
    }
    else{
        SetImage(RESOURCE_DIR"/Pokemon/Pokemonfront/Pokemonfront"+ID+".png");
    }
}

bool Pokemon::GetVisibility() const{ return m_Visible;}

const glm::vec2 &Pokemon::GetPosition() const { return m_Transform.translation; }

void Pokemon::SetImage(const std::string& path) {
    m_ImagePath=path;
    SetDrawable(std::make_shared<Util::Image>(m_ImagePath));
}

void Pokemon::SetPosition(const glm::vec2 &Position) {
    m_Transform.translation = Position;
}