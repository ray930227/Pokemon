#include "App.hpp"

#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

void App::Fight() {
    //Looking for position
    if (Util::Input::IsKeyPressed(Util::Keycode::KP_ENTER) || Util::Input::IsKeyPressed(Util::Keycode::RETURN)){
        LOG_DEBUG("Position:({},{})",Util::Input::GetCursorPosition().x,Util::Input::GetCursorPosition().y);
    }

    if (Util::Input::IsKeyPressed(Util::Keycode::H)){
        m_PlayerHP->SetScale({0.2,1});
    }

    if ((m_PlayerHP->GetScaledSize().x)<=91.200005){
        m_PlayerHP->SetImage(RESOURCE_DIR"/Fight/RedHealth.png");
    }

    if(m_FightLoad1_1->GetPosition().x!=720 && m_FightLoad1_1->GetVisibility()) {
        m_FightLoad1_1->SetPosition({m_FightLoad1_1->GetPosition().x + 15, 0});
        m_FightLoad1_2->SetPosition({m_FightLoad1_2->GetPosition().x - 15, 0});
    }
    else{
        m_FightLoad1_1->SetPosition({-720,0});
        m_FightLoad1_2->SetPosition({720,0});
        m_FightLoad1_1->SetVisible(false);
        m_FightLoad1_2->SetVisible(false);
        m_FightBG->SetVisible(true);
        m_arrow->SetVisible(true);
        m_PlayerHP->SetVisible(true);
        m_EnemyHP->SetVisible(true);
        m_PlayerPokemon->SetVisible(true);
        m_EnemyPokemon->SetVisible(true);
    }

    //Fight select 技能(-25,-200) 精靈(135,-200)
    //             道具(-25,-300) 逃跑(135,-300)
    if(Util::Input::IsKeyPressed(Util::Keycode::UP) && m_arrow->GetPosition().y!=-200
       && !m_Fightskill->GetVisibility() && !m_Fightitem->GetVisibility()){
        m_arrow->SetPosition({m_arrow->GetPosition().x,m_arrow->GetPosition().y+100});
    }
    else if(Util::Input::IsKeyPressed(Util::Keycode::DOWN) && m_arrow->GetPosition().y!=-300
            && !m_Fightskill->GetVisibility() && !m_Fightitem->GetVisibility()){
        m_arrow->SetPosition({m_arrow->GetPosition().x,m_arrow->GetPosition().y-100});
    }
    else if(Util::Input::IsKeyPressed(Util::Keycode::RIGHT) && m_arrow->GetPosition().x!=135
            && !m_Fightskill->GetVisibility() && !m_Fightitem->GetVisibility()){
        m_arrow->SetPosition({m_arrow->GetPosition().x+160,m_arrow->GetPosition().y});
    }
    else if(Util::Input::IsKeyPressed(Util::Keycode::LEFT) && m_arrow->GetPosition().x!=-25
            && !m_Fightskill->GetVisibility() && !m_Fightitem->GetVisibility()){
        m_arrow->SetPosition({m_arrow->GetPosition().x-160,m_arrow->GetPosition().y});
    }

    //進入技能選單
    if (!m_Fightskill->GetVisibility() && Util::Input::IsKeyPressed(Util::Keycode::Z)
        && m_arrow->GetPosition().x==-25 && m_arrow->GetPosition().y==-200){
        m_Fightskill->SetVisible(true);
        m_arrow->SetPosition({-180,-200});
    }
    //進入道具選單
    if(!m_Fightitem->GetVisibility() && Util::Input::IsKeyPressed(Util::Keycode::Z)
       && m_arrow->GetPosition().x==-25 && m_arrow->GetPosition().y==-300){
        m_Fightitem->SetVisible(true);
        m_arrow->SetPosition({-150,160});
    }
    //逃跑
    if (!m_Fightskill->GetVisibility() && !m_Fightitem->GetVisibility()
        && Util::Input::IsKeyPressed(Util::Keycode::Z)
        && m_arrow->GetPosition().x==135 && m_arrow->GetPosition().y==-300){
        m_FightBG->SetVisible(false);
        m_FightLoad1_1->SetVisible(false);
        m_FightLoad1_2->SetVisible(false);
        m_Fightskill->SetVisible(false);
        m_arrow->SetVisible(false);
        m_PlayerHP->SetVisible(false);
        m_EnemyHP->SetVisible(false);
        m_PlayerPokemon->SetVisible(false);
        m_EnemyPokemon->SetVisible(false);
        m_CurrentState = State::UPDATE;
    }
    //返回
    if (Util::Input::IsKeyPressed(Util::Keycode::X)){
        if (m_Fightskill->GetVisibility()){
            m_Fightskill->SetVisible(false);
            m_arrow->SetVisible(true);
            m_arrow->SetPosition({-25,-200});
        }
        else if (m_Fightitem->GetVisibility()){
            m_Fightitem->SetVisible(false);
            m_arrow->SetVisible(true);
            m_arrow->SetPosition({-25,-200});
        }
    }

    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }

    m_Root.Update();
}