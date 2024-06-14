#include "App.hpp"

void App::Init() {
    if (m_TempBox->GetVisibility()) {
        m_TempBox->InputString();
        if (Util::Input::IsKeyPressed(Util::Keycode::KP_ENTER) || Util::Input::IsKeyPressed(Util::Keycode::RETURN)) {
            m_TempBox->SetVisible(false);
            m_TB->Next();
            if (m_TB->GetLineIndex() == 11) {
                m_Player->SetName(m_TempBox->GetText());
            } else {
                m_NPCBromance->SetName(m_TempBox->GetText());
            }

        }
        if (m_TempBox->GetText().size() >= 8) {
            std::string tempStr = m_TempBox->GetText();
            tempStr.pop_back();
            m_TempBox->SetText(tempStr);
        }
    } else if (m_tempImage->GetPosition().x != 0) {
        m_tempImage->Move({-10, 0});
    } else if (Util::Input::IsKeyDown(Util::Keycode::Z)) {
        m_TB->Next();

        switch (m_TB->GetLineIndex()) {
            case 9:
                m_tempImage->SetPosition({360, 0});
                m_tempImage->SetImage(RESOURCE_DIR"/Charactor/playerWholeBody.png");
                break;
            case 10:
            case 13:
                m_TempBox->SetPosition({0, 0});
                m_TempBox->SetScale({0.5, 0.5});
                m_TempBox->SetVisible(true);
                m_TempBox->SetText(" ");
                break;
            case 12:
                m_tempImage->SetPosition({360, 0});
                m_tempImage->SetImage(RESOURCE_DIR"/Charactor/enemyWholeBody.png");
                break;
            case 15:
                m_tempImage->SetImage(RESOURCE_DIR"/Charactor/playerWholeBody.png");
                break;
        }
    }


    if (m_TB->GetText().find("<Player>") < m_TB->GetText().size()) {
        std::string tempStr = m_TB->GetText();
        tempStr.replace(tempStr.begin() + tempStr.find("<Player>"),
                        tempStr.begin() + tempStr.find("<Player>") + 8,
                        m_Player->GetName());
        m_TB->SetText(tempStr);
    }
    if (m_TB->GetText().find("<NPC_Bromance>") < m_TB->GetText().size()) {
        std::string tempStr = m_TB->GetText();
        tempStr.replace(tempStr.begin() + tempStr.find("<NPC_Bromance>"),
                        tempStr.begin() + tempStr.find("<NPC_Bromance>") + 14,
                        m_NPCBromance->GetName());
        m_TB->SetText(tempStr);
    }
    if (!m_TB->GetVisibility()) {
        m_WhiteBG->SetVisible(false);
        m_tempImage->SetVisible(false);
        m_MapSystem->SetVisible(true);
        m_MapSystem->SetPosition({72, 144});
        m_Player->GetImage()->SetVisible(true);
        m_Player->SetCurrentImagePath(0);
        m_DisplacementCount = 0;
        m_BGM->LoadMedia(RESOURCE_DIR"/BGM/PalletTown.mp3");
        m_BGM->Play();
        m_CurrentState = State::UPDATE;
    }
    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
    m_Root.Update();
}