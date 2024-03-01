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
    m_AnimatedText=std::make_shared<Object>(tempText);
    m_AnimatedText->SetVisible(true);
    m_AnimatedText->SetPosition({0,0});
    m_AnimatedText->SetZIndex(10);
    m_AnimatedText->SetLooping(true);
    m_AnimatedText->SetInterval(100);
    m_AnimatedText->Play();
    m_Root.AddChild(m_AnimatedText);
    m_CurrentState = State::HOME;
}