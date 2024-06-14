#include "App.hpp"

void App::Home() {
    LOG_TRACE("Home");
    if (m_OpeningAnimationCount == 28) {
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
        m_Player->SetName("Player");
        m_NPCBromance->SetName("Bromance");
        m_CurrentState = State::INIT;
    }
    if ((m_OpeningAnimationCount == 635 && Util::Input::IsKeyPressed(Util::Keycode::Z)) || Util::Input::IsKeyDown(Util::Keycode::F2)) {
        m_OpeningAnimation->SetVisible(false);

        m_Arrow->SetVisible(true);
        m_ReadSaveBG->SetVisible(true);
        m_CurrentState = State::READ_SAVE;
    }
    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }

    m_Root.Update();
}