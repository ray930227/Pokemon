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
#include "UI/EvolutionUI.hpp"
#include "UI/FightSkillUI.hpp"
#include "UI/PokeBagUI.hpp"
#include "TFBox.hpp"
#include "UI/LoadingUI.hpp"
#include "UI/FightMainUI.hpp"
#include "UI/ShopUI.hpp"
#include "UI/ReplaceSkillUI.hpp"
#include "UI/FightTextUI.hpp"
#include "UI/PokeFaintedUI.hpp"
#include "UI/SettingUI.hpp"
#include "UI/ComputerUI.hpp"

#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"
#include "Util/BGM.hpp"
#include "Core/Context.hpp"
#include "SFXSystem.hpp"
#include <cmath>

class App {
public:
    enum class State {
        START,
        HOME,
        READ_SAVE,
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
        SHOP,
        NPC,
        COMPUTER,
        HEAL,
        CHOOSE_POKEMON,
        SETTING,
        NPC_END,
        ALL_POKEMON_DIE,
        NONE
    };

    enum class LoadingID {
        INIT,
        LOADING,
        TEXT,
        NONE
    };

    enum class FightID {
        HOME,
        SKILL,
        POKEPACK,
        BACKPACK,
        RUN,
        FIGHT,
        CHANGEPOKE,
        FAILCHANGE,
        POKEFAINTED,
        EVOLUTION,
        GETSKILL,
        WILDFINISH,
        NPCCHANGE,
        UPDATEINFO,
        NONE
    };

    State GetCurrentState() const { return m_CurrentState; }

    void Start();

    void Home();

    void ReadSave();

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
    std::shared_ptr<Image> m_OpeningAnimation;
    int m_OpeningAnimationCount = 0;
    std::shared_ptr<MapSystem> m_MapSystem;
    std::shared_ptr<Image> m_WhiteBG;
    std::shared_ptr<Image> m_BlackBG;
    std::shared_ptr<Image> m_tempImage;
    std::shared_ptr<Image> m_ReadSaveBG;
    std::shared_ptr<Image> m_Arrow;

    std::shared_ptr<EvolutionUI> m_EvolutionUI;
    std::shared_ptr<FightSkillUI> m_FightSkillUI;
    std::shared_ptr<PokeBagUI> m_PokeBagUI;
    std::shared_ptr<LoadingUI> m_LoadingUI;
    std::shared_ptr<FightMainUI> m_FightMainUI;
    std::shared_ptr<ReplaceSkillUI> m_ReplaceSkillUI;
    std::shared_ptr<ShopUI> m_ShopUI;
    std::shared_ptr<FightTextUI> m_FightTextUI;
    std::shared_ptr<PokeFaintedUI> m_PokeFaintedUI;
    std::shared_ptr<SettingUI> m_SettingUI;
    std::shared_ptr<ComputerUI> m_ComputerUI;

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
    int PlayerSkillChoose = 0;
    int EnemySkillChoose = 0;
    bool IsPlayerRound;
    int DisplacementCount;
    int m_PreviousPlayerPokemon = 0;
    int m_CurrentPlayerPokemon = 0;
    int m_CurrentNPCPokemon = 0;
    int ButtonTrigger = 0;
    int FightCounter = 0;
    int Timer = 0;
    bool IsChangePokemon = false;
    std::pair<bool, int> m_Experience;
    bool encounterable = true;
    bool isWildPokemon = false;
    std::string currentDirection;
};

#endif
