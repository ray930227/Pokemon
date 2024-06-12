#include "Pokemon.hpp"

Pokemon::Pokemon(const std::string &ID) {
    m_Ability.insert({"LV", 5});
    m_Ability.insert({"IV", rand() % 32});
    m_Ability.insert({"HP", 0});
    m_Ability.insert({"CurrentHP", 0});
    m_Ability.insert({"Attack", 0});
    m_Ability.insert({"Defence", 0});
    m_Ability.insert({"Special", 0});
    m_Ability.insert({"Speed", 0});
    m_Ability.insert({"HPBP", 0});
    m_Ability.insert({"AttackBP", 0});
    m_Ability.insert({"DefenceBP", 0});
    m_Ability.insert({"SpecialBP", 0});
    m_Ability.insert({"SpeedBP", 0});
    m_Ability.insert({"ID", std::stoi(ID)});
    m_Ability.insert({"EXP", 0});
    m_Ability.insert({"CurrentEXP", 0});
    FindType();
    FindName();
    FindAbiltiy();
    FindSkill();
    m_Ability["CurrentHP"] = m_Ability["HP"];
}

std::map<std::string, int> Pokemon::GetAbility() {
    return m_Ability;
}

void Pokemon::SetAbility(std::map<std::string, int> Ability) {
    m_Ability = Ability;
    FindAbiltiy();
}

std::string Pokemon::GetID() {
    std::stringstream ToString;
    ToString << std::setw(3) << std::setfill('0') << m_Ability["ID"];
    std::string StringID = ToString.str();
    return StringID;
}

void Pokemon::SetIV(int IV) {
    m_Ability["IV"] = IV;
}

void Pokemon::SetCurrentEXP(int EXP) {
    m_Ability["CurrentEXP"] = EXP;
}

void Pokemon::SetBPs(std::vector<int> BPs) {
    m_Ability["HPBP"] = BPs[0];
    m_Ability["AttackBP"] = BPs[1];
    m_Ability["DefenceBP"] = BPs[2];
    m_Ability["SpecialBP"] = BPs[3];
    m_Ability["SpeedBP"] = BPs[4];
}

int Pokemon::GetIDByInt() {
    return m_Ability["ID"];
}

void Pokemon::LevelUp() {
    if (m_Ability["LV"] != 100) {
        m_Ability["LV"]++;
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
    m_Name = Name[m_Ability["ID"] - 1];
}

std::string Pokemon::GetName() const {
    return m_Name;
}

std::pair<std::vector<std::string>, std::vector<std::string>> Pokemon::GetSkillInfo() {
    std::stringstream ToString;
    ToString << std::setw(3) << std::setfill('0') << m_Ability["ID"];
    std::string StringID = ToString.str();
    std::ifstream FileOfSkill(RESOURCE_DIR"/Pokemon/PokeSkill/Poke" + StringID + ".txt");
    std::vector<std::string> Skills;
    std::vector<std::string> LVs;
    std::string NeedLV;
    std::string LearnSkill;
    while (FileOfSkill >> NeedLV >> LearnSkill) {
        if (NeedLV != "—") {
            if (std::stoi(NeedLV) > m_Ability["LV"]) {
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
    FileOfMove.close();
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
    return Skills[Skills.size() - 1];
}

std::vector<std::string> Pokemon::GetSkill() const {
    return m_Skills;
}

void Pokemon::FindType() {
    std::ifstream FileOfType(RESOURCE_DIR"/Pokemon/Type.txt");
    std::vector<std::string> Types;
    std::string text;
    while (std::getline(FileOfType, text)) {
        Types.push_back(text);
    }
    FileOfType.close();
    std::istringstream SpliteOfType(Types[m_Ability["ID"] - 1]);
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
    int PreviousHP = m_Ability["HP"];
    m_Ability["HP"] =
            ((int(Value[m_Ability["ID"] - 1][0]) + m_Ability["IV"] + int(round(sqrt(m_Ability["HPBP"]) / 8))) *
             m_Ability["LV"] / 50) + 10 + m_Ability["LV"];
    m_Ability["CurrentHP"] += m_Ability["HP"] - PreviousHP;

    m_Ability["Attack"] =
            ((int(Value[m_Ability["ID"] - 1][1]) + m_Ability["IV"] + int(round(sqrt(m_Ability["AttackBP"]) / 8))) *
             m_Ability["LV"] / 50) + 5;
    m_Ability["Defence"] =
            ((int(Value[m_Ability["ID"] - 1][2]) + m_Ability["IV"] + int(round(sqrt(m_Ability["DefenceBP"]) / 8))) *
             m_Ability["LV"] / 50) + 5;
    m_Ability["Special"] =
            ((int(Value[m_Ability["ID"] - 1][3]) + m_Ability["IV"] + int(round(sqrt(m_Ability["SpecialBP"]) / 8))) *
             m_Ability["LV"] / 50) + 5;
    m_Ability["Speed"] =
            ((int(Value[m_Ability["ID"] - 1][4]) + m_Ability["IV"] + int(round(sqrt(m_Ability["SpeedBP"]) / 8))) *
             m_Ability["LV"] / 50) + 5;
    m_Ability["EXP"] = m_Ability["LV"] * m_Ability["LV"] * m_Ability["LV"];
}

int Pokemon::GetHP()  {
    return m_Ability["HP"];
}

int Pokemon::GetCurrentHP()  {
    return m_Ability["CurrentHP"];
}

void Pokemon::PokemonHurt(int Damage) {
    m_Ability["CurrentHP"] -= Damage;
}

void Pokemon::PokemonHurt(const std::shared_ptr<Pokemon> &EnemyPokemon, int SkillChoose) {
    int Damage;
    Damage = round((((2.0 * EnemyPokemon->GetLV() + 10) / 250) * (1.0 * EnemyPokemon->GetAttack() / m_Ability["Defence"]) *
                    std::stof(EnemyPokemon->GetSkillDamge()[SkillChoose]) + 2) *
                   PokeFunction::TypeDamage(
                           EnemyPokemon->GetSkillType()[SkillChoose],
                           m_Type));
    m_Ability["CurrentHP"] -= Damage;
    if (m_Ability["CurrentHP"] < 0) {
        m_Ability["CurrentHP"] = 0;
    }
}

int Pokemon::GetAttack()  {
    return m_Ability["Attack"];
}

int Pokemon::GetDefence()  {
    return m_Ability["Defence"];
}

int Pokemon::GetSpecial()  {
    return m_Ability["Special"];
}

int Pokemon::GetSpeed()  {
    return m_Ability["Speed"];
}

int Pokemon::GetIV()  {
    return m_Ability["IV"];
}

int Pokemon::GetLV()  {
    return m_Ability["LV"];
}

int Pokemon::GetCurrentEXP()  {
    return m_Ability["CurrentEXP"];
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
    if (m_Ability["LV"] >= Levels[m_Ability["ID"] - 1] && Levels[m_Ability["ID"] - 1] != 0) {
        return true;
    } else {
        return false;
    }
}

void Pokemon::Evolution() {
    m_Ability["ID"]++;
    FindName();
    FindAbiltiy();
    FindType();
}

bool Pokemon::IsGetNewSkill() {
    std::vector<std::string> Skills = GetSkillInfo().first;
    std::vector<std::string> LVs = GetSkillInfo().second;
    if (LVs[LVs.size() - 1] != "—") {
        return (std::stoi(LVs[LVs.size() - 1]) == m_Ability["LV"]);
    }
    return false;
}

int Pokemon::CaculateDamge(const std::vector<std::string> &EnemyType) {
    int MostPowerful = 0;
    int Damage;
    int EnemySkillChoose = 0;
    for (size_t i = 0; i < m_Skills.size(); i++) {
        if (m_SkillDamage[i] != "—" && m_SkillDamage[i] != "變化") {
            Damage = round(std::stof(m_SkillDamage[i]) * PokeFunction::TypeDamage(m_SkillTypes[i], EnemyType));
            if (Damage > MostPowerful) {
                MostPowerful = Damage;
                EnemySkillChoose = i;
            }
        }
    }
    return EnemySkillChoose;
}

bool Pokemon::IsPokemonDying() {
    return m_Ability["CurrentHP"] <= 0;
}

std::pair<bool, int> Pokemon::GainExperince(int EnemyLV) {
    int RandomEXP = (rand() % 50) + EnemyLV * 15;
    int EXP;
    bool IsTrue = false;
    EXP = round((RandomEXP * EnemyLV) / 7);
    m_Ability["CurrentEXP"] += EXP;
    while (m_Ability["CurrentEXP"] > m_Ability["EXP"]) {
        m_Ability["CurrentEXP"] -= m_Ability["EXP"];
        LevelUp();
        IsTrue = true;
    }
    return std::make_pair(IsTrue, EXP);
}

void Pokemon::SetCurrentHP(int HP) {
    m_Ability["CurrentHP"] = HP;
}

void Pokemon::ReSetSkills() {
    m_Skills.clear();
    m_SkillTypes.clear();
    m_SkillClass.clear();
    m_SkillDamage.clear();
    m_SkillHitRates.clear();
    m_SkillPPs.clear();
    m_CurrentSkillPPs.clear();
}

void Pokemon::SetLevel(int Level) {
    m_Ability["LV"] = Level;
    while (IsEvolution()) {
        Evolution();
    }
    ReSetSkills();
    FindAbiltiy();
    FindSkill();
}

void Pokemon::SetSkillByID(std::vector<int> SkillID) {
    std::string Move;
    std::ifstream FileOfMove(RESOURCE_DIR"/Pokemon/Move.txt");
    std::vector<std::vector<std::string>> AllSkills;
    while (std::getline(FileOfMove, Move)) {
        std::vector<std::string> tokens;
        std::stringstream ss(Move);
        std::string token;
        while (std::getline(ss, token, ' ')) {
            tokens.push_back(token);
        }
        AllSkills.push_back(tokens);
    }
    ReSetSkills();
    for (auto ID: SkillID) {
        m_Skills.push_back(AllSkills[ID - 1][0]);
        m_SkillTypes.push_back(AllSkills[ID - 1][1]);
        m_SkillClass.push_back(AllSkills[ID - 1][2]);
        m_SkillDamage.push_back(AllSkills[ID - 1][3]);
        m_SkillHitRates.push_back(AllSkills[ID - 1][4]);
        m_SkillPPs.push_back(AllSkills[ID - 1][5]);
        m_CurrentSkillPPs.push_back(AllSkills[ID - 1][5]);
    }
    FileOfMove.close();
}

void Pokemon::GetSkillByCD(std::string CDofID) {
    if (IsSkillLearnable(CDofID) && !IsSkillFull()) {
        int Counter = 1;
        std::string SkillName;
        std::string Line;
        std::ifstream FileOfCDLearn(RESOURCE_DIR"/Pokemon/CDLearn.txt");
        while (getline(FileOfCDLearn, Line)) {
            if (Counter == std::stoi(CDofID)) {
                SkillName = Line;
                break;
            }
        }
        FileOfCDLearn.close();
        std::string Move;
        std::ifstream FileOfMove(RESOURCE_DIR"/Pokemon/Move.txt");
        while (std::getline(FileOfMove, Move)) {
            if (Move.find(SkillName) != std::string::npos) {
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
        FileOfMove.close();
    }
}

void Pokemon::GetSkillByCD(std::string CDofID, int SkillChange) {
    if (IsSkillLearnable(CDofID)) {
        int Counter = 1;
        std::string SkillName;
        std::string Line;
        std::ifstream FileOfCDLearn(RESOURCE_DIR"/Pokemon/CDLearn.txt");
        while (getline(FileOfCDLearn, Line)) {
            if (Counter == std::stoi(CDofID)) {
                SkillName = Line;
                break;
            }
            Counter++;
        }
        FileOfCDLearn.close();
        std::string Move;
        std::ifstream FileOfMove(RESOURCE_DIR"/Pokemon/Move.txt");
        while (std::getline(FileOfMove, Move)) {
            if (Move.find(SkillName) != std::string::npos) {
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
        FileOfMove.close();
    }
}


bool Pokemon::IsSkillLearnable(std::string CDofID) {
    int Counter = 1;
    std::string Line;
    std::string TargetLine;
    std::vector<std::string> AllCDs;
    std::ifstream FileOfLearnSet(RESOURCE_DIR"/Pokemon/LearnSet.txt");
    while (getline(FileOfLearnSet, Line)) {
        if (Counter == m_Ability["ID"]) {
            if (Line == "-") {
                return false;
            }
            TargetLine = Line;
            break;
        }
        Counter++;
    }
    FileOfLearnSet.close();
    std::stringstream ss(TargetLine);
    std::string token;
    while (std::getline(ss, token, ' ')) {
        AllCDs.push_back(token);
    }
    for (const auto &CD: AllCDs) {
        if (CD == CDofID) {
            return true;
        }
    }
    return false;
}

void Pokemon::GainBasePoints(int Point) {
    m_Ability["HPBP"] += Point;
    m_Ability["AttackBP"] += Point;
    m_Ability["DefenceBP"] += Point;
    m_Ability["SpecialBP"] += Point;
    m_Ability["SpeedBP"] += Point;
}

void Pokemon::SetSkillByName(const std::vector<std::string> &SkillName) {
    std::string Move;
    std::vector<std::vector<std::string>> AllSkills;
    for (const auto &Name: SkillName) {
        std::ifstream FileOfMove(RESOURCE_DIR"/Pokemon/Move.txt");
        while (std::getline(FileOfMove, Move)) {
            if (Move.find(Name) != std::string::npos) {
                std::vector<std::string> tokens;
                std::stringstream ss(Move);
                std::string token;
                while (std::getline(ss, token, ' ')) {
                    tokens.push_back(token);
                }
                AllSkills.push_back(tokens);
                break;
            }
        }
        FileOfMove.close();
    }
    ReSetSkills();
    for (auto Skill: AllSkills) {
        m_Skills.push_back(Skill[0]);
        m_SkillTypes.push_back(Skill[1]);
        m_SkillClass.push_back(Skill[2]);
        m_SkillDamage.push_back(Skill[3]);
        m_SkillHitRates.push_back(Skill[4]);
        m_SkillPPs.push_back(Skill[5]);
        m_CurrentSkillPPs.push_back(Skill[5]);
    }
}

void Pokemon::SetCurrentSkillPP(std::vector<std::string> CurrentSkillPP) {
    m_CurrentSkillPPs=CurrentSkillPP;
}