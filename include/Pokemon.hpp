#ifndef POKEMON_POKEMON_HPP
#define POKEMON_POKEMON_HPP

#include "Util/GameObject.hpp"
#include "UsefulFunctions.hpp"
#include <map>

#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>

class Pokemon {
private:
    std::vector<std::string> m_Skills;
    std::vector<std::string> m_SkillTypes;
    std::vector<std::string> m_SkillClass;
    std::vector<std::string> m_SkillDamage;
    std::vector<std::string> m_SkillHitRates;
    std::vector<std::string> m_SkillPPs;
    std::vector<std::string> m_CurrentSkillPPs;

    std::string m_Name;
    std::vector<std::string> m_Type;
    std::map<std::string, int> m_Ability;
public:
    Pokemon(const std::string &ID);

    std::map<std::string, int> GetAbility();

    void SetAbility(std::map<std::string, int> Ability);

    std::string GetID();

    void SetIV(int IV);

    void SetCurrentEXP(int EXP);

    void SetBPs(std::vector<int> BPs);

    int GetIDByInt();

    void LevelUp();

    void FindName();

    [[nodiscard]] std::string GetName() const;

    std::pair<std::vector<std::string>, std::vector<std::string>> GetSkillInfo();

    void FindSkill();

    void GetNewSkill();

    void GetNewSkill(int SkillChange);

    std::string NewSkill();

    [[nodiscard]] std::vector<std::string> GetSkill() const;

    void FindType();

    [[nodiscard]] std::vector<std::string> GetType() const;

    void FindAbiltiy();

    [[nodiscard]] int GetHP();

    [[nodiscard]] int GetCurrentHP();

    void PokemonHurt(int Damage);

    void PokemonHurt(const std::shared_ptr<Pokemon> &EnemyPokemon, int SkillChoose);

    [[nodiscard]] int GetAttack();

    [[nodiscard]] int GetDefence();

    [[nodiscard]] int GetSpecial();

    [[nodiscard]] int GetSpeed();

    [[nodiscard]] int GetIV();

    [[nodiscard]] int GetLV();

    [[nodiscard]] int GetCurrentEXP();

    [[nodiscard]] bool IsSkillFull() const;

    [[nodiscard]] std::vector<std::string> GetSkillType() const;

    [[nodiscard]] std::vector<std::string> GetSkillPP() const;

    [[nodiscard]] std::vector<std::string> GetCurrentSkillPP() const;

    void ReducePP(int skill);

    [[nodiscard]] std::vector<std::string> GetSkillDamge() const;

    [[nodiscard]] std::vector<std::string> GetSkillHitRate() const;

    [[nodiscard]] std::vector<std::string> GetSkillClass() const;

    bool IsEvolution();

    void Evolution();

    bool IsGetNewSkill();

    int CaculateDamge(const std::vector<std::string> &EnemyType);

    bool IsPokemonDying();

    std::pair<bool, int> GainExperince(int EnemyLV);

    void SetCurrentHP(int HP);

    void ReSetSkills();

    void SetLevel(int Level);

    void SetSkillByID(std::vector<int> SkillID);

    void GetSkillByCD(std::string CDofID);

    void GetSkillByCD(std::string CDofID, int SkillChange);

    bool IsSkillLearnable(std::string CDofID);

    void GainBasePoints(int Point);

    void SetSkillByName(const std::vector<std::string> &SkillName);

    void SetCurrentSkillPP(std::vector<std::string> CurrentSkillPP);
};

#endif //POKEMON_POKEMON_HPP
