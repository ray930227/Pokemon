#include "App.hpp"

#include "Util/Logger.hpp"
#include "Util/Text.hpp"

void App::Start() {
    LOG_TRACE("Start");
    std::vector<std::string> tempText;
    for(int i=100;i>=10;i-=10){
        tempText.push_back(RESOURCE_DIR"/Start/press enter to start"+std::to_string(i)+"%.png");
    }
    for(int i=20;i<100;i+=10){
        tempText.push_back(RESOURCE_DIR"/Start/press enter to start"+std::to_string(i)+"%.png");
    }
    m_AnimatedText=std::make_shared<GIF>(tempText);
    m_AnimatedText->SetZIndex(10);
    m_AnimatedText->SetLooping(true);
    m_AnimatedText->SetInterval(100);
    m_AnimatedText->Play();
    m_Root.AddChild(m_AnimatedText);

    m_BG=std::make_shared<Image>(RESOURCE_DIR"/Background/WhiteBG.png");
    m_BG->SetZIndex(0);
    m_BG->SetVisible(false);
    m_Root.AddChild(m_BG);

    m_BlackBG=std::make_shared<Image>(RESOURCE_DIR"/Background/BlackBG.png");
    m_BlackBG->SetZIndex(0);
    m_BlackBG->SetVisible(true);
    m_BlackBG->SetPosition({0,0});
    m_Root.AddChild(m_BlackBG);

    //Fight
    m_FightLoad1_1=std::make_shared<Image>(RESOURCE_DIR"/Fight/Fightloading1_1.png");
    m_FightLoad1_1->SetZIndex(51);
    m_FightLoad1_1->SetVisible(false);
    m_FightLoad1_1->SetPosition({-720,0});

    m_Root.AddChild(m_FightLoad1_1);
    m_FightLoad1_2=std::make_shared<Image>(RESOURCE_DIR"/Fight/Fightloading1_2.png");
    m_FightLoad1_2->SetZIndex(51);
    m_FightLoad1_2->SetVisible(false);
    m_FightLoad1_2->SetPosition({720,0});
    m_Root.AddChild(m_FightLoad1_2);

    m_FightBG=std::make_shared<Image>(RESOURCE_DIR"/Fight/FightBG.png");
    m_FightBG->SetZIndex(51);
    m_FightBG->SetVisible(false);
    m_FightBG->SetPosition({0,0});
    m_Root.AddChild(m_FightBG);

    m_arrow=std::make_shared<Image>(RESOURCE_DIR"/Fight/arrow.png");
    m_arrow->SetZIndex(54);
    m_arrow->SetVisible(false);
    m_arrow->SetPosition({-25,-200});
    m_Root.AddChild(m_arrow);

    m_Fightskill=std::make_shared<Image>(RESOURCE_DIR"/Fight/Fightskillbox.png");
    m_Fightskill->SetZIndex(53);
    m_Fightskill->SetVisible(false);
    m_Fightskill->SetPosition({0,-160});
    m_Root.AddChild(m_Fightskill);

    m_Fightitem=std::make_shared<Image>(RESOURCE_DIR"/Fight/Fightitembox.png");
    m_Fightitem->SetZIndex(53);
    m_Fightitem->SetVisible(false);
    m_Fightitem->SetPosition({0,-60});
    m_Root.AddChild(m_Fightitem);

    m_PlayerHP=std::make_shared<Image>(RESOURCE_DIR"/Fight/GreenHealth.png");
    m_PlayerHP->SetZIndex(52);
    m_PlayerHP->SetVisible(false);
    m_PlayerHP->SetPosition({63,-9});
    m_Root.AddChild(m_PlayerHP);

    m_EnemyHP=std::make_shared<Image>(RESOURCE_DIR"/Fight/GreenHealth.png");
    m_EnemyHP->SetZIndex(52);
    m_EnemyHP->SetVisible(false);
    m_EnemyHP->SetPosition({-217,260});
    m_Root.AddChild(m_EnemyHP);

    m_PlayerPokemon=std::make_shared<Image>(RESOURCE_DIR"/Pokemon/Pokemonback/Pokemonback004.png");
    m_PlayerPokemon->SetZIndex(51);
    m_PlayerPokemon->SetVisible(false);
    m_PlayerPokemon->SetPosition({-210,-10});
    m_Root.AddChild(m_PlayerPokemon);

    std::vector<std::string> Enemypoke;
    Enemypoke.push_back(RESOURCE_DIR"/Pokemon/Pokemonfront/Pokemonfront007.png");
    Enemypoke.push_back(RESOURCE_DIR"/Pokemon/Pokemonmove/Pokemonmove007.png");
    m_EnemyPokemon=std::make_shared<GIF>(Enemypoke);
    m_EnemyPokemon->SetZIndex(51);
    m_EnemyPokemon->SetLooping(true);
    m_EnemyPokemon->SetVisible(false);
    m_EnemyPokemon->SetInterval(1500);
    m_EnemyPokemon->SetPosition({210,230});
    m_EnemyPokemon->Play();
    m_Root.AddChild(m_EnemyPokemon);
    //----------------------------------------------------------------------------------------
    m_TB=std::make_shared<TextBox>();
    m_TB->SetVisible(false);
    m_Root.AddChildren(m_TB->GetChildren());

    tempBox=std::make_shared<TextBox>();
    tempBox->SetVisible(false);
    m_Root.AddChildren(tempBox->GetChildren());

    Player=std::make_shared<Character>();
    Player->SetZIndex(50);
    Player->SetPosition({36,-36});
    Player->SetVisible(false);
    m_Root.AddChild(Player);

    NPC_Bromance=std::make_shared<Character>();

    m_CurrentState = State::HOME;
}