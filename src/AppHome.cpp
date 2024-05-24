#include "App.hpp"

void App::Home() {
    LOG_TRACE("Home");
    if(m_OpeningAnimationCount==28){
        m_BGM->Play();
    }
    if (m_OpeningAnimationCount < 635) {
        m_OpeningAnimationCount++;
        m_OpeningAnimation->SetDrawable(std::make_shared<Util::Image>(
                RESOURCE_DIR"/OpeningAnimation/frame_" + std::to_string(m_OpeningAnimationCount) + ".jpg"));
    }
    if (m_OpeningAnimationCount == 286) {
        m_BGM->LoadMedia(RESOURCE_DIR"/BGM/Opening.mp3");
        m_BGM->Play();
    }
    if (Util::Input::IsKeyPressed(Util::Keycode::F1)) {
        m_OpeningAnimation->SetVisible(false);
        Player->SetName("Player");
        NPC_Bromance->SetName("Bromance");
        m_CurrentState = State::INIT;
    }
    if (m_OpeningAnimationCount==635 && Util::Input::IsKeyPressed(Util::Keycode::Z) ) {
        m_OpeningAnimation->SetVisible(false);
        m_WhiteBG->SetVisible(true);

        m_TB->SetVisible(true);
        m_TB->ReadLines(RESOURCE_DIR"/Lines/OpeningLine.txt");

        m_tempImage->SetVisible(true);

        m_CurrentState = State::INIT;
    }
    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }

    m_Root.Update();
}