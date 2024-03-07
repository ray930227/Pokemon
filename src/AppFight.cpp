#include "App.hpp"

#include "Util/Input.hpp"
#include "Util/Keycode.hpp"


void App::Fight() {

    if(Util::Input::IsKeyPressed(Util::Keycode::B)){
        m_FightBG->SetVisible(false);
        m_FightLoad1_1->SetVisible(false);
        m_FightLoad1_2->SetVisible(false);
        m_CurrentState = State::UPDATE;
    }

    if(m_FightLoad1_1->GetPosition().x!=0 && m_FightLoad1_1->GetVisibility()) {
        m_FightLoad1_1->SetPosition({m_FightLoad1_1->GetPosition().x + 10, 0});
        m_FightLoad1_2->SetPosition({m_FightLoad1_2->GetPosition().x - 10, 0});
    }
    else{
        m_FightLoad1_1->SetPosition({-720,0});
        m_FightLoad1_1->SetVisible(false);
        m_FightLoad1_2->SetPosition({720,0});
        m_FightLoad1_2->SetVisible(false);
    }

    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
    m_Root.Update();
}