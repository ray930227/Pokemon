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
                m_EnemyPokemonImage->SetVisible(true);
                m_TB->SetVisible(true);
                if (m_tempImage->GetPosition().x != -210) {
                    m_tempImage->Move({-10, 0});
                    m_EnemyPokemonImage->Move({10, 0});
                } else {
                    m_TB->Next();
                    m_FightLoad1_1->SetPosition({-720, 0});
                    m_FightLoad1_2->SetPosition({720, 0});
                    m_FightLoad1_1->SetVisible(false);
                    m_FightLoad1_2->SetVisible(false);
                    m_CurrentLoading = LoadingID::TEXT;
                }
            }
            break;
        case LoadingID::TEXT:
            switch (m_TB->GetLineIndex()) {
                case 2:
                    if (m_TB->GetVisibility() && (Util::Input::IsKeyDown(Util::Keycode::Z))) {
                        m_TB->Next();
                        m_BallAnimation->Reset();
                        m_BallAnimation->SetVisible(true);
                        m_BallAnimation->Play();
                        m_PlayerPokemonImage->SetScale({0.5, 0.5});
                    }
                    m_PlayerBalls->SetImage(
                            RESOURCE_DIR"/Fight/PlayerBall" + std::to_string(Player->GetPokemonBag()->size()) + ".png");
                    m_PlayerBalls->SetVisible(true);
                    break;
                case 3:
                    m_PlayerHP->SetText(
                            std::to_string(
                                    Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetCurrentHP()) +
                            " / " +
                            std::to_string(Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetHP()));
                    m_PlayerPokeName->SetText(
                            Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetName() + " LV:" +
                            std::to_string(Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetLV()));
                    m_EnemyPokeName->SetText(
                            m_EnemyPokemon->GetName() + " LV:" + std::to_string(m_EnemyPokemon->GetLV()));
                    m_FightSkillUI->SetText(Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetSkill());
                    m_PlayerBalls->SetVisible(false);
                    m_EnemyHPUI->SetVisible(true);
                    m_EnemyHPimage->SetVisible(true);
                    m_EnemyPokeName->SetVisible(true);
                    if (m_PlayerPokemonImage->GetScale().x >= 1 && m_TB->GetVisibility() &&
                        (Util::Input::IsKeyDown(Util::Keycode::Z))) {
                        m_TB->Next();
                    }
                    if (m_tempImage->GetPosition().x != -620) {
                        m_tempImage->Move({-10, 0});
                    } else {
                        if (m_BallAnimation->IsAnimationEnds()) {
                            if (m_PlayerPokemonImage->GetScale().x <= 1.0) {
                                m_PlayerPokemonImage->SetScale(
                                        {m_PlayerPokemonImage->GetScale().x + 0.05,
                                         m_PlayerPokemonImage->GetScale().y + 0.05});
                            }
                            m_BallAnimation->SetVisible(false);
                            m_PlayerPokemonImage->SetVisible(true);
                            m_PlayerHPUI->SetVisible(true);
                            m_PlayerHPimage->SetVisible(true);
                            m_PlayerPokeName->SetVisible(true);
                            m_PlayerHP->SetVisible(true);
                        }
                        if (!m_TB->GetVisibility()) {
                            m_arrow->SetVisible(true);
                            m_PlayerPokeInfo->SetVisible(true);
                            m_EnemyPokeInfo->SetVisible(true);
                            m_BallAnimation->SetCurrentFrame(0);
                            m_CurrentFighting = FightID::HOME;
                            m_CurrentState = State::FIGHT;
                        }
                    }
                    break;
            }
            if (!m_TB->GetVisibility()) {
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