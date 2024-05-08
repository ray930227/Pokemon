#include "App.hpp"

void App::Init() {
    if (tempBox->GetVisibility()) {
        tempBox->InputString();
        if (Util::Input::IsKeyPressed(Util::Keycode::KP_ENTER) || Util::Input::IsKeyPressed(Util::Keycode::RETURN)) {
            tempBox->SetVisible(false);
            m_TB->Next();
            if (m_TB->GetLineIndex() == 11) {
                Player->SetName(tempBox->GetText());
            } else {
                NPC_Bromance->SetName(tempBox->GetText());
            }

        }
        if (tempBox->GetText().size() >= 8) {
            std::string tempStr = tempBox->GetText();
            tempStr.pop_back();
            tempBox->SetText(tempStr);
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
                tempBox->SetPosition({0, 0});
                tempBox->SetScale({0.5, 0.5});
                tempBox->SetVisible(true);
                tempBox->SetText(" ");
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
                        Player->GetName());
        m_TB->SetText(tempStr);
    }
    if (m_TB->GetText().find("<NPC_Bromance>") < m_TB->GetText().size()) {
        std::string tempStr = m_TB->GetText();
        tempStr.replace(tempStr.begin() + tempStr.find("<NPC_Bromance>"),
                        tempStr.begin() + tempStr.find("<NPC_Bromance>") + 14,
                        NPC_Bromance->GetName());
        m_TB->SetText(tempStr);
    }
    if (!m_TB->GetVisibility()) {
        m_WhiteBG->SetVisible(false);
        m_tempImage->SetVisible(false);
        m_MapSystem->SetVisible(true);
        m_MapSystem->SetPosition({72, 144});
        Player->GetImage()->SetVisible(true);
        Player->SetCurrentImagePath(0);
        DisplacementCount = 0;
        m_BGM->LoadMedia(RESOURCE_DIR"/BGM/PalletTown.mp3");
        m_BGM->Play();

        std::shared_ptr<Pokemon> TempPokemon = std::make_shared<Pokemon>("007");
        NPC_Bromance->GetPokemonBag()->addPomekon(TempPokemon);
        std::shared_ptr<Pokemon> FirstPokemon = std::make_shared<Pokemon>("004");
        Player->GetPokemonBag()->addPomekon(FirstPokemon);
        std::shared_ptr<Pokemon> SecondPokemon = std::make_shared<Pokemon>("143");
        Player->GetPokemonBag()->addPomekon(SecondPokemon);

        m_CurrentState = State::UPDATE;
    }
    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
    m_Root.Update();
}