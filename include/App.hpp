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
#include "EventManager.hpp"
#include "UI/EvolutionUI.hpp"
#include "UI/FightSkillUI.hpp"
#include "UI/PokeBagUI.hpp"
#include "TFBox.hpp"
#include "UI/LoadingUI.hpp"
#include "UI/FightMainUI.hpp"
#include "UI/ShopUI.hpp"
#include "UI/ReplaceSkillUI.hpp"
#include "UI/FightTextUI.hpp"

#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"
#include "Util/BGM.hpp"
#include "Core/Context.hpp"
#include "SFXSystem.hpp"

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
        END
    };

    enum class EventID {
        MOVE,
        DOOR,
        GRASS,
        BILLBOARD,
        JUMP,
        WEEKTREE,
        BALL,
        CHOOSE_POKEMON,
        SHOP,
        NONE
    };

    enum class LoadingID {
        INTO,
        TEXT,
        NONE
    };

    enum class FightID {
        HOME,
        SKILL,
        POKEPACK,
        BACKPACK,
        FIGHT,
        DECISION,
        EVOLUTION,
        OBTAINSKILL,
        REPLACESKILL,
        UPDATEINFO,
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
    State m_CurrentState = State::START;
    EventID m_CurrentEvent = EventID::NONE;
    LoadingID m_CurrentLoading = LoadingID::NONE;
    FightID m_CurrentFighting = FightID::NONE;

    Util::Root m_Root;
    std::shared_ptr<Util::BGM> m_BGM;
    std::shared_ptr<SFXSystem> m_SFX;
    std::shared_ptr<GIF> m_AnimatedText;
    std::shared_ptr<MapSystem> m_MapSystem;
    std::shared_ptr<Image> m_WhiteBG;
    std::shared_ptr<Image> m_BlackBG;
    std::shared_ptr<Image> m_tempImage;

    std::shared_ptr<EvolutionUI> m_EvolutionUI;
    std::shared_ptr<FightSkillUI> m_FightSkillUI;
    std::shared_ptr<PokeBagUI> m_PokeBagUI;
    std::shared_ptr<LoadingUI> m_LoadingUI;
    std::shared_ptr<FightMainUI> m_FightMainUI;
    std::shared_ptr<ReplaceSkillUI> m_ReplaceSkillUI;
    std::shared_ptr<ShopUI> m_ShopUI;
    std::shared_ptr<FightTextUI> m_FightTextUI;

    std::shared_ptr<Image> m_Fightitem;
    std::shared_ptr<Text> m_PlayerPokeInfo;
    std::shared_ptr<Text> m_EnemyPokeInfo;

    std::shared_ptr<TFBox> m_TFBox;
    std::shared_ptr<TextBox> m_TB;
    std::shared_ptr<Character> Player;
    std::shared_ptr<Character> Enemy;
    std::shared_ptr<Character> NPC_Bromance;
    std::shared_ptr<Character> NPC_Oak;
    std::shared_ptr<TextBox> tempBox;
    glm::vec2 Displacement = {0, 0};
    int PlayerSkillChoose;
    int EnemySkillChoose;
    bool IsPlayerRound;
    int DisplacementCount;
    int m_CurrentPlayerPokemon = 0;
    int ButtonTrigger = 0;
    int FightCounter = 0;
    bool encounterable = true;
    bool isWildPokemon = false;
    std::string currentDirection;
    EventManager m_EventManager;
};

#endif
