#include "App.hpp"

void App::Fight() {
    switch (m_CurrentFighting) {
        case FightID::HOME:
            // region Home
            if (m_FightTextUI->GetTBVisibility()) {
                if (Util::Input::IsKeyDown(Util::Keycode::Z)) {
                    m_FightTextUI->Next();
                }
            } else {
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
                        m_FightMainUI->SetArrowVisible(false);
                        LOG_DEBUG("State:Backpack");
                        m_BackPackUI->Start(1);
                        m_CurrentFighting = FightID::BACKPACK;
                    } else if (m_FightMainUI->GetDecision() == "Run") {
                        LOG_DEBUG("Run");
                        m_FightTextUI->SetRun(isWildPokemon);
                        m_CurrentFighting = FightID::RUN;
                    }
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
            if (m_FightTextUI->GetTBVisibility()) {
                if (Util::Input::IsKeyDown(Util::Keycode::Z)) {
                    m_FightTextUI->Next();
                }
            } else {
                m_FightSkillUI->ShowSkillInfo(m_CurrentPlayerPokemon);
                if (m_FightSkillUI->Choose(m_CurrentPlayerPokemon)) {
                    IsChangePokemon = false;
                    if (Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->IsPPAllZero()) {
                        PlayerSkillChoose = 4;
                    } else {
                        PlayerSkillChoose = m_FightSkillUI->GetDecision();
                    }
                    if (std::stoi(
                            Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetCurrentSkillPP()[PlayerSkillChoose]) ==
                        0) {
                        m_FightTextUI->SetPPRunOut(m_CurrentPlayerPokemon, PlayerSkillChoose);
                        LOG_DEBUG("State:None");
                        m_CurrentFighting = FightID::SKILL;
                        break;
                    }
                    if (Enemy->GetPokemonBag()->GetPokemons()[m_CurrentNPCPokemon]->IsPPAllZero()) {
                        EnemySkillChoose = 4;
                    } else {
                        EnemySkillChoose = Enemy->GetPokemonBag()->GetPokemons()[m_CurrentNPCPokemon]->CaculateDamge(
                                Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetType());
                    }
                    IsPlayerRound = Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetSpeed() >
                                    Enemy->GetPokemonBag()->GetPokemons()[m_CurrentNPCPokemon]->GetSpeed() ||
                                    Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetSkill()[PlayerSkillChoose] ==
                                    "電光一閃";
                    if (IsPlayerRound) {
                        m_FightPoke.first = Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon];
                        m_FightPoke.second = Enemy->GetPokemonBag()->GetPokemons()[m_CurrentNPCPokemon];
                        m_FightSkill.first = PlayerSkillChoose;
                        m_FightSkill.second = EnemySkillChoose;
                    } else {
                        m_FightPoke.first = Enemy->GetPokemonBag()->GetPokemons()[m_CurrentNPCPokemon];
                        m_FightPoke.second = Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon];
                        m_FightSkill.first = EnemySkillChoose;
                        m_FightSkill.second = PlayerSkillChoose;
                    }
                    m_FightSkillUI->SetVisible(false);
                    LOG_DEBUG("State:Fight");
                    m_CurrentFighting = FightID::FIGHT;
                }
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
                    bool die = false;
                    if (Player->GetPokemonBag()->GetPokemons()[m_PreviousPlayerPokemon]->IsPokemonDying()) {
                        die = true;
                        m_FightTextUI->Next();
                    }
                    m_PokeBagUI->SetVisible(false);
                    m_FightMainUI->SetArrowVisible(true);
                    m_FightSkillUI->ReSetArrow();
                    if (die) {
                        m_FightMainUI->SetPlayerPokeVisible(false);
                        m_FightMainUI->SetPlayerPokeScale({0.5, 0.5});
                        m_FightMainUI->SetBallAnimationVisible(true, true);
                        Timer = 101;
                    } else {
                        Timer = 0;
                    }
                    LOG_DEBUG("State:CHANGEPOKE");
                    m_CurrentFighting = FightID::CHANGEPOKE;
                }
            }
            break;
            //endregion

        case FightID::BACKPACK:
            //region BackPack
            m_BackPackUI->Run();
            if (!m_BackPackUI->GetVisible()) {
                m_FightMainUI->SetArrowVisible(true);
                if (m_BackPackUI->IsXLeave()) {
                    m_FightMainUI->SetArrowVisible(true);
                    m_CurrentFighting = FightID::HOME;
                } else {
                    if (isWildPokemon) {
                        if (m_BackPackUI->GetDecision() < 5) {
                            Player->GetItemBag()->AddItemQuantity(m_BackPackUI->GetDecision(), -1);
                            int CatachRate;
                            m_SuccessCatch = false;
                            if (m_BackPackUI->GetDecision() == 1) {
                                CatachRate = 255;
                            } else {
                                CatachRate = Enemy->GetPokemonBag()->GetPokemons()[m_CurrentNPCPokemon]->GetHP() *
                                             (256 / (8 + (m_BackPackUI->GetDecision() - 2) * 2))
                                             /
                                             (1.0 *
                                              Enemy->GetPokemonBag()->GetPokemons()[m_CurrentNPCPokemon]->GetCurrentHP() /
                                              4);
                            }
                            if (rand() % 256 <= CatachRate) {
                                m_SuccessCatch = true;
                            }
                            m_FightMainUI->SetCatchBallAnimationVisible(true);
                            m_CurrentFighting = FightID::CATCHPOKE;
                        } else {
                            m_CurrentFighting = FightID::UPDATEINFO;
                        }
                    } else {
                        m_FightTextUI->SetCatch();
                        m_CurrentFighting = FightID::HOME;
                    }
                }
            }

            break;
            //endregion

        case FightID::CATCHPOKE:
            //region Catch
            if (m_FightMainUI->IsCatching()) {
                m_FightMainUI->RunCatchPokemon(m_SuccessCatch, m_CurrentNPCPokemon);
            } else if (m_FightMainUI->SuccessCatch()) {
                std::shared_ptr<Pokemon> EnemyPokemon = Enemy->GetPokemonBag()->GetPokemons()[m_CurrentNPCPokemon];
                EnemyPokemon->SetCurrentHP(EnemyPokemon->GetHP());
                EnemyPokemon->SetCurrentSkillPP(EnemyPokemon->GetSkillPP());
                if (Player->GetPokemonBag()->isFull()) {
                    m_ComputerUI->Keep(Enemy->GetPokemonBag()->GetPokemons()[m_CurrentNPCPokemon]);
                } else {
                    Player->GetPokemonBag()->addPomekon(Enemy->GetPokemonBag()->GetPokemons()[m_CurrentNPCPokemon]);
                }
                m_CurrentFighting = FightID::WILDFINISH;
            } else {
                m_FightTextUI->SetEnemy(m_CurrentNPCPokemon, m_CurrentPlayerPokemon, EnemySkillChoose);
                Fighting(Enemy->GetPokemonBag()->GetPokemons()[m_CurrentNPCPokemon],
                         Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon], m_EnemyBuff, m_PlayerBuff,
                         EnemySkillChoose);
                FightCounter = 1;
                m_CurrentFighting = FightID::FIGHT;
            }
            break;
            //endregion

        case FightID::RUN:
            //region Run
            if (!m_FightTextUI->GetTBVisibility()) {
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
            if (!m_FightTextUI->GetTBVisibility()) {
                if (FightCounter == 0) {
                    if (IsPlayerRound) {
                        m_FightTextUI->SetPlayer(m_CurrentPlayerPokemon, m_CurrentNPCPokemon, PlayerSkillChoose);
                    } else {
                        m_FightTextUI->SetEnemy(m_CurrentNPCPokemon, m_CurrentPlayerPokemon, EnemySkillChoose);
                    }
                    Fighting(m_FightPoke.first, m_FightPoke.second, m_PlayerBuff, m_EnemyBuff, m_FightSkill.first);
                } else {
                    if (m_FightPoke.second->GetCurrentHP() <= 0) {
                        m_FightMainUI->SetArrowVisible(true);
                        LOG_DEBUG("State:Home");
                        FightCounter = 0;
                        m_CurrentFighting = FightID::HOME;
                        break;
                    }
                    if (!IsPlayerRound) {
                        m_FightTextUI->SetPlayer(m_CurrentPlayerPokemon, m_CurrentNPCPokemon, PlayerSkillChoose);
                    } else {
                        m_FightTextUI->SetEnemy(m_CurrentNPCPokemon, m_CurrentPlayerPokemon, EnemySkillChoose);
                    }
                    Fighting(m_FightPoke.second, m_FightPoke.first, m_EnemyBuff, m_PlayerBuff, m_FightSkill.second);
                }
            }
            if (Util::Input::IsKeyDown(Util::Keycode::Z)) {
                m_FightTextUI->Next();
                if (!m_FightTextUI->GetTBVisibility()) {
                    FightCounter++;
                    if (FightCounter == 2) {
                        m_FightMainUI->SetArrowVisible(true);
                        LOG_DEBUG("State:Home");
                        FightCounter = 0;
                        m_CurrentFighting = FightID::HOME;
                    }
                }
            }
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
                    LOG_DEBUG("State:UPDATEINFO");
                    m_CurrentFighting = FightID::UPDATEINFO;
                    m_FightMainUI->SetPlayerPokeVisible(true);
                    m_FightMainUI->SetBallAnimationVisible(false, true);
                    if (m_FightMainUI->GetPlayerPokeScale().x < 1) {
                        m_FightMainUI->ZoomImage(true);
                    }
                    if (Timer == 155) {
                        m_SFX->Play("PokeSound" +
                                    Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetID());
                    }
                    if (Timer == 170) {
                        m_FightMainUI->SetPlayerPokeScale({1, 1});
                        m_FightMainUI->SetPlayerHPUIVisible(true);
                        m_FightMainUI->SetPlayerHPTextVisible(true);
                        m_FightMainUI->SetPlayerPokeNameVisible(true);
                        m_FightTextUI->Next();
                    }
                }
            }
            if (!m_FightTextUI->GetTBVisibility()) {
                Timer = 0;
                m_FightTextUI->SetEnemy(m_CurrentNPCPokemon, m_CurrentPlayerPokemon, EnemySkillChoose);
                Fighting(Enemy->GetPokemonBag()->GetPokemons()[m_CurrentNPCPokemon],
                         Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon], m_EnemyBuff, m_PlayerBuff,
                         EnemySkillChoose);
                FightCounter = 1;
                IsChangePokemon = false;
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
            if (!m_FightMainUI->SuccessCatch()) {
                m_FightMainUI->SetEnemyPokeVisible(false);
                m_FightMainUI->SetEnemyHPUIVisible(false);
                m_FightMainUI->SetEnemyPokeNameVisible(false);
            }
            if (FightCounter == 0) {
                m_Experience = Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GainExperince(
                        Enemy->GetPokemonBag()->GetPokemons()[m_CurrentNPCPokemon]->GetLV());
                Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GainBasePoints(m_Experience.second);
                m_FightTextUI->SetDefeatWild(m_CurrentPlayerPokemon, 0, m_Experience.second);
                if (m_FightMainUI->SuccessCatch()) {
                    m_FightTextUI->Next();
                }
                FightCounter++;
            } else if (!m_FightTextUI->GetTBVisibility() && m_Experience.first && FightCounter == 1) {
                m_SFX->Play("LevelUp");
                m_FightMainUI->SetTextPlayerPokeName(m_CurrentPlayerPokemon);
                m_FightMainUI->SetTextHP(m_CurrentPlayerPokemon);
                m_FightTextUI->SetLevelUP(Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetName(),
                                          Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetLV());
                FightCounter++;
            } else if (!m_FightTextUI->GetTBVisibility() && FightCounter == 2) {
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
            if (!m_FightTextUI->GetTBVisibility() && !m_Experience.first && FightCounter == 1) {
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
            if (Enemy->GetPokemonBag()->GetPokemons()[m_CurrentNPCPokemon]->IsPokemonDying() ||
                m_FightMainUI->SuccessCatch()) {
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
                LOG_DEBUG("State:CHANGEPOKE");
                m_CurrentFighting = FightID::CHANGEPOKE;
            } else if (m_Experience.first) {
                m_CurrentFighting = FightID::WILDFINISH;
            } else {
                LOG_DEBUG("State:HOME");
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

void
App::Fighting(const std::shared_ptr<Pokemon> &A, const std::shared_ptr<Pokemon> &B, std::map<std::string, float> &Abuff,
              std::map<std::string, float> &Bbuff, int useSkill) {
    auto SkillClass = A->GetSkillClass()[useSkill];
    auto Skill = A->GetSkill()[useSkill];
    int Damage = 0;
    auto A_Ability = A->GetAbility();
    auto B_Ability = B->GetAbility();
    auto B_Type = B->GetType();

    bool isHit;
    if (Skill == "斷頭鉗" || Skill == "角鑽" || Skill == "地裂")
        isHit = (rand() % 254 + 1) <= (int) (30 + A->GetLV() - B->GetLV()) * 2.55;
    else
        isHit = (rand() % 254 + 1) <=
                (int) (std::stof(A->GetSkillHitRate()[useSkill]) * 2.55 * Abuff["命中率"] * Bbuff["閃避率"]);


    if (isHit) {
        if (SkillClass == "變化") {

            std::string type = "";
            float rate = 0;
            if (Skill == "劍舞") {
                type = "攻擊";
                rate = 2.0;
            } else if (Skill == "潑沙" || Skill == "定身法" || Skill == "麻痺粉" || Skill == "催眠粉" ||
                       Skill == "電磁波" || Skill == "催眠術" || Skill == "模仿" || Skill == "煙幕" ||
                       Skill == "鸚鵡學舌" || Skill == "折彎湯匙" || Skill == "變身" || Skill == "蘑菇孢子" ||
                       Skill == "閃光") {
                type = "命中率";
                rate = 0.66;
            } else if (Skill == "搖尾巴" || Skill == "瞪眼" || Skill == "毒粉" || Skill == "刺耳聲" ||
                       Skill == "毒瓦斯") {
                type = "防禦";
                rate = 0.66;
            } else if (Skill == "叫聲") {
                type = "攻擊";
                rate = 0.66;
            } else if (Skill == "吼叫" || Skill == "反射壁") {
                type = "攻擊";
                rate = 0.5;
            } else if (Skill == "生長") {
                type = "特殊";
                rate = 1.5;
            } else if (Skill == "吐絲") {
                type = "速度";
                rate = 0.5;
            } else if (Skill == "瑜伽姿勢" || Skill == "聚氣" || Skill == "揮指" || Skill == "稜角化") {
                type = "攻擊";
                rate = 1.5;
            } else if (Skill == "高速移動") {
                type = "速度";
                rate = 2.0;
            } else if (Skill == "瞬間移動") {
                type = "速度";
                rate = 2.5;
            } else if (Skill == "影子分身") {
                type = "閃避率";
                rate = 1.5;
            } else if (Skill == "變硬" || Skill == "縮入殼中" || Skill == "變圓" || Skill == "忍耐" ||
                       Skill == "紋理") {
                type = "防禦";
                rate = 1.5;
            } else if (Skill == "屏障" || Skill == "光牆" || Skill == "瞬間失憶" || Skill == "溶化") {
                type = "防禦";
                rate = 2.0;
            } else if (Skill == "變小") {
                type = "閃避率";
                rate = 2.0;
            } else if (Skill == "自我再生" || Skill == "替身") {
                A_Ability["CurrentHP"] += A_Ability["HP"] / 2;
                if (A_Ability["CurrentHP"] > A_Ability["HP"]) {
                    A_Ability["CurrentHP"] = A_Ability["HP"];
                }
                A->SetCurrentHP(A_Ability["CurrentHP"]);
                type = "HP";
            } else if (Skill == "黑霧") {
                std::vector<std::pair<std::string, float>> tempPairs = {{"攻擊",   1.0},
                                                                        {"命中率", 1.0},
                                                                        {"閃避率", 1.0},
                                                                        {"防禦",   1.0},
                                                                        {"特殊",   1.0},
                                                                        {"速度",   1.0},};

                for (auto &i: tempPairs) {
                    Abuff[i.first] = i.second;
                }
                type = "State";
            } else if (Skill == "睡覺") {
                A_Ability["CurrentHP"] += A_Ability["HP"];
                A->SetCurrentHP(A_Ability["CurrentHP"]);
                std::vector<std::pair<std::string, float>> tempPairs = {{"攻擊",   1.0},
                                                                        {"命中率", 1.0},
                                                                        {"閃避率", 1.0},
                                                                        {"防禦",   1.0},
                                                                        {"特殊",   1.0},
                                                                        {"速度",   1.0},};

                for (auto &i: tempPairs) {
                    Abuff[i.first] = i.second;
                }
                type = "ALL";
            }
            if (type == "") {

            } else {
                if (rate > 1)
                    Abuff[type] *= rate;
                else
                    Bbuff[type] *= rate;
            }
        } else {

            if (Skill == "斷頭鉗" || Skill == "角鑽" || Skill == "地裂") {
                Damage = 999999;
            } else if (Skill == "地球上投" || Skill == "黑夜魔影") {
                Damage = A->GetLV();
            } else if (Skill == "龍之怒" || Skill == "音爆") {
                Damage = std::stof(A->GetSkillDamge()[useSkill]);
            } else if (Skill == "精神波") {
                Damage = A->GetLV() * (rand() % 10 + 5) / 10.0;
            } else if (Skill == "憤怒門牙") {
                Damage = B_Ability["CurrentHP"] / 2;
            } else {
                Damage = round(
                        (((2.0 * A->GetLV() + 10) / 250) *
                         (1.0 * (A->GetAttack() * Abuff["攻擊"]) / (B_Ability["Defence"] * Bbuff["防禦"])) *
                         std::stof(A->GetSkillDamge()[useSkill]) + 2) *
                        PokeFunction::TypeDamage(A->GetSkillType()[useSkill], B_Type));
            }

            if (Skill == "劈開" || Skill == "飛葉快刀" || Skill == "空手劈" || Skill == "蟹鉗錘") {
                if (rand() % 256 < A_Ability["SpeedSS"] * 4)
                    Damage *= 1.5;
            } else {
                if (rand() % 256 < A_Ability["SpeedSS"] / 2)
                    Damage *= 1.5;
            }

            if (Skill == "猛撞") {
                A_Ability["CurrentHP"] -= Damage / 4;
            } else if (Skill == "捨身衝撞") {
                A_Ability["CurrentHP"] -= Damage / 3;
            } else if (Skill == "吸取" || Skill == "超級吸取" || Skill == "寄生種子" || Skill == "吸血") {
                A_Ability["CurrentHP"] += Damage / 2;
            } else if (Skill == "自爆" || Skill == "大爆炸") {
                A_Ability["CurrentHP"] = 0;
            }

            B_Ability["CurrentHP"] -= Damage;
            if (A_Ability["CurrentHP"] < 0) {
                A_Ability["CurrentHP"] = 0;
            }
            A->SetCurrentHP(A_Ability["CurrentHP"]);
            if (B_Ability["CurrentHP"] < 0) {
                B_Ability["CurrentHP"] = 0;
            }
            B->SetCurrentHP(B_Ability["CurrentHP"]);
        }
    } else {
        m_FightTextUI->SetNoHit(A->GetName());
    }
    m_SFX->Play("PokeSound" + A->GetID());
    A->ReducePP(useSkill);
    m_FightMainUI->SetEnemyHPScale(m_CurrentNPCPokemon);
    m_FightMainUI->SetPlayerHPScale(m_CurrentPlayerPokemon);
    m_FightMainUI->SetTextHP(m_CurrentPlayerPokemon);
}