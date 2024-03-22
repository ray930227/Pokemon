#include "Pokemon.hpp"

Pokemon::Pokemon(const std::string &ID, int choose) {
    m_ID = std::stoi(ID);
    m_IV = rand() % 32;
    m_HPBP = 0;
    m_AttackBP = 0;
    m_DefenceBP = 0;
    m_SpecialBP = 0;
    m_SpeedBP = 0;
    m_LV = 5;
    std::ifstream FileOfType(RESOURCE_DIR"/Pokemon/Type.txt");
    std::vector<std::string> Types;
    std::string text;
    while (FileOfType >> text) {
        Types.push_back(text);
    }
    FileOfType.close();
    std::istringstream iss(Types[m_ID - 1]);
    std::vector<std::string> Type;
    while (iss >> text) {
        Type.push_back(text);
    }
    m_Type = Type;
    std::ifstream FileOfAbility(RESOURCE_DIR"/Pokemon/PokemonAbility.txt");
    int Value[151][5];
    for (int r = 0; r < 151; r++) {
        for (int c = 0; c < 5; c++) {
            FileOfAbility >> Value[r][c];
        }
    }
    FileOfAbility.close();
    m_HP = ((int(Value[m_ID - 1][0]) + m_IV + int(round(sqrt(m_HPBP) / 8))) * m_LV / 50) + 10 + m_LV;
    m_Attack = ((int(Value[m_ID - 1][1]) + m_IV + int(round(sqrt(m_AttackBP) / 8))) * m_LV / 50) + 5;
    m_Defence = ((int(Value[m_ID - 1][2]) + m_IV + int(round(sqrt(m_DefenceBP) / 8))) * m_LV / 50) + 5;
    m_Special = ((int(Value[m_ID - 1][3]) + m_IV + int(round(sqrt(m_SpecialBP) / 8))) * m_LV / 50) + 5;
    m_Speed = ((int(Value[m_ID - 1][4]) + m_IV + int(round(sqrt(m_SpeedBP) / 8))) * m_LV / 50) + 5;
    std::ifstream FileOfSkill(RESOURCE_DIR"/Pokemon/PokemonAbility.txt");

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

std::vector<std::string> Pokemon::GetSkill() const {
    return m_Skill;
}

std::vector<std::string> Pokemon::GetType() const {
    return m_Type;
}

int Pokemon::GetHP() const {
    return m_HP;
}

int Pokemon::GetAttack() const {
    return m_Attack;
}

int Pokemon::GetDefence() const {
    return m_Defence;
}

int Pokemon::GetSpecial() const {
    return m_Special;
}

int Pokemon::GetSpeed() const {
    return m_Speed;
}

void Pokemon::LevelUp() {
    m_LV++;
}

int Pokemon::GetIV() const{
    return m_IV;
}
