#include "App.hpp"

#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

void App::Home() {
    LOG_TRACE("Home");
    if (Util::Input::IsKeyPressed(Util::Keycode::KP_ENTER)){
        m_AnimatedText->SetLooping(false);
        m_AnimatedText->SetVisible(false);
        m_CurrentState = State::INIT;
    }
    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }

    m_Root.Update();
}