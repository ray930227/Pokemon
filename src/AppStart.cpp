#include "App.hpp"

#include "Util/Logger.hpp"

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

    m_FightLoad1_1=std::make_shared<Image>(RESOURCE_DIR"/Background/Fightloading1_1.png");
    m_FightLoad1_1->SetZIndex(52);
    m_FightLoad1_1->SetVisible(false);
    m_FightLoad1_1->SetPosition({-720,0});

    m_Root.AddChild(m_FightLoad1_1);
    m_FightLoad1_2=std::make_shared<Image>(RESOURCE_DIR"/Background/Fightloading1_2.png");
    m_FightLoad1_2->SetZIndex(52);
    m_FightLoad1_2->SetVisible(false);
    m_FightLoad1_2->SetPosition({720,0});
    m_Root.AddChild(m_FightLoad1_2);

    m_FightBG=std::make_shared<Image>(RESOURCE_DIR"/Background/Fightselectbox.png");
    m_FightBG->SetZIndex(51);
    m_FightBG->SetVisible(false);
    m_FightBG->SetPosition({0,-249});
    m_Root.AddChild(m_FightBG);

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