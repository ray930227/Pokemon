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
    FindType();
    FindName();
    FindAbiltiy();
    FindSkill();
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

void Pokemon::FindName() {
    std::ifstream file(RESOURCE_DIR"/Pokemon/Name.txt");
    std::vector<std::string> Name;
    std::string text;
    while (file >> text) {
        Name.push_back(text);
    }
    file.close();
    m_Name = Name[m_ID - 1];
}

std::string Pokemon::GetName() const {
    return m_Name;
}

void Pokemon::FindSkill() {
    std::stringstream ToString;
    ToString << std::setw(3) << std::setfill('0') << m_ID;
    std::string StringID = ToString.str();
    std::ifstream FileOfSkill(RESOURCE_DIR"/Pokemon/PokeSkill/Poke" + StringID + ".txt");
    std::vector<std::string> Skills;
    std::vector<std::string> LVs;
    std::string NeedLV;
    std::string LearnSkill;
    while (FileOfSkill >> NeedLV >> LearnSkill) {
        LVs.push_back(NeedLV);
        Skills.push_back(LearnSkill);
    }
    FileOfSkill.close();

    for (long long unsigned int i = 0; i < LVs.size(); i++) {
        bool ShouldAdd=true;
        if (LVs[i] == "—" or std::stoi(LVs[i]) <= m_LV) {
            for (const auto &skill:m_Skills){
                if (Skills[i]==skill){
                    ShouldAdd=false;
                }
            }
            if (ShouldAdd){
                if (IsSkillFull()){
                    m_Skills.erase(m_Skills.begin());
                }
                m_Skills.push_back(Skills[i]);
            }
        }
    }
    std::string text;
    std::vector<std::string> Moves;
    for (const auto &skill: m_Skills) {
        std::ifstream FileOfMove(RESOURCE_DIR"/Pokemon/Move.txt");
        while (std::getline(FileOfMove, text)) {
            if (text.find(skill) != std::string::npos) {
                Moves.push_back(text);
                break;
            }
        }
        FileOfMove.close();
    }
    for (const auto &Element: Moves) {
        std::vector<std::string> tokens;
        std::stringstream ss(Element);
        std::string token;
        while (std::getline(ss, token, ' ')) {
            tokens.push_back(token);
        }
        if (m_SkillTypes.size()==4){
            m_SkillTypes.erase(m_SkillTypes.begin());
            m_SkillClass.erase(m_SkillClass.begin());
            m_SkillDamage.erase(m_SkillDamage.begin());
            m_SkillHitRates.erase(m_SkillHitRates.begin());
            m_SkillPPs.erase(m_SkillPPs.begin());
        }
        m_SkillTypes.push_back(tokens[1]);
        m_SkillClass.push_back(tokens[2]);
        m_SkillDamage.push_back(tokens[3]);
        m_SkillHitRates.push_back(tokens[4]);
        m_SkillPPs.push_back(tokens[5]);
    }
}

std::vector<std::string> Pokemon::GetSkill() const {
    return m_Skills;
}

void Pokemon::FindType() {
    std::ifstream FileOfType(RESOURCE_DIR"/Pokemon/Type.txt");
    std::vector<std::string> Types;
    std::string text;
    while (FileOfType >> text) {
        Types.push_back(text);
    }
    FileOfType.close();
    std::istringstream SpliteOfType(Types[m_ID - 1]);
    std::vector<std::string> Type;
    while (SpliteOfType >> text) {
        Type.push_back(text);
    }
    m_Type = Type;
}

std::vector<std::string> Pokemon::GetType() const {
    return m_Type;
}

void Pokemon::FindAbiltiy() {
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
    if (m_LV!=100){
        m_LV++;
        FindAbiltiy();
        FindSkill();
        IsEvolution();
    }
}

int Pokemon::GetIV() const {
    return m_IV;
}

int Pokemon::GetLV() const {
    return m_LV;
}

bool Pokemon::IsSkillFull() const {
    return m_Skills.size() == 4;
}

std::vector<std::string> Pokemon::GetSkillType() const {
    return m_SkillTypes;
}

std::vector<std::string> Pokemon::GetSkillPP() const {
    return m_SkillPPs;
}

void Pokemon::IsEvolution(){
    std::ifstream FileOfLevel(RESOURCE_DIR"/Pokemon/Levelup.txt");
    std::vector<int> Levels;
    std::string text;
    while (FileOfLevel >> text) {
        Levels.push_back(std::stoi(text));
    }
    FileOfLevel.close();
    if (m_LV==Levels[m_ID-1] && Levels[m_ID-1]!=0){
        std::stringstream ToString;
        ToString << std::setw(3) << std::setfill('0') << m_ID+1;
        std::string StringID = ToString.str();
        SetImage(RESOURCE_DIR"/Pokemon/Pokemonback/Pokemonback" + StringID + ".png");
        m_ID++;
        FindName();
    }
}
