#include "App.hpp"

#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"
#include "Util/BGM.hpp"

void App::Update() {
    LOG_TRACE("Update");
    if(DisplacementCount!=0){
        m_BG->Move(Displacement);
        DisplacementCount--;
        if(DisplacementCount==0){
            m_BG->SetPosition({round(m_BG->GetPosition().x),round(m_BG->GetPosition().y)});
        }
    }
    else if(Util::Input::IsKeyPressed(Util::Keycode::UP)){
        Displacement={0,-72/Player->GetSpeed()};
        DisplacementCount=Player->GetSpeed();
        Player->SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR"/Charactor/playerback.png"));
    }
    else if(Util::Input::IsKeyPressed(Util::Keycode::DOWN)){
        Displacement={0,72/Player->GetSpeed()};
        DisplacementCount=Player->GetSpeed();
        Player->SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR"/Charactor/playerfront.png"));
    }
    else if(Util::Input::IsKeyPressed(Util::Keycode::RIGHT)){
        Displacement={-72/Player->GetSpeed(),0};
        DisplacementCount=Player->GetSpeed();
        Player->SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR"/Charactor/playerright.png"));
    }
    else if(Util::Input::IsKeyPressed(Util::Keycode::LEFT)){
        Displacement={72/Player->GetSpeed(),0};
        DisplacementCount=Player->GetSpeed();
        Player->SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR"/Charactor/playerleft.png"));
    }


    if(Util::Input::IsKeyPressed(Util::Keycode::A)){
        Player->SetSpeed(5);
        LOG_DEBUG("{},{}",m_BG->GetPosition().x,m_BG->GetPosition().y);
    }

    if(Util::Input::IsKeyPressed(Util::Keycode::F)){
        m_FightLoad1_1->SetVisible(true);
        m_FightLoad1_2->SetVisible(true);
        m_FightBG->SetVisible(true);
        Util::BGM battle(RESOURCE_DIR"/BGM/Battle.mp3");
        battle.Play(1);
        battle.SetVolume(128);
        m_CurrentState = State::FIGHT;
    }
    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
    m_Root.Update();
}