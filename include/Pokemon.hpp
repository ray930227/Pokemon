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
    std::vector<std::string> m_CurrentSkillPPs;

    std::string m_ImagePath;
    std::string m_Name;
    std::vector<std::string> m_Type;
    int m_LV;
    int m_HP;
    int m_CurrentHP;
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
    bool m_Isfornt;
public:
    Pokemon(const std::string &ID, int choose);//choose 0:back 1:front

    [[nodiscard]] bool GetVisibility() const;

    [[nodiscard]] const glm::vec2 &GetPosition() const;

    std::string  GetImagepath();

    void SetImage(const std::string &path);

    void SetPosition(const glm::vec2 &Position);

    [[nodiscard]] const glm::vec2 &GetScale();

    void SetScale(const glm::vec2 &scale);

    void Move(const glm::vec2 &Displacement);

    void LevelUp();

    void FindName();

    [[nodiscard]] std::string GetName() const;

    void FindSkill();

    [[nodiscard]] std::vector<std::string> GetSkill() const;

    void FindType();

    [[nodiscard]] std::vector<std::string> GetType() const;

    void FindAbiltiy();

    [[nodiscard]] int GetHP() const;

    [[nodiscard]] int GetCurrentHP() const;

    void PokemonHurt(int Damage);

    [[nodiscard]] int GetAttack() const;

    [[nodiscard]] int GetDefence() const;

    [[nodiscard]] int GetSpecial() const;

    [[nodiscard]] int GetSpeed() const;

    [[nodiscard]] int GetIV() const;

    [[nodiscard]] int GetLV() const;

    [[nodiscard]] bool IsSkillFull() const;

    [[nodiscard]] std::vector<std::string> GetSkillType() const;

    [[nodiscard]] std::vector<std::string> GetSkillPP() const;

    [[nodiscard]] std::vector<std::string> GetCurrentSkillPP() const;

    void ReducePP(int skill);

    [[nodiscard]] std::vector<std::string> GetSkillDamge() const;

    [[nodiscard]] std::vector<std::string> GetSkillHitRate() const;

    [[nodiscard]] std::vector<std::string> GetSkillClass() const;

    void IsEvolution();
};

#endif //POKEMON_POKEMON_HPP
