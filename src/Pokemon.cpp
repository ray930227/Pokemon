#include "Pokemon.hpp"

Pokemon::Pokemon(const std::string &ID, int choose) {
    m_ID = std::stoi(ID);
    if (choose == 0) {
        SetImage(RESOURCE_DIR"/Pokemon/Pokemonback/Pokemonback" + ID + ".png");
    } else {
        SetImage(RESOURCE_DIR"/Pokemon/Pokemonfront/Pokemonfront" + ID + ".png");
    }
}

bool Pokemon::GetVisibility() const { return m_Visible; }

const glm::vec2 &Pokemon::GetPosition() const { return m_Transform.translation; }

void Pokemon::SetImage(const std::string &path) {
    m_ImagePath = path;
    SetDrawable(std::make_shared<Util::Image>(m_ImagePath));
}

void Pokemon::SetPosition(const glm::vec2 &Position) {
    m_Transform.translation = Position;
}

int Pokemon::GetAbility(int option) const {
    std::ifstream file(RESOURCE_DIR"/Pokemon/PokemonAbility.txt");
    int Value[151][5];
    for (int r = 0; r < 151; r++) {
        for (int c = 0; c < 5; c++) {
            file >> Value[r][c];
        }
    }
    file.close();
    return Value[m_ID - 1][option];
}

std::string Pokemon::GetName() const {
    std::ifstream file(RESOURCE_DIR"/Pokemon/Name.txt");
    std::vector<std::string> Name;
    std::string text;
    while (file >> text) {
        Name.push_back(text);
    }
    file.close();
    return Name[m_ID - 1];
}