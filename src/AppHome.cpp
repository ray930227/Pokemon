#include "App.hpp"

#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

void App::Home() {
    LOG_TRACE("Home");
    if (Util::Input::IsKeyPressed(Util::Keycode::KP_ENTER)){
        m_AnimatedText->SetLooping(false);
        m_AnimatedText->SetVisible(false);
        m_BG=std::make_shared<Object>(RESOURCE_DIR"/Background/WhiteBG.png");
        m_BG->SetPosition({0,0});
        m_BG->SetZIndex(0);
        m_BG->SetVisible(true);
        m_Root.AddChild(m_BG);
        m_CurrentState = State::INIT;
    }
    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }

    m_Root.Update();
}