#include "Pokemon.hpp"

Pokemon::Pokemon(const std::string &ID) {
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
    m_CurrentHP = m_HP;
}

std::string Pokemon::GetID() {
    std::stringstream ToString;
    ToString << std::setw(3) << std::setfill('0') << m_ID;
    std::string StringID = ToString.str();
    return StringID;
}

void Pokemon::LevelUp() {
    if (m_LV != 100) {
        m_LV++;
        FindAbiltiy();
    }
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

std::pair<std::vector<std::string>, std::vector<std::string>> Pokemon::GetSkillInfo() {
    std::stringstream ToString;
    ToString << std::setw(3) << std::setfill('0') << m_ID;
    std::string StringID = ToString.str();
    std::ifstream FileOfSkill(RESOURCE_DIR"/Pokemon/PokeSkill/Poke" + StringID + ".txt");
    std::vector<std::string> Skills;
    std::vector<std::string> LVs;
    std::string NeedLV;
    std::string LearnSkill;
    while (FileOfSkill >> NeedLV >> LearnSkill) {
        if (NeedLV != "—") {
            if (std::stoi(NeedLV) > m_LV) {
                break;
            }
        }
        LVs.push_back(NeedLV);
        Skills.push_back(LearnSkill);
    }
    FileOfSkill.close();
    return std::make_pair(Skills, LVs);
}

void Pokemon::FindSkill() {
    std::vector<std::string> Skills = GetSkillInfo().first;
    std::vector<std::string> LVs = GetSkillInfo().second;
    for (long long unsigned int i = 0; i < LVs.size(); i++) {
        if (IsSkillFull()) {
            m_Skills.erase(m_Skills.begin());
        }
        m_Skills.push_back(Skills[i]);
        std::string Move;
        std::ifstream FileOfMove(RESOURCE_DIR"/Pokemon/Move.txt");
        while (std::getline(FileOfMove, Move)) {
            if (Move.find(Skills[i]) != std::string::npos) {
                std::vector<std::string> tokens;
                std::stringstream ss(Move);
                std::string token;
                while (std::getline(ss, token, ' ')) {
                    tokens.push_back(token);
                }
                if (m_SkillTypes.size() == 4) {
                    m_SkillTypes.erase(m_SkillTypes.begin());
                    m_SkillClass.erase(m_SkillClass.begin());
                    m_SkillDamage.erase(m_SkillDamage.begin());
                    m_SkillHitRates.erase(m_SkillHitRates.begin());
                    m_SkillPPs.erase(m_SkillPPs.begin());
                    m_CurrentSkillPPs.erase(m_CurrentSkillPPs.begin());
                }
                m_SkillTypes.push_back(tokens[1]);
                m_SkillClass.push_back(tokens[2]);
                m_SkillDamage.push_back(tokens[3]);
                m_SkillHitRates.push_back(tokens[4]);
                m_SkillPPs.push_back(tokens[5]);
                m_CurrentSkillPPs.push_back(tokens[5]);
                break;
            }
        }
        FileOfMove.close();
    }
}

void Pokemon::GetNewSkill() {
    std::vector<std::string> Skills = GetSkillInfo().first;
    std::vector<std::string> LVs = GetSkillInfo().second;
    std::string Move;
    std::ifstream FileOfMove(RESOURCE_DIR"/Pokemon/Move.txt");
    while (std::getline(FileOfMove, Move)) {
        if (Move.find(Skills[Skills.size() - 1]) != std::string::npos) {
            std::vector<std::string> tokens;
            std::stringstream ss(Move);
            std::string token;
            while (std::getline(ss, token, ' ')) {
                tokens.push_back(token);
            }
            m_Skills.push_back(tokens[0]);
            m_SkillTypes.push_back(tokens[1]);
            m_SkillClass.push_back(tokens[2]);
            m_SkillDamage.push_back(tokens[3]);
            m_SkillHitRates.push_back(tokens[4]);
            m_SkillPPs.push_back(tokens[5]);
            m_CurrentSkillPPs.push_back(tokens[5]);
            break;
        }
    }
}

void Pokemon::GetNewSkill(int SkillChange) {
    std::vector<std::string> Skills = GetSkillInfo().first;
    std::vector<std::string> LVs = GetSkillInfo().second;
    std::string Move;
    std::ifstream FileOfMove(RESOURCE_DIR"/Pokemon/Move.txt");
    while (std::getline(FileOfMove, Move)) {
        if (Move.find(Skills[Skills.size() - 1]) != std::string::npos) {
            std::vector<std::string> tokens;
            std::stringstream ss(Move);
            std::string token;
            while (std::getline(ss, token, ' ')) {
                tokens.push_back(token);
            }
            m_Skills[SkillChange] = tokens[0];
            m_SkillTypes[SkillChange] = tokens[1];
            m_SkillClass[SkillChange] = tokens[2];
            m_SkillDamage[SkillChange] = tokens[3];
            m_SkillHitRates[SkillChange] = tokens[4];
            m_SkillPPs[SkillChange] = tokens[5];
            m_CurrentSkillPPs[SkillChange] = tokens[5];
            break;
        }
    }
}


std::string Pokemon::NewSkill() {
    std::vector<std::string> Skills = GetSkillInfo().first;
    return Skills[Skills.size()-1];
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
    int PreviousHP=m_HP;
    m_HP = ((int(Value[m_ID - 1][0]) + m_IV + int(round(sqrt(m_HPBP) / 8))) * m_LV / 50) + 10 + m_LV;
    m_CurrentHP += m_HP-PreviousHP;
    m_Attack = ((int(Value[m_ID - 1][1]) + m_IV + int(round(sqrt(m_AttackBP) / 8))) * m_LV / 50) + 5;
    m_Defence = ((int(Value[m_ID - 1][2]) + m_IV + int(round(sqrt(m_DefenceBP) / 8))) * m_LV / 50) + 5;
    m_Special = ((int(Value[m_ID - 1][3]) + m_IV + int(round(sqrt(m_SpecialBP) / 8))) * m_LV / 50) + 5;
    m_Speed = ((int(Value[m_ID - 1][4]) + m_IV + int(round(sqrt(m_SpeedBP) / 8))) * m_LV / 50) + 5;
}

int Pokemon::GetHP() const {
    return m_HP;
}

int Pokemon::GetCurrentHP() const {
    return m_CurrentHP;
}

void Pokemon::PokemonHurt(int Damage) {
    m_CurrentHP -= Damage;
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

std::vector<std::string> Pokemon::GetCurrentSkillPP() const {
    return m_CurrentSkillPPs;
}

void Pokemon::ReducePP(int skill) {
    int tempstr;
    tempstr = std::stoi(m_CurrentSkillPPs[skill]);
    tempstr -= 1;
    m_CurrentSkillPPs[skill] = std::to_string(tempstr);
}

std::vector<std::string> Pokemon::GetSkillDamge() const {
    return m_SkillDamage;
}

std::vector<std::string> Pokemon::GetSkillHitRate() const {
    return m_SkillHitRates;
}

std::vector<std::string> Pokemon::GetSkillClass() const {
    return m_SkillClass;
}

bool Pokemon::IsEvolution() {
    std::ifstream FileOfLevel(RESOURCE_DIR"/Pokemon/Levelup.txt");
    std::vector<int> Levels;
    std::string text;
    while (FileOfLevel >> text) {
        Levels.push_back(std::stoi(text));
    }
    FileOfLevel.close();
    if (m_LV == Levels[m_ID - 1] && Levels[m_ID - 1] != 0) {
        m_ID++;
        FindName();
        return true;
    }
    else{
        return false;
    }
}

bool Pokemon::IsGetNewSkill() {
    std::vector<std::string> Skills = GetSkillInfo().first;
    std::vector<std::string> LVs = GetSkillInfo().second;
    if (LVs[LVs.size() - 1] != "—") {
        return (std::stoi(LVs[LVs.size() - 1]) == m_LV);
    }
    return false;
}
