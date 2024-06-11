#include "App.hpp"

void App::ReadSave() {
    if (m_TB->GetVisibility()) {
        if (Util::Input::IsKeyDown(Util::Keycode::Z)) {
            m_TB->SetVisible(false);
        }
    } else if (Util::Input::IsKeyDown(Util::Keycode::UP)) {
        m_Arrow->SetPosition({-300, 290});
    } else if (Util::Input::IsKeyDown(Util::Keycode::DOWN)) {
        m_Arrow->SetPosition({-300, 218});
    } else if (Util::Input::IsKeyDown(Util::Keycode::Z)) {
        m_Arrow->SetVisible(false);
        m_ReadSaveBG->SetVisible(false);
        if (m_Arrow->GetPosition().y == 290) {
            m_WhiteBG->SetVisible(true);
            m_TB->SetVisible(true);
            m_TB->ReadLines(RESOURCE_DIR"/Lines/OpeningLine.txt");
            m_tempImage->SetVisible(true);
            m_CurrentState = State::INIT;
        } else {
            std::ifstream file(RESOURCE_DIR"/Save/CharacterData.txt", std::ios::in);
            std::string tempStr;
            if (std::getline(file, tempStr)) {
                file.close();
                m_SettingUI->Read(Player, NPC_Bromance, m_ComputerUI, m_MapSystem);
                m_MapSystem->SetVisible(true);
                Player->GetImage()->SetVisible(true);
                Player->SetCurrentImagePath(0);
                DisplacementCount = 0;
                m_BGM->LoadMedia(RESOURCE_DIR"/BGM/PalletTown.mp3");
                m_BGM->Play();
                m_CurrentState = State::UPDATE;
            } else {
                m_Arrow->SetVisible(true);
                m_ReadSaveBG->SetVisible(true);
                file.close();
                m_TB->SetVisible(true);
                m_TB->SetText("沒有存檔!!!");
            }
        }

    }

    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }

    m_Root.Update();
}