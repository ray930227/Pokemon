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

    m_ReadSaveBG=std::make_shared<Image>(RESOURCE_DIR"/Background/ReadSaveBG.png");
    m_ReadSaveBG->SetVisible(false);
    m_ReadSaveBG->SetZIndex(50);
    m_Root.AddChild(m_ReadSaveBG);

    m_Arrow=std::make_shared<Image>(RESOURCE_DIR"/Background/BlockArrow.png");
    m_Arrow->SetVisible(false);
    m_Arrow->SetZIndex(51);
    m_Arrow->SetPosition({-300, 290});
    m_Root.AddChild(m_Arrow);


    m_BGM = std::make_shared<Util::BGM>(RESOURCE_DIR"/OpeningAnimation/OpeningSound.mp3");
    m_BGM->SetVolume(32);

    m_SFX = std::make_shared<SFXSystem>();

    m_EvolutionUI = std::make_shared<EvolutionUI>();
    m_Root.AddChildren(m_EvolutionUI->GetChildren());

    m_PokeFaintedUI = std::make_shared<PokeFaintedUI>();
    for (const auto &Child: m_PokeFaintedUI->GetChildren()) {
        m_Root.AddChildren(Child);
    }

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

    m_TempBox = std::make_shared<TextBox>();
    m_TempBox->SetVisible(false);
    m_Root.AddChildren(m_TempBox->GetChildren());

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
    m_Player = std::make_shared<Character>(tempImagePathses);
    m_Player->SetCurrentImagePath(1);
    m_Player->GetImage()->SetZIndex(50);
    m_Player->GetImage()->SetPosition({36, -36});
    m_Player->GetImage()->SetVisible(false);
    m_Root.AddChild(m_Player->GetImage());

    m_Enemy=std::make_shared<Character>();

    m_PokeBagUI = std::make_shared<PokeBagUI>(m_Player);
    m_Root.AddChildren(m_PokeBagUI->GetChildren());

    m_FightSkillUI = std::make_shared<FightSkillUI>(m_Player);
    m_Root.AddChildren(m_FightSkillUI->GetChildren());

    m_FightMainUI = std::make_shared<FightMainUI>(m_Player, m_Enemy);
    m_Root.AddChildren(m_FightMainUI->GetChildren());

    m_FightTextUI = std::make_shared<FightTextUI>(m_Player, m_Enemy);
    for(auto &i:m_FightTextUI->GetChildren()){
        m_Root.AddChildren(i);
    }

    m_ReplaceSkillUI = std::make_shared<ReplaceSkillUI>(m_Player);
    for (const auto &Child: m_ReplaceSkillUI->GetChildren()) {
        m_Root.AddChildren(Child);
    }

    m_LoadingUI = std::make_shared<LoadingUI>(m_Player, m_Enemy);
    for (const auto &Child: m_LoadingUI->GetChildren()) {
        m_Root.AddChildren(Child);
    }

    m_BackPackUI = std::make_shared<ItemUI>(m_Player);
    m_Root.AddChildren(m_BackPackUI->GetChildren());

    tempImagePathses.clear();
    tempImagePathses.resize(1);
    tempImagePathses.push_back({RESOURCE_DIR"/Charactor/enemyfront_1.png"});
    m_NPCBromance = std::make_shared<Character>(tempImagePathses);

    tempImagePathses.clear();
    tempImagePathses.resize(4);
    tempImagePathses[0].push_back(RESOURCE_DIR"/Charactor/OakBack_1.png");
    tempImagePathses[0].push_back(RESOURCE_DIR"/Charactor/OakBack_2.png");
    tempImagePathses[0].push_back(RESOURCE_DIR"/Charactor/OakBack_1.png");
    tempImagePathses[0].push_back(RESOURCE_DIR"/Charactor/OakBack_3.png");
    tempImagePathses[1].push_back(RESOURCE_DIR"/Charactor/OakFront_1.png");
    tempImagePathses[1].push_back(RESOURCE_DIR"/Charactor/OakFront_2.png");
    tempImagePathses[1].push_back(RESOURCE_DIR"/Charactor/OakFront_1.png");
    tempImagePathses[1].push_back(RESOURCE_DIR"/Charactor/OakFront_3.png");
    tempImagePathses[2].push_back(RESOURCE_DIR"/Charactor/OakLeft_1.png");
    tempImagePathses[2].push_back(RESOURCE_DIR"/Charactor/OakLeft_2.png");
    tempImagePathses[3].push_back(RESOURCE_DIR"/Charactor/OakRight_1.png");
    tempImagePathses[3].push_back(RESOURCE_DIR"/Charactor/OakRight_2.png");
    m_NPCOak = std::make_shared<Character>(tempImagePathses);
    m_NPCOak->GetImage()->SetZIndex(49);
    m_NPCOak->GetImage()->SetVisible(false);
    m_Root.AddChild(m_NPCOak->GetImage());

    m_ShopUI = std::make_shared<ShopUI>(m_Player);
    m_Root.AddChildren(m_ShopUI->GetChildren());

    m_ComputerUI = std::make_shared<ComputerUI>(m_Player);
    m_Root.AddChildren(m_ComputerUI->GetChildren());

    m_SettingUI=std::make_shared<SettingUI>(m_Player, m_ComputerUI);
    m_Root.AddChildren(m_SettingUI->GetChildren());


    std::vector<std::pair<std::string,float>> tempPairs={{"攻擊",1.0},{"命中率",1.0},{"閃避率",1.0},
                                                         {"防禦",1.0},{"特殊",1.0},{"速度",1.0},};

    for(auto &i:tempPairs){
        m_PlayerBuff.insert(i);
        m_EnemyBuff.insert(i);
    }

    m_CurrentState = State::HOME;
}