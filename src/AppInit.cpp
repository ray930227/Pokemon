#include "App.hpp"

#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

void App::Init() {


    if (Util::Input::IsKeyPressed(Util::Keycode::KP_ENTER)){
        LOG_DEBUG(Util::Input::GetCursorPosition().x);

    }
    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
    m_Root.Update();
}