#include "App.hpp"

#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

void App::Fight() {
    //Looking for position
//    if (Util::Input::IsKeyPressed(Util::Keycode::KP_ENTER) || Util::Input::IsKeyPressed(Util::Keycode::RETURN)){
//        LOG_DEBUG("{},{}",Util::Input::GetCursorPosition().x,Util::Input::GetCursorPosition().y);
//    }

    if(m_FightLoad1_1->GetPosition().x!=720 && m_FightLoad1_1->GetVisibility()) {
        m_FightLoad1_1->SetPosition({m_FightLoad1_1->GetPosition().x + 10, 0});
        m_FightLoad1_2->SetPosition({m_FightLoad1_2->GetPosition().x - 10, 0});
    }
    else{
        m_FightLoad1_1->SetPosition({-720,0});
        m_FightLoad1_2->SetPosition({720,0});
        m_FightLoad1_1->SetVisible(false);
        m_FightLoad1_2->SetVisible(false);
        m_FightBG->SetVisible(true);
        m_arrow->SetVisible(true);
        m_BG->SetVisible(true);
    }
//    if (!m_FightLoad1_1->GetVisibility()){
//        m_FightBG->SetVisible(true);
//        m_arrow->SetVisible(true);
//    }

    //Fight select 技能(-25,-200) 精靈(135,-200)
    //             道具(-25,-300) 逃跑(135,-300)
    if(Util::Input::IsKeyPressed(Util::Keycode::UP) && m_arrow->GetPosition().y!=-200){
        m_arrow->SetPosition({m_arrow->GetPosition().x,m_arrow->GetPosition().y+100});
    }
    else if(Util::Input::IsKeyPressed(Util::Keycode::DOWN) && m_arrow->GetPosition().y!=-300){
        m_arrow->SetPosition({m_arrow->GetPosition().x,m_arrow->GetPosition().y-100});
    }
    else if(Util::Input::IsKeyPressed(Util::Keycode::RIGHT) && m_arrow->GetPosition().x!=135){
        m_arrow->SetPosition({m_arrow->GetPosition().x+160,m_arrow->GetPosition().y});
    }
    else if(Util::Input::IsKeyPressed(Util::Keycode::LEFT) && m_arrow->GetPosition().x!=-25){
        m_arrow->SetPosition({m_arrow->GetPosition().x-160,m_arrow->GetPosition().y});
    }

    //進入技能選單
    if (!m_Fightskill->GetVisibility() && Util::Input::IsKeyPressed(Util::Keycode::Z)
        && m_arrow->GetPosition().x==-25 && m_arrow->GetPosition().y==-200){
        m_arrow->SetVisible(false);
        m_Fightskill->SetVisible(true);
    }
    //逃跑
    else if (!m_Fightskill->GetVisibility() && Util::Input::IsKeyPressed(Util::Keycode::Z)
        && m_arrow->GetPosition().x==135 && m_arrow->GetPosition().y==-300){
        m_FightBG->SetVisible(false);
        m_FightLoad1_1->SetVisible(false);
        m_FightLoad1_2->SetVisible(false);
        m_Fightskill->SetVisible(false);
        m_arrow->SetVisible(false);
        m_CurrentState = State::UPDATE;
    }
    //返回
    if (m_Fightskill->GetVisibility() && Util::Input::IsKeyPressed(Util::Keycode::X)){
        m_Fightskill->SetVisible(false);
        m_arrow->SetVisible(true);
        m_arrow->SetPosition({-25,-200});
    }

    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }

    m_Root.Update();
}