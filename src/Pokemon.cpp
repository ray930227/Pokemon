#include "Pokemon.hpp"
#include "UsefulFunctions.hpp"

Pokemon::Pokemon(const std::string& ID,int choose){
    m_ID=std::stoi(ID);
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

int Pokemon::GetHP() const{
    return (useful::Getability(m_ID,0));
}

std::string Pokemon::GetName() const {
    return (useful::Getname(m_ID));
}