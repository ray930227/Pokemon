#include "App.hpp"

void App::Start() {
    LOG_TRACE("Start");
    std::vector<std::string> tempText;
    for (int i = 100; i >= 10; i -= 10) {
        tempText.push_back(RESOURCE_DIR"/Start/press enter to start" + std::to_string(i) + "%.png");
    }
    for (int i = 20; i < 100; i += 10) {
        tempText.push_back(RESOURCE_DIR"/Start/press enter to start" + std::to_string(i) + "%.png");
    }
    m_AnimatedText = std::make_shared<GIF>(tempText);
    m_AnimatedText->SetZIndex(10);
    m_AnimatedText->SetLooping(true);
    m_AnimatedText->SetInterval(100);
    m_AnimatedText->Play();
    m_Root.AddChild(m_AnimatedText);

    m_Map = std::make_shared<Map>(RESOURCE_DIR"/Map/MainMap");
    m_Map->SetVisible(false);
    m_Root.AddChildren(m_Map->GetChildren());

    m_WhiteBG = std::make_shared<Image>(RESOURCE_DIR"/Background/WhiteBG.png");
    m_WhiteBG->SetZIndex(0);
    m_WhiteBG->SetVisible(false);
    m_Root.AddChild(m_WhiteBG);

    m_BlackBG = std::make_shared<Image>(RESOURCE_DIR"/Background/BlackBG.png");
    m_BlackBG->SetZIndex(0);
    m_BlackBG->SetVisible(true);
    m_BlackBG->SetPosition({0, 0});
    m_Root.AddChild(m_BlackBG);

    m_tempImage = std::make_shared<Image>(RESOURCE_DIR"/Charactor/DrWholeBody.png");
    m_tempImage->SetZIndex(1);
    m_tempImage->SetVisible(false);
    m_Root.AddChild(m_tempImage);

    m_BGM = std::make_shared<Util::BGM>(RESOURCE_DIR"/BGM/Opening.mp3");
    m_BGM->Play();

    //region Fight
    m_FightLoad1_1 = std::make_shared<Image>(RESOURCE_DIR"/Fight/Fightloading1_1.png");
    m_FightLoad1_1->SetZIndex(51);
    m_FightLoad1_1->SetVisible(false);
    m_FightLoad1_1->SetPosition({-720, 0});

    m_Root.AddChild(m_FightLoad1_1);
    m_FightLoad1_2 = std::make_shared<Image>(RESOURCE_DIR"/Fight/Fightloading1_2.png");
    m_FightLoad1_2->SetZIndex(51);
    m_FightLoad1_2->SetVisible(false);
    m_FightLoad1_2->SetPosition({720, 0});
    m_Root.AddChild(m_FightLoad1_2);

    m_FightBG = std::make_shared<Image>(RESOURCE_DIR"/Fight/FightBG.png");
    m_FightBG->SetZIndex(51);
    m_FightBG->SetVisible(false);
    m_FightBG->SetPosition({0, 0});
    m_Root.AddChild(m_FightBG);

    m_arrow = std::make_shared<Image>(RESOURCE_DIR"/Fight/arrow.png");
    m_arrow->SetZIndex(54);
    m_arrow->SetVisible(false);
    m_arrow->SetPosition({-25, -200});
    m_Root.AddChild(m_arrow);

    m_Fightskill = std::make_shared<Image>(RESOURCE_DIR"/Fight/Fightskillbox.png");
    m_Fightskill->SetZIndex(53);
    m_Fightskill->SetVisible(false);
    m_Fightskill->SetPosition({0, -160});
    m_Root.AddChild(m_Fightskill);

    m_Fightitem = std::make_shared<Image>(RESOURCE_DIR"/Fight/Fightitembox.png");
    m_Fightitem->SetZIndex(53);
    m_Fightitem->SetVisible(false);
    m_Fightitem->SetPosition({0, -60});
    m_Root.AddChild(m_Fightitem);

    m_PlayerHPimage = std::make_shared<Image>(RESOURCE_DIR"/Fight/GreenHealth.png");
    m_PlayerHPimage->SetZIndex(52);
    m_PlayerHPimage->SetVisible(false);
    m_PlayerHPimage->SetPosition({63, -9});
    m_Root.AddChild(m_PlayerHPimage);

    m_EnemyHPimage = std::make_shared<Image>(RESOURCE_DIR"/Fight/GreenHealth.png");
    m_EnemyHPimage->SetZIndex(52);
    m_EnemyHPimage->SetVisible(false);
    m_EnemyHPimage->SetPosition({-217, 260});
    m_Root.AddChild(m_EnemyHPimage);

    m_PlayerPokemon = std::make_shared<Pokemon>("004", 0);
    m_PlayerPokemon->SetZIndex(52);
    m_PlayerPokemon->SetVisible(false);
    m_PlayerPokemon->SetPosition({-210, -10});
    m_Root.AddChild(m_PlayerPokemon);

    m_EnemyPokemon = std::make_shared<Pokemon>("007", 1);
    m_EnemyPokemon->SetZIndex(52);
    m_EnemyPokemon->SetVisible(false);
    m_EnemyPokemon->SetPosition({210, 230});
    m_Root.AddChild(m_EnemyPokemon);

    m_PlayerHP = std::make_shared<Text>();
    m_PlayerHP->SetZIndex(52);
    m_PlayerHP->SetVisible(false);
    m_PlayerHP->SetPosition({170, -60});
    m_PlayerHP->SetText(
            std::to_string(m_PlayerPokemon->GetHP()) + " / " + std::to_string(m_PlayerPokemon->GetHP()));
    m_Root.AddChild(m_PlayerHP);

    m_PlayerName = std::make_shared<Text>();
    m_PlayerName->SetZIndex(52);
    m_PlayerName->SetVisible(false);
    m_PlayerName->SetPosition({175, 25});
    m_PlayerName->SetText(m_PlayerPokemon->GetName());
    m_Root.AddChild(m_PlayerName);

    m_PokemonBag = std::make_shared<PokemonBag>();
    m_PokemonBag->addPomekon(m_PlayerPokemon);

    m_EnemyName = std::make_shared<Text>();
    m_EnemyName->SetZIndex(52);
    m_EnemyName->SetVisible(false);
    m_EnemyName->SetPosition({-110, 295});
    m_EnemyName->SetText(m_EnemyPokemon->GetName());
    m_Root.AddChild(m_EnemyName);

    m_PlayerPokeInfo = std::make_shared<Text>();
    m_PlayerPokeInfo->SetZIndex(54);
    m_PlayerPokeInfo->SetVisible(false);
    m_PlayerPokeInfo->SetPosition({-500, -70});
    m_PlayerPokeInfo->SetDrawable(std::make_unique<Util::Text>(
            RESOURCE_DIR"/text.ttf",30,
            "IV:"+std::to_string(m_PlayerPokemon->GetIV())+"\n"+
            "HP:"+std::to_string(m_PlayerPokemon->GetHP())+"\n"+
            "Attack:"+std::to_string(m_PlayerPokemon->GetAttack())+"\n"+
            "Defence:"+std::to_string(m_PlayerPokemon->GetDefence())+"\n"+
            "Special:"+std::to_string(m_PlayerPokemon->GetSpecial())+"\n"+
            "Speed:"+std::to_string(m_PlayerPokemon->GetSpeed()),
            Util::Color::FromName(Util::Colors::WHITE)));
    m_Root.AddChild(m_PlayerPokeInfo);

    m_EnemyPokeInfo = std::make_shared<Text>();
    m_EnemyPokeInfo->SetZIndex(54);
    m_EnemyPokeInfo->SetVisible(false);
    m_EnemyPokeInfo->SetPosition({500, 200});
    m_EnemyPokeInfo->SetDrawable(std::make_unique<Util::Text>(
            RESOURCE_DIR"/text.ttf",30,
            "IV:"+std::to_string(m_EnemyPokemon->GetIV())+"\n"+
            "HP:"+std::to_string(m_EnemyPokemon->GetHP())+"\n"+
            "Attack:"+std::to_string(m_EnemyPokemon->GetAttack())+"\n"+
            "Defence:"+std::to_string(m_EnemyPokemon->GetDefence())+"\n"+
            "Special:"+std::to_string(m_EnemyPokemon->GetSpecial())+"\n"+
            "Speed:"+std::to_string(m_EnemyPokemon->GetSpeed()),
            Util::Color::FromName(Util::Colors::WHITE)));
    m_Root.AddChild(m_EnemyPokeInfo);
    //endregion

    m_TB = std::make_shared<TextBox>();
    m_TB->SetVisible(false);
    m_Root.AddChildren(m_TB->GetChildren());

    tempBox = std::make_shared<TextBox>();
    tempBox->SetVisible(false);
    m_Root.AddChildren(tempBox->GetChildren());


    std::vector<std::vector<std::string>> tempImagePathses;
    tempImagePathses.resize(4);
    tempImagePathses[0].push_back(RESOURCE_DIR"/Charactor/playerBack_2.png");
    tempImagePathses[0].push_back(RESOURCE_DIR"/Charactor/playerBack_1.png");
    tempImagePathses[0].push_back(RESOURCE_DIR"/Charactor/playerBack_3.png");
    tempImagePathses[0].push_back(RESOURCE_DIR"/Charactor/playerBack_1.png");
    tempImagePathses[1].push_back(RESOURCE_DIR"/Charactor/playerFront_2.png");
    tempImagePathses[1].push_back(RESOURCE_DIR"/Charactor/playerFront_1.png");
    tempImagePathses[1].push_back(RESOURCE_DIR"/Charactor/playerFront_3.png");
    tempImagePathses[1].push_back(RESOURCE_DIR"/Charactor/playerFront_1.png");
    tempImagePathses[2].push_back(RESOURCE_DIR"/Charactor/playerLeft_2.png");
    tempImagePathses[2].push_back(RESOURCE_DIR"/Charactor/playerLeft_1.png");
    tempImagePathses[3].push_back(RESOURCE_DIR"/Charactor/playerRight_2.png");
    tempImagePathses[3].push_back(RESOURCE_DIR"/Charactor/playerRight_1.png");
    Player = std::make_shared<Character>(tempImagePathses);
    Player->SetCurrentImage(1);
    Player->GetImage()->SetZIndex(50);
    Player->GetImage()->SetPosition({36, -36});
    Player->GetImage()->SetVisible(false);
    m_Root.AddChild(Player->GetImage());


    tempImagePathses.clear();
    tempImagePathses.resize(1);
    tempImagePathses.push_back({RESOURCE_DIR"/Charactor/enemyfront_1.png"});
    NPC_Bromance = std::make_shared<Character>(tempImagePathses);

    m_CurrentState = State::HOME;
}