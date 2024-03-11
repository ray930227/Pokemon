#include "App.hpp"

#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

void App::Home() {
    LOG_TRACE("Home");
    if (Util::Input::IsKeyPressed(Util::Keycode::KP_ENTER) || Util::Input::IsKeyPressed(Util::Keycode::RETURN)){
        m_AnimatedText->SetLooping(false);
        m_AnimatedText->SetVisible(false);

        m_WhiteBG->SetVisible(true);

        m_TB->SetVisible(true);
        m_TB->ReadLines(RESOURCE_DIR"/Lines/OpeningLine.txt");

        m_CurrentState = State::INIT;
    }
    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }

    m_Root.Update();
}