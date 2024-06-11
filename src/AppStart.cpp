#include "App.hpp"

void App::Start() {
    LOG_TRACE("Start");
    srand(time(NULL));
    std::vector<std::string> tempText;

    m_OpeningAnimation = std::make_shared<Image>(RESOURCE_DIR"/OpeningAnimation/frame_0.jpg");
    m_OpeningAnimation->SetZIndex(99);
    m_OpeningAnimation->SetVisible(true);
    m_Root.AddChild(m_OpeningAnimation);

    m_MapSystem = std::make_shared<MapSystem>("PlayerHouse2F");
    m_MapSystem->SetVisible(false);
    m_Root.AddChildren(m_MapSystem->GetChildren());

    m_WhiteBG = std::make_shared<Image>(RESOURCE_DIR"/Background/WhiteBG.png");
    m_WhiteBG->SetZIndex(0);
    m_WhiteBG->SetVisible(false);
    m_Root.AddChild(m_WhiteBG);

    m_BlackBG = std::make_shared<Image>(RESOURCE_DIR"/Background/BlackBG.png");
    m_BlackBG->SetZIndex(98);
    m_BlackBG->SetVisible(true);
    m_BlackBG->SetPosition({0, 0});
    m_Root.AddChild(m_BlackBG);

    m_tempImage = std::make_shared<Image>(RESOURCE_DIR"/Charactor/DrWholeBody.png");
    m_tempImage->SetZIndex(1);
    m_tempImage->SetVisible(false);
    m_Root.AddChild(m_tempImage);

    m_BGM = std::make_shared<Util::BGM>(RESOURCE_DIR"/OpeningAnimation/OpeningSound.mp3");
    m_BGM->SetVolume(32);

    m_SFX = std::make_shared<SFXSystem>();

    //region Fight
    m_LoadingUI = std::make_shared<LoadingUI>();
    for (const auto &Child: m_LoadingUI->GetChildren()) {
        m_Root.AddChildren(Child);
    }

    m_EvolutionUI = std::make_shared<EvolutionUI>();
    m_Root.AddChildren(m_EvolutionUI->GetChildren());

    m_PokeFaintedUI = std::make_shared<PokeFaintedUI>();
    for (const auto &Child: m_PokeFaintedUI->GetChildren()) {
        m_Root.AddChildren(Child);
    }

    m_Fightitem = std::make_shared<Image>(RESOURCE_DIR"/Fight/Fightitembox.png");
    m_Fightitem->SetZIndex(54);
    m_Fightitem->SetVisible(false);
    m_Fightitem->SetPosition({0, -60});
    m_Root.AddChild(m_Fightitem);

    m_PlayerPokeInfo = std::make_shared<Text>();
    m_PlayerPokeInfo->SetZIndex(99);
    m_PlayerPokeInfo->SetVisible(false);
    m_PlayerPokeInfo->SetPosition({-500, -70});
    m_Root.AddChild(m_PlayerPokeInfo);

    m_EnemyPokeInfo = std::make_shared<Text>();
    m_EnemyPokeInfo->SetZIndex(99);
    m_EnemyPokeInfo->SetVisible(false);
    m_EnemyPokeInfo->SetPosition({500, 200});
    m_Root.AddChild(m_EnemyPokeInfo);
    //endregion

    m_TB = std::make_shared<TextBox>();
    m_TB->SetVisible(false);
    m_Root.AddChildren(m_TB->GetChildren());

    tempBox = std::make_shared<TextBox>();
    tempBox->SetVisible(false);
    m_Root.AddChildren(tempBox->GetChildren());

    m_TFBox = std::make_shared<TFBox>();
    m_Root.AddChildren(m_TFBox->GetChildren());

    std::vector<std::vector<std::string>> tempImagePathses;
    tempImagePathses.resize(4);
    tempImagePathses[0].push_back(RESOURCE_DIR"/Charactor/playerBack_1.png");
    tempImagePathses[0].push_back(RESOURCE_DIR"/Charactor/playerBack_2.png");
    tempImagePathses[0].push_back(RESOURCE_DIR"/Charactor/playerBack_1.png");
    tempImagePathses[0].push_back(RESOURCE_DIR"/Charactor/playerBack_3.png");
    tempImagePathses[1].push_back(RESOURCE_DIR"/Charactor/playerFront_1.png");
    tempImagePathses[1].push_back(RESOURCE_DIR"/Charactor/playerFront_2.png");
    tempImagePathses[1].push_back(RESOURCE_DIR"/Charactor/playerFront_1.png");
    tempImagePathses[1].push_back(RESOURCE_DIR"/Charactor/playerFront_3.png");
    tempImagePathses[2].push_back(RESOURCE_DIR"/Charactor/playerLeft_1.png");
    tempImagePathses[2].push_back(RESOURCE_DIR"/Charactor/playerLeft_2.png");
    tempImagePathses[3].push_back(RESOURCE_DIR"/Charactor/playerRight_1.png");
    tempImagePathses[3].push_back(RESOURCE_DIR"/Charactor/playerRight_2.png");
    Player = std::make_shared<Character>(tempImagePathses);
    Player->SetCurrentImagePath(1);
    Player->GetImage()->SetZIndex(50);
    Player->GetImage()->SetPosition({36, -36});
    Player->GetImage()->SetVisible(false);
    m_Root.AddChild(Player->GetImage());

    Enemy=std::make_shared<Character>();

    m_PokeBagUI = std::make_shared<PokeBagUI>(Player);
    m_Root.AddChildren(m_PokeBagUI->GetChildren());

    m_FightSkillUI = std::make_shared<FightSkillUI>(Player);
    m_Root.AddChildren(m_FightSkillUI->GetChildren());

    m_FightMainUI = std::make_shared<FightMainUI>(Player,Enemy);
    m_Root.AddChildren(m_FightMainUI->GetChildren());

    m_FightTextUI = std::make_shared<FightTextUI>(Player,Enemy);
    for (const auto &Child: m_FightTextUI->GetChildren()) {
        m_Root.AddChildren(Child);
    }

    m_ReplaceSkillUI = std::make_shared<ReplaceSkillUI>(Player);
    for (const auto &Child: m_ReplaceSkillUI->GetChildren()) {
        m_Root.AddChildren(Child);
    }

    tempImagePathses.clear();
    tempImagePathses.resize(1);
    tempImagePathses.push_back({RESOURCE_DIR"/Charactor/enemyfront_1.png"});
    NPC_Bromance = std::make_shared<Character>(tempImagePathses);

    tempImagePathses.clear();
    tempImagePathses.resize(4);
    tempImagePathses.push_back({RESOURCE_DIR"/Charactor/OakBack.png"});
    tempImagePathses.push_back({RESOURCE_DIR"/Charactor/OakFront.png"});
    tempImagePathses.push_back({RESOURCE_DIR"/Charactor/OakLeft.png"});
    tempImagePathses.push_back({RESOURCE_DIR"/Charactor/OakRight.png"});
    NPC_Oak = std::make_shared<Character>(tempImagePathses);
    NPC_Oak->GetImage()->SetZIndex(49);
    NPC_Oak->GetImage()->SetVisible(false);
    m_Root.AddChild(NPC_Oak->GetImage());

    m_ShopUI = std::make_shared<ShopUI>(Player);
    m_Root.AddChildren(m_ShopUI->GetChildren());

    m_ComputerUI = std::make_shared<ComputerUI>(Player);
    m_Root.AddChildren(m_ComputerUI->GetChildren());

    m_SettingUI=std::make_shared<SettingUI>(Player,m_ComputerUI);
    m_Root.AddChildren(m_SettingUI->GetChildren());

    m_CurrentState = State::HOME;
}