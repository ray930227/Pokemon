#include "App.hpp"

void App::Loading() {
    switch (m_CurrentLoading) {
        case LoadingID::INTO:
            if (m_LoadingUI->GetVisibility()) {
                m_LoadingUI->StartLoading();
            } else {
                m_WhiteBG->SetVisible(true);
                m_WhiteBG->SetZIndex(51);
                m_FightMainUI->SetEnemyPokeImage(RESOURCE_DIR"/Pokemon/PokeImage/Pokemonfront" +
                                                 Enemy->GetPokemonBag()->GetPokemons()[0]->GetID() + ".png");
                m_FightMainUI->SetPlayerPokeImage(RESOURCE_DIR"/Pokemon/PokeImage/Pokemonback" +
                                                  Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetID() +
                                                  ".png");
                m_LoadingUI->LoadText(Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetName(),
                                      Enemy->GetPokemonBag()->GetPokemons()[0]->GetName());
                m_FightMainUI->SetPlayerVisible(true);
                m_FightMainUI->SetEnemyPokeVisible(true);
                if (m_FightMainUI->BeginMoving()) {
                    m_SFX->Play("PokeSound"+Enemy->GetPokemonBag()->GetPokemons()[0]->GetID());
                    m_LoadingUI->Next();
                    m_CurrentLoading = LoadingID::TEXT;
                }
            }
            break;
        case LoadingID::TEXT:
            switch (m_LoadingUI->GetCurrentIndex()) {
                case 2:
                    m_FightMainUI->SetPlayerBallVisible(true);
                    m_FightMainUI->SetBallsImage(
                            RESOURCE_DIR"/Fight/PlayerBall" + std::to_string(Player->GetPokemonBag()->size()) + ".png");
                    if (Util::Input::IsKeyDown(Util::Keycode::Z)) {
                        m_FightMainUI->SetBallAnimationVisible(true);
                        m_FightMainUI->SetPlayerPokeScale({0.5, 0.5});
                        m_LoadingUI->Next();
                    }
                    break;
                case 3:
                    m_FightMainUI->SetTextHP(std::to_string(
                            Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetCurrentHP()) +
                                             " / " +
                                             std::to_string(
                                                     Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetHP()));
                    m_FightMainUI->SetTextPlayerPokeName(
                            Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetName() + " LV:" +
                            std::to_string(Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetLV()));
                    m_FightMainUI->SetTextEnemyPokeName(Enemy->GetPokemonBag()->GetPokemons()[0]->GetName() + " LV:" +
                                                        std::to_string(
                                                                Enemy->GetPokemonBag()->GetPokemons()[0]->GetLV()));
                    m_FightSkillUI->SetText(Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetSkill());
                    m_FightMainUI->SetPlayerBallVisible(false);
                    m_FightMainUI->SetEnemyHPUIVisible(true);
                    m_FightMainUI->SetEnemyPokeNameVisible(true);
                    if (m_FightMainUI->GetPlayerPokeScale().x < 1 && m_FightMainUI->EndMoving()) {
                        if (m_FightMainUI->GetPlayerPokeScale().x > 0.95){
                            m_SFX->Play("PokeSound"+Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetID());
                        }
                        m_FightMainUI->ZoomPlayerImage();
                        m_FightMainUI->SetBallAnimationVisible(false);
                        m_FightMainUI->SetPlayerPokeVisible(true);
                        m_FightMainUI->SetPlayerHPUIVisible(true);
                        m_FightMainUI->SetPlayerPokeNameVisible(true);
                        m_FightMainUI->SetPlayerHPTextVisible(true);
                    } else if (m_FightMainUI->GetPlayerPokeScale().x >= 1) {
                        m_FightMainUI->SetPlayerPokeScale({1.0, 1.0});
                        if (Util::Input::IsKeyDown(Util::Keycode::Z)) {
                            m_LoadingUI->Next();
                        }
                    }
                    break;
            }
            if (!m_LoadingUI->GetTBVisibility()) {
                m_FightMainUI->ReSetBallAnimation();
                m_FightMainUI->SetArrowVisible(true);
                m_FightMainUI->SetFightBGVisible(true);
                m_PlayerPokeInfo->SetVisible(true);
                m_EnemyPokeInfo->SetVisible(true);
                m_CurrentFighting = FightID::HOME;
                m_CurrentState = State::FIGHT;
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