#ifndef POKEMON_POKEMON_HPP
#define POKEMON_POKEMON_HPP

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"
#include "UsefulFunctions.hpp"
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>

class Pokemon : public Util::GameObject {
private:
    std::vector<std::string> m_Skills;
    std::vector<std::string> m_SkillTypes;
    std::vector<std::string> m_SkillClass;
    std::vector<std::string> m_SkillDamage;
    std::vector<std::string> m_SkillHitRates;
    std::vector<std::string> m_SkillPPs;
    std::string m_ImagePath;
    std::string m_Name;
    std::vector<std::string> m_Type;
    int m_LV;
    int m_HP;
    int m_Attack;
    int m_Defence;
    int m_Special;
    int m_Speed;
    int m_IV;
    int m_HPBP;
    int m_AttackBP;
    int m_DefenceBP;
    int m_SpecialBP;
    int m_SpeedBP;
    int m_ID;
public:
    Pokemon(const std::string &ID, int choose);//choose 0:back 1:front

    [[nodiscard]] bool GetVisibility() const;

    [[nodiscard]] const glm::vec2 &GetPosition() const;

    void SetImage(const std::string &path);

    void SetPosition(const glm::vec2 &Position);

    void LevelUp();

    void FindName();

    [[nodiscard]] std::string GetName() const;

    void FindSkill();

    [[nodiscard]] std::vector<std::string> GetSkill() const;

    void FindType();

    [[nodiscard]] std::vector<std::string> GetType() const;

    void FindAbiltiy();

    int GetHP() const;

    int GetAttack() const;

    int GetDefence() const;

    int GetSpecial() const;

    int GetSpeed() const;

    int GetIV() const;

    int GetLV() const;

    bool IsSkillFull() const;

    [[nodiscard]] std::vector<std::string> GetSkillType() const;

    [[nodiscard]] std::vector<std::string> GetSkillPP() const;

    void IsEvolution();
};

#endif //POKEMON_POKEMON_HPP
