#ifndef APP_HPP
#define APP_HPP

#include "pch.hpp" // IWYU pragma: export

#include "Util/Root.hpp"
#include "TextBox.hpp"
#include "Image.hpp"
#include "GIF.hpp"
#include "Character.hpp"
#include "MapSystem.hpp"
#include "Pokemon.hpp"

#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"
#include "Util/BGM.hpp"

class App {
public:
    enum class State {
        START,
        HOME,
        INIT,
        UPDATE,
        EVENT,
        LOADING,
        FIGHT,
        END,
    };

    enum class EventID {
        MOVE,
        DOOR,
        GRASS,
        BILLBOARD,
        JUMP,
        WEEKTREE,
        NONE
    };

    enum class LoadingID {
        INTO,
        TEXT,
        NONE
    };

    State GetCurrentState() const { return m_CurrentState; }

    void Start();

    void Home();

    void Init();

    void Update();

    void Event();

    void Loading();

    void Fight();

    void End();

private:
    void ValidTask();

private:
    State m_CurrentState = State::START;
    EventID m_CurrentEvent = EventID::NONE;
    LoadingID m_CurrentLoading = LoadingID::NONE;

    Util::Root m_Root;
    std::shared_ptr<Util::BGM> m_BGM;
    std::shared_ptr<GIF> m_AnimatedText;
    std::shared_ptr<MapSystem> m_MapSystem;
    std::shared_ptr<Image> m_WhiteBG;
    std::shared_ptr<Image> m_BlackBG;
    std::shared_ptr<Image> m_FightBG;
    std::shared_ptr<Image> m_tempImage;

    std::shared_ptr<Image> m_FightLoad1_1;
    std::shared_ptr<Image> m_FightLoad1_2;
    std::shared_ptr<Image> m_arrow;
    std::shared_ptr<Image> m_Fightskill;
    std::shared_ptr<Image> m_Fightitem;
    std::shared_ptr<Image> m_PlayerHPimage;
    std::shared_ptr<Image> m_EnemyHPimage;
    std::shared_ptr<Image> m_PlayerHPUI;
    std::shared_ptr<Image> m_EnemyHPUI;
    std::shared_ptr<Image> m_PlayerBalls;
    std::shared_ptr<GIF> m_BallAnimation;
    std::shared_ptr<Pokemon> m_PlayerPokemon;
    std::shared_ptr<Pokemon> m_EnemyPokemon;
    std::shared_ptr<PokemonBag> m_PokemonBag;
    std::shared_ptr<Text> m_PlayerHP;
    std::shared_ptr<Text> m_PlayerPokeName;
    std::shared_ptr<Text> m_EnemyPokeName;
    std::shared_ptr<Text> m_Skill1;
    std::shared_ptr<Text> m_Skill2;
    std::shared_ptr<Text> m_Skill3;
    std::shared_ptr<Text> m_Skill4;
    std::shared_ptr<Text> m_SkillInfo;
    std::shared_ptr<Text> m_PlayerPokeInfo;
    std::shared_ptr<Text> m_EnemyPokeInfo;

    std::shared_ptr<TextBox> m_TB;
    std::shared_ptr<Character> Player;
    std::shared_ptr<Character> NPC_Bromance;
    std::shared_ptr<TextBox> tempBox;
    glm::vec2 Displacement = {0, 0};
    int DisplacementCount;
    bool encounterable= true;
    std::string currentDirection;
};

#endif
