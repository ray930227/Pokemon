#include "App.hpp"

void App::Start() {
    LOG_TRACE("Start");
    srand(time(NULL));
    std::vector<std::string> tempText;
    for (int i = 100; i >= 10; i -= 10) {
        tempText.push_back(RESOURCE_DIR"/Start/press enter to start" + std::to_string(i) + "%.png");
    }
    for (int i = 20; i < 100; i += 10) {
        tempText.push_back(RESOURCE_DIR"/Start/press enter to start" + std::to_string(i) + "%.png");
    }
    m_AnimatedText = std::make_shared<GIF>(tempText);
    m_AnimatedText->SetZIndex(99);
    m_AnimatedText->SetLooping(true);
    m_AnimatedText->SetInterval(100);
    m_AnimatedText->Play();
    m_Root.AddChild(m_AnimatedText);

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

    m_BGM = std::make_shared<Util::BGM>(RESOURCE_DIR"/BGM/Opening.mp3");
    m_BGM->SetVolume(32);
    m_BGM->Play();

    //region Fight
    m_LoadingUI = std::make_shared<LoadingUI>();
    for (const auto &Child: m_LoadingUI->GetChildren()) {
        m_Root.AddChildren(Child);
    }

    m_FightMainUI = std::make_shared<FightMainUI>();
    m_Root.AddChildren(m_FightMainUI->GetChildren());

    m_FightSkillUI = std::make_shared<FightSkillUI>();
    m_Root.AddChildren(m_FightSkillUI->GetChildren());

    m_PokeBagUI = std::make_shared<PokeBagUI>();
    for (size_t i = 0; i < 6; i++) {
        m_Root.AddChildren(m_PokeBagUI->GetChildren()[i]);
    }

    m_EvolutionUI = std::make_shared<EvolutionUI>();
    m_Root.AddChildren(m_EvolutionUI->GetChildren());

    m_ReplaceSkillUI = std::make_shared<ReplaceSkillUI>();
    for (const auto &Child: m_ReplaceSkillUI->GetChildren()) {
        m_Root.AddChildren(Child);
    }

    m_arrow = std::make_shared<Image>(RESOURCE_DIR"/Fight/arrow.png");
    m_arrow->SetZIndex(55);
    m_arrow->SetVisible(false);
    m_arrow->SetPosition({-25, -200});
    m_Root.AddChild(m_arrow);

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

    m_CurrentState = State::HOME;
}