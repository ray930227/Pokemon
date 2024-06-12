#include "App.hpp"

void App::Fight() {
    switch (m_CurrentFighting) {
        case FightID::HOME:
            // region Home
            if (m_FightMainUI->Choose()) {
                if (m_FightMainUI->GetDecision() == "Skill") {
                    m_FightMainUI->SetArrowVisible(false);
                    m_FightSkillUI->SetVisible(true);
                    LOG_DEBUG("State:Skill");
                    m_CurrentFighting = FightID::SKILL;
                } else if (m_FightMainUI->GetDecision() == "PokePack") {
                    m_FightMainUI->SetArrowVisible(false);
                    m_PokeBagUI->SetVisible(true);
                    LOG_DEBUG("State:Pokepack");
                    m_CurrentFighting = FightID::POKEPACK;
                } else if (m_FightMainUI->GetDecision() == "BackPack") {
                    m_Fightitem->SetVisible(true);
                    m_FightMainUI->SetArrowVisible(false);
                    LOG_DEBUG("State:Backpack");
                    m_CurrentFighting = FightID::BACKPACK;
                } else if (m_FightMainUI->GetDecision() == "Run") {
                    LOG_DEBUG("Run");
                    m_FightTextUI->SetRun(isWildPokemon);
                    m_CurrentFighting = FightID::RUN;
                }
            }
            if (Enemy->GetPokemonBag()->GetPokemons()[m_CurrentNPCPokemon]->IsPokemonDying()) {
                m_CurrentFighting = FightID::WILDFINISH;
            } else if (Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->IsPokemonDying()) {
                bool Check = false;
                for (auto i: Player->GetPokemonBag()->GetPokemons()) {
                    if (!i->IsPokemonDying()) {
                        Check = true;
                        break;
                    }
                }
                m_FightMainUI->SetPlayerPokeVisible(false);
                m_FightMainUI->SetPlayerHPUIVisible(false);
                m_FightMainUI->SetPlayerHPTextVisible(false);
                m_FightMainUI->SetPlayerPokeNameVisible(false);
                m_PokeFaintedUI->SetText(Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetName());
                if (Check) {
                    m_CurrentFighting = FightID::POKEFAINTED;
                } else {
                    m_PokeFaintedUI->SetVisible(false);
                    m_FightTextUI->SetLose(Player->GetName());
                    LOG_DEBUG("Run");
                    m_CurrentEvent = EventID::ALL_POKEMON_DIE;
                    m_CurrentFighting = FightID::RUN;
                }
            }
            if (Util::Input::IsKeyDown(Util::Keycode::I)) {
                Enemy->GetPokemonBag()->GetPokemons()[m_CurrentNPCPokemon]->LevelUp();
                m_FightMainUI->SetTextEnemyPokeName(0);
                m_CurrentFighting = FightID::UPDATEINFO;
            }
            if (Util::Input::IsKeyDown(Util::Keycode::U)) {
                Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->LevelUp();
                if (Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->IsGetNewSkill()) {
                    m_ReplaceSkillUI->SetText(m_CurrentPlayerPokemon);
                    m_CurrentFighting = FightID::GETSKILL;
                } else if (Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->IsEvolution()) {
                    m_EvolutionUI->Setting(
                            Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetIDByInt());
                    m_EvolutionUI->SetVisible(true);
                    m_EvolutionUI->SetPokeVisible(false);
                    m_CurrentFighting = FightID::EVOLUTION;
                } else {
                    m_CurrentFighting = FightID::UPDATEINFO;
                }
                m_FightMainUI->SetTextPlayerPokeName(m_CurrentPlayerPokemon);
            }

            if (Util::Input::IsKeyDown(Util::Keycode::H)) {
                Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->PokemonHurt(1);
                m_FightMainUI->SetPlayerHPScale(m_CurrentPlayerPokemon);
                m_CurrentFighting = FightID::UPDATEINFO;
            }
            break;
            //endregion

        case FightID::SKILL:
            // region Skill
            m_FightSkillUI->ShowSkillInfo(m_CurrentPlayerPokemon);
            if (m_FightSkillUI->Choose(m_CurrentPlayerPokemon)) {
                IsChangePokemon = false;
                PlayerSkillChoose = m_FightSkillUI->GetDecision();
                EnemySkillChoose = Enemy->GetPokemonBag()->GetPokemons()[m_CurrentNPCPokemon]->CaculateDamge(
                        Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetType());
                IsPlayerRound=Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetSpeed() >
                              Enemy->GetPokemonBag()->GetPokemons()[m_CurrentNPCPokemon]->GetSpeed();
                m_FightSkillUI->SetVisible(false);
                LOG_DEBUG("State:Fight");
                m_CurrentFighting = FightID::FIGHT;
            }
            if (Util::Input::IsKeyDown(Util::Keycode::X)) {
                m_FightSkillUI->SetVisible(false);
                m_FightMainUI->SetArrowVisible(true);
                m_CurrentFighting = FightID::HOME;
            }
            break;
            //endregion

        case FightID::POKEPACK:
            //region PokePack
            if (m_PokeBagUI->GetVisible()) {
                m_FightTextUI->SetPokePack();
                if (Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->IsPokemonDying()) {
                    m_PokeBagUI->Run(1);
                } else {
                    m_PokeBagUI->Run(2);
                }
            } else {
                m_FightTextUI->Next();
                if (m_PokeBagUI->GetDecision() == -1) {
                    m_FightMainUI->SetArrowVisible(true);
                    m_CurrentFighting = FightID::HOME;
                } else {
                    m_PreviousPlayerPokemon = m_CurrentPlayerPokemon;
                    m_CurrentPlayerPokemon = m_PokeBagUI->GetDecision();
                    IsChangePokemon = true;
                    IsPlayerRound = false;
                    m_FightTextUI->SetChangePoke(
                            Player->GetPokemonBag()->GetPokemons()[m_PreviousPlayerPokemon]->GetName(),
                            Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetName());
                    if (Player->GetPokemonBag()->GetPokemons()[m_PreviousPlayerPokemon]->IsPokemonDying()) {
                        IsChangePokemon = false;
                        m_FightTextUI->Next();
                    }
                    m_PokeBagUI->SetVisible(false);
                    m_FightMainUI->SetArrowVisible(true);
                    m_FightSkillUI->ReSetArrow();
                    if (!IsChangePokemon) {
                        m_FightMainUI->SetPlayerPokeVisible(false);
                        m_FightMainUI->SetPlayerPokeScale({0.5, 0.5});
                        m_FightMainUI->SetBallAnimationVisible(true, true);
                    }
                    if (!IsChangePokemon) {
                        Timer = 101;
                    } else {
                        Timer = 0;
                    }
                    m_CurrentFighting = FightID::CHANGEPOKE;
                }
            }
            break;
            //endregion

        case FightID::BACKPACK:
            //region BackPack
            if (Util::Input::IsKeyDown(Util::Keycode::X)) {
                m_Fightitem->SetVisible(false);
                m_FightMainUI->SetArrowVisible(true);
                m_CurrentFighting = FightID::HOME;
            }
            break;
            //endregion

        case FightID::RUN:
            //region Run
            if (!m_FightTextUI->GetLoseVisibility() && !m_FightTextUI->GetRunVisibility()) {
                if (isWildPokemon || m_CurrentEvent == EventID::ALL_POKEMON_DIE) {
                    m_WhiteBG->SetVisible(false);
                    m_WhiteBG->SetZIndex(0);
                    m_FightMainUI->SetVisible(false);
                    m_PlayerPokeInfo->SetVisible(false);
                    m_EnemyPokeInfo->SetVisible(false);
                    m_FightMainUI->SetVisible(false);
                    m_BGM->LoadMedia(RESOURCE_DIR"/BGM/PalletTown.mp3");
                    m_BGM->Play();
                    LOG_DEBUG("State:UPDATE");
                    m_CurrentState = State::UPDATE;
                } else {
                    m_FightMainUI->SetArrowVisible(true);
                    m_CurrentFighting = FightID::HOME;
                }
            }
            if (Util::Input::IsKeyDown(Util::Keycode::Z)) {
                m_FightTextUI->Next();
            }
            break;
            //endregion

        case FightID::FIGHT:
            //region Fight
            m_FightMainUI->RunFightSystem(IsPlayerRound, IsChangePokemon, m_CurrentPlayerPokemon, m_CurrentNPCPokemon,
                                          PlayerSkillChoose, EnemySkillChoose);
//            if (IsPlayerRound) {
//                if (FightCounter == 0) {
//                    if (!Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->IsPokemonDying()) {
//                        if (Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetSkillClass()[PlayerSkillChoose] ==
//                            "變化" ||
//                            Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetSkillDamge()[PlayerSkillChoose] ==
//                            "變化") {
//                            LOG_DEBUG("Status is not ready");
//                        } else {
//                            m_SFX->Play(
//                                    "PokeSound" +
//                                    Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetID());
//                            Enemy->GetPokemonBag()->GetPokemons()[m_CurrentNPCPokemon]->PokemonHurt(
//                                    Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon], PlayerSkillChoose);
//                            Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->ReducePP(PlayerSkillChoose);
//                            m_FightMainUI->SetEnemyHPScale(m_CurrentNPCPokemon);
//                            m_FightMainUI->SetPlayerHPScale(m_CurrentPlayerPokemon);
//                            m_FightMainUI->SetTextHP(m_CurrentPlayerPokemon);
//                        }
//                    }
//                    FightCounter++;
//                } else if (!m_FightTextUI->GetPlayerVisibility() && FightCounter == 1) {
//                    if (!Enemy->GetPokemonBag()->GetPokemons()[m_CurrentNPCPokemon]->IsPokemonDying()) {
//                        m_FightTextUI->SetEnemy(m_CurrentNPCPokemon, m_CurrentPlayerPokemon, EnemySkillChoose);
//                        if (Enemy->GetPokemonBag()->GetPokemons()[m_CurrentNPCPokemon]->GetSkillClass()[EnemySkillChoose] ==
//                            "變化") {
//                            LOG_DEBUG("Status is not ready");
//                        } else {
//                            m_SFX->Play(
//                                    "PokeSound" + Enemy->GetPokemonBag()->GetPokemons()[m_CurrentNPCPokemon]->GetID());
//                            Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->PokemonHurt(
//                                    Enemy->GetPokemonBag()->GetPokemons()[m_CurrentNPCPokemon], EnemySkillChoose);
//                            Enemy->GetPokemonBag()->GetPokemons()[m_CurrentNPCPokemon]->ReducePP(EnemySkillChoose);
//                            m_FightMainUI->SetEnemyHPScale(m_CurrentNPCPokemon);
//                            m_FightMainUI->SetPlayerHPScale(m_CurrentPlayerPokemon);
//                            m_FightMainUI->SetTextHP(m_CurrentPlayerPokemon);
//                        }
//                    }
//                    FightCounter++;
//                }
//            } else {
//                if (FightCounter == 0) {
//                    if (!Enemy->GetPokemonBag()->GetPokemons()[m_CurrentNPCPokemon]->IsPokemonDying()) {
//                        if (Enemy->GetPokemonBag()->GetPokemons()[m_CurrentNPCPokemon]->GetSkillClass()[EnemySkillChoose] ==
//                            "變化") {
//                            LOG_DEBUG("Status is not ready");
//                        } else {
//                            m_SFX->Play(
//                                    "PokeSound" + Enemy->GetPokemonBag()->GetPokemons()[m_CurrentNPCPokemon]->GetID());
//                            Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->PokemonHurt(
//                                    Enemy->GetPokemonBag()->GetPokemons()[m_CurrentNPCPokemon], EnemySkillChoose);
//                            Enemy->GetPokemonBag()->GetPokemons()[m_CurrentNPCPokemon]->ReducePP(EnemySkillChoose);
//                            m_FightMainUI->SetEnemyHPScale(m_CurrentNPCPokemon);
//                            m_FightMainUI->SetPlayerHPScale(m_CurrentPlayerPokemon);
//                            m_FightMainUI->SetTextHP(m_CurrentPlayerPokemon);
//                        }
//                    }
//                    FightCounter++;
//                } else if (!m_FightTextUI->GetEnemyVisibility() && FightCounter == 1) {
//                    if (!Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->IsPokemonDying() &&
//                        !IsChangePokemon) {
//                        m_FightTextUI->SetPlayer(m_CurrentPlayerPokemon, m_CurrentNPCPokemon, PlayerSkillChoose);
//                        if (Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetSkillClass()[PlayerSkillChoose] ==
//                            "變化" ||
//                            Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetSkillDamge()[PlayerSkillChoose] ==
//                            "變化") {
//                            LOG_DEBUG("Status is not ready");
//                        } else {
//                            m_SFX->Play(
//                                    "PokeSound" +
//                                    Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetID());
//                            Enemy->GetPokemonBag()->GetPokemons()[m_CurrentNPCPokemon]->PokemonHurt(
//                                    Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon], PlayerSkillChoose);
//                            Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->ReducePP(PlayerSkillChoose);
//                            m_FightMainUI->SetEnemyHPScale(m_CurrentNPCPokemon);
//                            m_FightMainUI->SetPlayerHPScale(m_CurrentPlayerPokemon);
//                            m_FightMainUI->SetTextHP(m_CurrentPlayerPokemon);
//                        }
//                    }
//                    FightCounter++;
//                }
//            }
//            if (Util::Input::IsKeyDown(Util::Keycode::Z)) {
//                m_FightTextUI->Next();
//            }
//            if (!m_FightTextUI->GetPlayerVisibility() && !m_FightTextUI->GetEnemyVisibility() && FightCounter == 2) {
//                FightCounter = 0;
//                m_FightMainUI->SetArrowVisible(true);
//                LOG_DEBUG("State:Home");
//                m_CurrentFighting = FightID::HOME;
//            }
            break;
            //endregion

        case FightID::CHANGEPOKE:
            //region ChangePoke
            Timer++;
            if (m_FightMainUI->GetPlayerPokeScale().x > 0.5 && Timer < 100) {
                if (Timer > 80) {
                    m_FightMainUI->ReduceImage(true);
                }
            } else if (m_FightMainUI->GetPlayerPokeScale().x <= 0.5 && Timer <= 100) {
                m_FightMainUI->SetPlayerPokeVisible(false);
                if (Timer == 100) {
                    m_FightTextUI->Next();
                    m_FightMainUI->SetBallAnimationVisible(true, true);
                }
            } else {
                if (m_FightMainUI->GetBallAnimationIndex() == 4) {
                    m_CurrentFighting = FightID::UPDATEINFO;
                    m_FightMainUI->SetPlayerPokeVisible(true);
                    m_FightMainUI->SetBallAnimationVisible(false, true);
                    if (m_FightMainUI->GetPlayerPokeScale().x < 1) {
                        m_FightMainUI->ZoomImage(true);
                    } else {
                        if (Timer == 155) {
                            m_SFX->Play("PokeSound" +
                                        Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetID());
                        }
                        if (Timer == 180) {
                            m_FightMainUI->SetPlayerPokeScale({1, 1});
                            m_FightMainUI->SetPlayerHPUIVisible(true);
                            m_FightMainUI->SetPlayerHPTextVisible(true);
                            m_FightMainUI->SetPlayerPokeNameVisible(true);
                            m_FightTextUI->Next();
                        }
                    }
                }
            }
            if (!m_FightTextUI->GetChangePokeVisibility()) {
                Timer = 0;
                m_FightTextUI->SetEnemy(m_CurrentNPCPokemon, m_CurrentPlayerPokemon, EnemySkillChoose);
                m_CurrentFighting = FightID::FIGHT;
            }
            break;
            //endregion

        case FightID::POKEFAINTED:
            //region PokeFainted
            if (m_PokeFaintedUI->GetCurrentIndex() == 1 && Util::Input::IsKeyDown(Util::Keycode::Z)) {
                m_PokeFaintedUI->SetTFBoxVisible(true);
                m_PokeFaintedUI->Next();
            } else if (m_PokeFaintedUI->GetCurrentIndex() == 2) {
                if (m_PokeFaintedUI->TFBoxChoose()) {
                    if (m_PokeFaintedUI->GetTF()) {
                        m_PokeFaintedUI->Next();
                        m_PokeFaintedUI->SetTFBoxVisible(false);
                        m_FightMainUI->SetArrowVisible(false);
                        m_PokeBagUI->SetVisible(true);
                        LOG_DEBUG("State:Pokepack");
                        m_CurrentFighting = FightID::POKEPACK;
                    } else {
                        m_PokeFaintedUI->SetVisible(false);
                        Enemy->GetPokemonBag()->SetPokemons({});
                        LOG_DEBUG("Run");
                        m_CurrentFighting = FightID::RUN;
                    }
                }
            }

            break;
            //endregion

        case FightID::EVOLUTION:
            //region Evolution
            switch (m_EvolutionUI->GetTextIndex()) {
                case 1:
                    if (ButtonTrigger >= 5 && FightCounter > 60) {
                        m_SFX->SetVolume("Evolution", 0);
                        m_EvolutionUI->Pause();
                        m_EvolutionUI->SetCurrentFrame(0);
                        m_EvolutionUI->Next();
                    } else if (FightCounter >= 420) {
                        m_SFX->SetVolume("Evolution", 0);
                        m_SFX->Play("EndEvolution");
                        m_EvolutionUI->Pause();
                        m_EvolutionUI->SetCurrentFrame(1);
                        Timer = 0;
                        m_EvolutionUI->Next();
                    } else {
                        FightCounter++;
                        if (FightCounter % 30 == 0 && FightCounter > 120) {
                            m_EvolutionUI->Play();
                            if (m_EvolutionUI->GetInterval() > 0) {
                                m_EvolutionUI->SetInterval(m_EvolutionUI->GetInterval() - 40);
                            }
                        } else if (FightCounter > 60) {
                            m_EvolutionUI->SetPokeVisible(true);
                        }
                        if (Util::Input::IsKeyDown(Util::Keycode::X)) {
                            ButtonTrigger++;
                        }
                    }
                    break;
                case 2:
                    if (Timer < 200) {
                        Timer++;
                    }
                    if (ButtonTrigger >= 5) {
                        m_EvolutionUI->StopEvolution();
                    }
                    if (Util::Input::IsKeyDown(Util::Keycode::Z) && Timer >= 200) {
                        if (ButtonTrigger < 5) {
                            Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->Evolution();
                            m_FightMainUI->SetPlayerPokeImage(m_CurrentPlayerPokemon);
                        }
                        FightCounter = 0;
                        ButtonTrigger = 0;
                        Timer = 0;
                        m_EvolutionUI->SetInterval(401);
                        m_EvolutionUI->SetVisible(false);
                        m_CurrentFighting = FightID::UPDATEINFO;
                    }
                    break;
            }
            break;
            //endregion

        case FightID::GETSKILL:
            //region GetSkill
            if (m_ReplaceSkillUI->GetVisibility()) {
                m_ReplaceSkillUI->Run();
            } else {
                m_FightSkillUI->SetVisible(true);
                m_FightMainUI->SetArrowVisible(false);
                m_FightSkillUI->ShowSkillInfo(m_CurrentPlayerPokemon);
                if (m_FightSkillUI->Choose(m_CurrentPlayerPokemon)) {
                    PlayerSkillChoose = m_FightSkillUI->GetDecision();
                    Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetNewSkill(PlayerSkillChoose);
                    m_FightSkillUI->SetVisible(false);
                    m_FightMainUI->SetArrowVisible(true);
                    m_CurrentFighting = FightID::UPDATEINFO;
                } else if (m_ReplaceSkillUI->GetCurrentIndex() == 1) {
                    Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetNewSkill();
                    m_FightSkillUI->SetVisible(false);
                    m_FightMainUI->SetArrowVisible(true);
                    m_CurrentFighting = FightID::UPDATEINFO;
                } else if (m_ReplaceSkillUI->GetCurrentIndex() == 3) {
                    m_FightSkillUI->SetVisible(false);
                    m_FightMainUI->SetArrowVisible(true);
                    m_CurrentFighting = FightID::UPDATEINFO;
                }
            }
            break;
            //endregion

        case FightID::WILDFINISH:
            //region WildFinish
            m_FightMainUI->SetEnemyPokeVisible(false);
            m_FightMainUI->SetEnemyHPUIVisible(false);
            m_FightMainUI->SetEnemyPokeNameVisible(false);
            if (FightCounter == 0) {
                m_Experience = Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GainExperince(
                        Enemy->GetPokemonBag()->GetPokemons()[m_CurrentNPCPokemon]->GetLV());
                Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GainBasePoints(m_Experience.second);
                m_FightTextUI->SetDefeatWild(m_CurrentPlayerPokemon, 0, m_Experience.second);
                FightCounter++;
            } else if (!m_FightTextUI->GetDefeatWildVisibility() && m_Experience.first && FightCounter == 1) {
                m_BGM->Pause();
                m_SFX->Play("LevelUp");
                m_FightTextUI->SetLevelUP(Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetName(),
                                          Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetLV());
                FightCounter++;
            } else if (!m_FightTextUI->GetLevelUPVisibility() && FightCounter == 2) {
                m_CurrentFighting = FightID::UPDATEINFO;
                FightCounter = 0;
                if (Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->IsGetNewSkill()) {
                    m_SFX->Play("LevelUp");
                    m_ReplaceSkillUI->SetText(m_CurrentPlayerPokemon);
                    m_CurrentFighting = FightID::GETSKILL;
                } else if (Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->IsEvolution()) {
                    m_SFX->Play("Evolution");
                    m_EvolutionUI->Setting(
                            Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetIDByInt());
                    m_EvolutionUI->SetVisible(true);
                    m_EvolutionUI->SetPokeVisible(false);
                    m_CurrentFighting = FightID::EVOLUTION;
                } else {
                    m_CurrentFighting = FightID::UPDATEINFO;
                }
            }
            if (Util::Input::IsKeyDown(Util::Keycode::Z)) {
                m_FightTextUI->Next();
            }
            if (!m_FightTextUI->GetDefeatWildVisibility() && !m_FightTextUI->GetGainEXPVisibility() &&
                !m_Experience.first && FightCounter == 1) {
                FightCounter = 0;
                m_CurrentFighting = FightID::UPDATEINFO;
            }
            break;
            //endregion

        case FightID::NPCCHANGE:
            //region NPCChange
            if (m_FightMainUI->GetBallAnimationIndex() == 4) {
                m_FightMainUI->SetEnemyPokeVisible(true);
                m_FightMainUI->SetBallAnimationVisible(false, false);
                if (m_FightMainUI->GetEnemyPokeScale().x < 1) {
                    m_FightMainUI->ZoomImage(false);
                } else {
                    Timer++;
                    if (Timer == 1) {
                        m_SFX->Play("PokeSound" + Enemy->GetPokemonBag()->GetPokemons()[m_CurrentNPCPokemon]->GetID());
                    } else if (Timer == 60) {
                        m_FightMainUI->SetEnemyPokeScale({1, 1});
                        m_FightMainUI->SetEnemyHPUIVisible(true);
                        m_FightMainUI->SetEnemyPokeNameVisible(true);
                        m_LoadingUI->SetTBVisible(false);
                        Timer = 0;
                        m_CurrentFighting = FightID::HOME;
                    }
                    if (Util::Input::IsKeyDown(Util::Keycode::Z)) {

                    }
                }
            }
            //endregion
            break;

        case FightID::UPDATEINFO:
            //region UpdateInfo
            m_FightMainUI->SetPlayerPokeImage(m_CurrentPlayerPokemon);
            m_FightMainUI->SetTextPlayerPokeName(m_CurrentPlayerPokemon);
            m_FightMainUI->SetPlayerHPScale(m_CurrentPlayerPokemon);
            m_FightMainUI->SetTextHP(m_CurrentPlayerPokemon);
            m_FightSkillUI->SetText(m_CurrentPlayerPokemon);
            if (Enemy->GetPokemonBag()->GetPokemons()[m_CurrentNPCPokemon]->IsPokemonDying()) {
                if (isWildPokemon) {
                    m_WhiteBG->SetVisible(false);
                    m_WhiteBG->SetZIndex(0);
                    m_FightMainUI->SetVisible(false);
                    m_PlayerPokeInfo->SetVisible(false);
                    m_EnemyPokeInfo->SetVisible(false);
                    m_FightMainUI->SetVisible(false);
                    m_BGM->LoadMedia(RESOURCE_DIR"/BGM/PalletTown.mp3");
                    m_BGM->Play();
                    Enemy->GetPokemonBag()->SetPokemons({});
                    LOG_DEBUG("State:UPDATE");
                    m_CurrentState = State::UPDATE;
                } else {
                    bool AllNPCPokemonDie = true;
                    for (auto EnemyPokemon: Enemy->GetPokemonBag()->GetPokemons()) {
                        if (EnemyPokemon->IsPokemonDying()) {
                            m_CurrentNPCPokemon++;
                        } else {
                            AllNPCPokemonDie = false;
                            break;
                        }
                    }
                    if (AllNPCPokemonDie) {
                        m_WhiteBG->SetVisible(false);
                        m_WhiteBG->SetZIndex(0);
                        m_FightMainUI->SetVisible(false);
                        m_PlayerPokeInfo->SetVisible(false);
                        m_EnemyPokeInfo->SetVisible(false);
                        m_FightMainUI->SetVisible(false);
                        m_BGM->LoadMedia(RESOURCE_DIR"/BGM/PalletTown.mp3");
                        m_BGM->Play();
                        Enemy->GetPokemonBag()->SetPokemons({});
                        LOG_DEBUG("State:UPDATE");
                        m_CurrentState = State::UPDATE;
                    } else {
                        m_FightMainUI->SetEnemyPokeImage(m_CurrentNPCPokemon);
                        m_FightMainUI->SetTextEnemyPokeName(m_CurrentNPCPokemon);
                        m_FightMainUI->SetEnemyHPScale(m_CurrentNPCPokemon);
                        m_FightMainUI->SetBallAnimationVisible(true, false);
                        m_FightMainUI->SetEnemyPokeScale({0.5, 0.5});
                        m_LoadingUI->LoadText(m_CurrentPlayerPokemon, m_CurrentNPCPokemon, isWildPokemon);
                        m_LoadingUI->Next();
                        LOG_DEBUG("State:NPCCHANGE");
                        m_CurrentFighting = FightID::NPCCHANGE;
                    }
                }
                if (m_CurrentEvent == EventID::NPC) {
                    m_CurrentEvent = EventID::NPC_END;
                }
            } else if (IsChangePokemon) {
                m_CurrentFighting = FightID::CHANGEPOKE;
            } else if (m_Experience.first) {
                m_CurrentFighting = FightID::WILDFINISH;
            } else {
                m_CurrentFighting = FightID::HOME;
            }
            break;
            //endregion

        case FightID::NONE:
            break;
    }

    if (Util::Input::IsKeyDown(Util::Keycode::KP_ENTER) || Util::Input::IsKeyPressed(Util::Keycode::RETURN)) {
        LOG_DEBUG("Position:({},{})", Util::Input::GetCursorPosition().x, Util::Input::GetCursorPosition().y);
        LOG_DEBUG(Enemy->GetPokemonBag()->GetPokemons()[m_CurrentNPCPokemon]->GetID());
    }

    m_FightMainUI->DetectBlood();

    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }

    m_Root.Update();
}