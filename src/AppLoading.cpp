#include "App.hpp"

void App::Loading() {
    switch (m_CurrentLoading) {
        //region INIT
        case LoadingID::INIT:
            for (size_t i = 0; i < m_Player->GetPokemonBag()->Size(); i++) {
                if (!m_Player->GetPokemonBag()->GetPokemons()[i]->IsPokemonDying()) {
                    m_CurrentPlayerPokemon = i;
                    break;
                }
            }
            m_CurrentNPCPokemon = 0;
            m_IsChangePokemon = false;
            m_SuccessCatch = false;
            m_BGM->LoadMedia(RESOURCE_DIR"/BGM/Battle.mp3");
            m_BGM->Play();
            m_LoadingUI->RandomMode();
            m_FightMainUI->ReSetWildPosition();
            m_FightSkillUI->ReSetArrow();
            m_PokeBagUI->ReSetCurrentPokemon();
            m_PlayerBuff["攻擊"] = 1.0;
            m_PlayerBuff["命中率"] = 1.0;
            m_PlayerBuff["閃避率"] = 1.0;
            m_PlayerBuff["防禦"] = 1.0;
            m_PlayerBuff["特殊"] = 1.0;
            m_PlayerBuff["速度"] = 1.0;
            m_EnemyBuff["攻擊"] = 1.0;
            m_EnemyBuff["命中率"] = 1.0;
            m_EnemyBuff["閃避率"] = 1.0;
            m_EnemyBuff["防禦"] = 1.0;
            m_EnemyBuff["特殊"] = 1.0;
            m_EnemyBuff["速度"] = 1.0;

            m_CurrentLoading = LoadingID::LOADING;
            break;
            //endregion
            //region LOADING
        case LoadingID::LOADING:
            if (m_LoadingUI->GetVisibility()) {
                m_LoadingUI->StartLoading();
            } else {
                m_WhiteBG->SetVisible(true);
                m_WhiteBG->SetZIndex(51);
                m_FightMainUI->SetEnemyPokeImage(m_CurrentNPCPokemon);
                m_FightMainUI->SetPlayerPokeImage(m_CurrentPlayerPokemon);
                m_LoadingUI->LoadText(m_CurrentPlayerPokemon, m_CurrentNPCPokemon, m_IsWildPokemon);
                m_FightMainUI->SetPlayerVisible(true);
                m_FightMainUI->SetEnemyPokeVisible(true);
                if (m_FightMainUI->BeginMoving()) {
                    m_SFX->Play("PokeSound" + m_Enemy->GetPokemonBag()->GetPokemons()[m_CurrentNPCPokemon]->GetID());
                    m_LoadingUI->Next();
                    m_CurrentLoading = LoadingID::TEXT;
                }
            }
            break;
            //endregion
            //region TEXT
        case LoadingID::TEXT:
            switch (m_LoadingUI->GetCurrentIndex()) {
                case 2:
                    m_FightMainUI->SetPlayerBallVisible(true);
                    m_FightMainUI->SetBallsImage();
                    if (Util::Input::IsKeyDown(Util::Keycode::Z)) {
                        m_FightMainUI->SetBallAnimationVisible(true, true);
                        m_FightMainUI->SetPlayerPokeScale({0.5, 0.5});
                        m_FightMainUI->SetPlayerHPScale(m_CurrentPlayerPokemon);
                        m_FightMainUI->SetEnemyHPScale(m_CurrentNPCPokemon);
                        m_FightMainUI->DetectBlood();
                        m_LoadingUI->Next();
                    }
                    break;
                case 3:
                    m_FightMainUI->SetTextHP(m_CurrentPlayerPokemon);
                    m_FightMainUI->SetTextPlayerPokeName(m_CurrentPlayerPokemon);
                    m_FightMainUI->SetTextEnemyPokeName(m_CurrentNPCPokemon);
                    m_FightSkillUI->SetText(m_CurrentPlayerPokemon);
                    m_FightMainUI->SetPlayerBallVisible(false);
                    m_FightMainUI->SetEnemyHPUIVisible(true);
                    m_FightMainUI->SetEnemyPokeNameVisible(true);
                    if (m_FightMainUI->GetPlayerPokeScale().x < 1 && m_FightMainUI->EndMoving()) {
                        if (m_FightMainUI->GetPlayerPokeScale().x > 0.9) {
                            m_SFX->Play("PokeSound" +
                                        m_Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetID());
                        }
                        m_FightMainUI->ZoomImage(true);
                        m_FightMainUI->SetBallAnimationVisible(false, true);
                        m_FightMainUI->SetPlayerPokeVisible(true);
                        m_FightMainUI->SetPlayerHPUIVisible(true);
                        m_FightMainUI->SetPlayerPokeNameVisible(true);
                        m_FightMainUI->SetPlayerHPTextVisible(true);
                    } else if (m_FightMainUI->GetPlayerPokeScale().x >= 1) {
                        m_Timer++;
                        m_FightMainUI->SetPlayerPokeScale({1.0, 1.0});
                        if (m_Timer == 40) {
                            m_LoadingUI->Next();
                        }
                    }
                    break;
            }
            if (!m_LoadingUI->GetTBVisibility()) {
                m_FightMainUI->SetArrowVisible(true);
                m_FightMainUI->SetFightBGVisible(true);
                m_PlayerPokeInfo->SetVisible(true);
                m_EnemyPokeInfo->SetVisible(true);
                m_Timer = 0;
                m_FightCounter = 0;
                m_CurrentFighting = FightID::HOME;
                m_CurrentState = State::FIGHT;
            }
            break;
            //endregion
        case LoadingID::NONE:
            break;
    }

    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
    m_Root.Update();
}