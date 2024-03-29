#include "App.hpp"

void App::Loading() {
    switch (m_CurrentLoading) {
        case LoadingID::INTO:
            if (m_FightLoad1_1->GetPosition().x != 720 && m_FightLoad1_1->GetVisibility()) {
                m_FightLoad1_1->Move({15, 0});
                m_FightLoad1_2->Move({-15, 0});
            } else {
                m_WhiteBG->SetVisible(true);
                m_WhiteBG->SetZIndex(51);
                m_tempImage->SetVisible(true);
                m_tempImage->SetZIndex(52);
                m_EnemyPokemon->SetVisible(true);
                if (m_tempImage->GetPosition().x != -210) {
                    m_tempImage->Move({-10, 0});
                    m_EnemyPokemon->Move({10, 0});
                } else {
                    m_TB->SetVisible(true);
                    m_FightLoad1_1->SetPosition({-720, 0});
                    m_FightLoad1_2->SetPosition({720, 0});
                    m_FightLoad1_1->SetVisible(false);
                    m_FightLoad1_2->SetVisible(false);
                    m_CurrentLoading = LoadingID::TEXT;
                }
            }
            break;
        case LoadingID::TEXT:
            if (m_TB->GetText().find("<WildPokemon>") < m_TB->GetText().size()) {
                std::string tempStr = m_TB->GetText();
                tempStr.replace(tempStr.begin() + tempStr.find("<WildPokemon>"),
                                tempStr.begin() + tempStr.find("<WildPokemon>") + 13,
                                m_EnemyPokemon->GetName());
                m_TB->SetText(tempStr);
            }
            if (m_TB->GetText().find("<PlayerPokemon>") < m_TB->GetText().size()) {
                std::string tempStr = m_TB->GetText();
                tempStr.replace(tempStr.begin() + tempStr.find("<PlayerPokemon>"),
                                tempStr.begin() + tempStr.find("<PlayerPokemon>") + 15,
                                m_PlayerPokemon->GetName());
                m_TB->SetText(tempStr);
            }
            switch (m_TB->GetLineIndex()) {
                case 1:
                    if (m_TB->GetVisibility() && (Util::Input::IsKeyDown(Util::Keycode::Z))) {
                        m_TB->Next();
                    }
                    m_PlayerBalls->SetVisible(true);
                    break;
                case 2:
                    m_PlayerBalls->SetVisible(false);
                    m_EnemyHPUI->SetVisible(true);
                    m_EnemyHPimage->SetVisible(true);
                    m_EnemyPokeName->SetVisible(true);
                    if (m_PlayerPokemon->GetVisibility() && m_TB->GetVisibility() && (Util::Input::IsKeyDown(Util::Keycode::Z))) {
                        m_TB->Next();
                    }
                    if (m_tempImage->GetPosition().x!=-620){
                        m_tempImage->Move({-10,0});
                    }
                    else{
                        m_BallAnimation->SetScale({1.3,1.3});
                        m_BallAnimation->SetVisible(true);
                        m_BallAnimation->Play();
                        if (m_BallAnimation->GetCurrentFrameIndex()==3){
                            m_BallAnimation->SetVisible(false);
                            m_PlayerPokemon->SetVisible(true);
                            m_PlayerHPUI->SetVisible(true);
                            m_PlayerHPimage->SetVisible(true);
                            m_PlayerPokeName->SetVisible(true);
                            m_PlayerHP->SetVisible(true);
                        }
                        if (!m_TB->GetVisibility()){
                            m_arrow->SetVisible(true);
                            m_PlayerPokeInfo->SetVisible(true);
                            m_EnemyPokeInfo->SetVisible(true);
                            m_BallAnimation->SetCurrentFrame(0);
                            m_CurrentState = State::FIGHT;
                        }
                    }
                    break;
            }
            if (!m_TB->GetVisibility()){
                m_FightBG->SetVisible(true);
            }
            break;
        case LoadingID::NONE:
            break;
    }

    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
    m_Root.Update();
}