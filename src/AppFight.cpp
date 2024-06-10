#include "App.hpp"

void App::Fight() {
    switch (m_CurrentFighting) {
        // region Home
        case FightID::HOME:
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
                    m_FightTextUI->SetRun();
                    m_CurrentFighting = FightID::RUN;
                }
            }
            if (Enemy->GetPokemonBag()->GetPokemons()[0]->IsPokemonDying() && isWildPokemon) {
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
                Enemy->GetPokemonBag()->GetPokemons()[0]->LevelUp();
                m_FightMainUI->SetTextEnemyPokeName(0);
                m_CurrentFighting = FightID::UPDATEINFO;
            }
            if (Util::Input::IsKeyDown(Util::Keycode::U)) {
                Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->LevelUp();
                if (Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->IsGetNewSkill()) {
                    if (Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->IsSkillFull()) {
                        m_ReplaceSkillUI->SetText(
                                Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetName(),
                                Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->NewSkill());
                        m_CurrentFighting = FightID::REPLACESKILL;
                    } else {
                        m_TB->SetVisible(true);
                        m_TB->ReadLines(RESOURCE_DIR"/Lines/ObtainSkill.txt");
                        m_CurrentFighting = FightID::OBTAINSKILL;
                    }
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
            // region Skill
        case FightID::SKILL:
            m_FightSkillUI->ShowSkillInfo(m_CurrentPlayerPokemon);
            if (m_FightSkillUI->Choose(m_CurrentPlayerPokemon)) {
                IsChangePokemon = false;
                PlayerSkillChoose = m_FightSkillUI->GetDecision();
                EnemySkillChoose = Enemy->GetPokemonBag()->GetPokemons()[0]->CaculateDamge(
                        Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetType());
                if (Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetSpeed() >
                    Enemy->GetPokemonBag()->GetPokemons()[0]->GetSpeed()) {
                    IsPlayerRound = true;
                    m_FightTextUI->SetPlayer(m_CurrentPlayerPokemon, 0, PlayerSkillChoose);
                } else {
                    IsPlayerRound = false;
                    m_FightTextUI->SetEnemy(0, m_CurrentPlayerPokemon, EnemySkillChoose);
                }
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
            //region PokePack
        case FightID::POKEPACK:
            if (m_PokeBagUI->GetVisible()) {
                m_PokeBagUI->Run(2);
            } else {
                m_CurrentPlayerPokemon = m_PokeBagUI->GetDecision();
                m_PokeBagUI->SetVisible(false);
                m_FightMainUI->SetArrowVisible(true);
                m_FightTextUI->SetChangePoke(
                        Player->GetPokemonBag()->GetPokemons()[m_PreviousPlayerPokemon]->GetName(),
                        Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetName());
                m_CurrentFighting = FightID::CHANGEPOKE;
            }
            break;
            //endregion
            //region BackPack
        case FightID::BACKPACK:
            if (Util::Input::IsKeyDown(Util::Keycode::X)) {
                m_Fightitem->SetVisible(false);
                m_FightMainUI->SetArrowVisible(true);
                m_CurrentFighting = FightID::HOME;
            }
            break;
            //endregion
            //region Run
        case FightID::RUN:
            if (Util::Input::IsKeyDown(Util::Keycode::Z)) {
                m_FightTextUI->Next();
            }
            if (!m_FightTextUI->GetRunVisibility() && !m_FightTextUI->GetLoseVisibility()) {
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
            }
            break;
            //endregion
            //region Fight
        case FightID::FIGHT:
            if (IsPlayerRound) {
                if (FightCounter == 0) {
                    if (!Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->IsPokemonDying()) {
                        if (Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetSkillClass()[PlayerSkillChoose] ==
                            "變化") {
                            LOG_DEBUG("Status is not ready");
                        } else {
                            m_SFX->Play(
                                    "PokeSound" +
                                    Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetID());
                            Enemy->GetPokemonBag()->GetPokemons()[0]->PokemonHurt(
                                    Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon], PlayerSkillChoose);
                            Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->ReducePP(PlayerSkillChoose);
                            m_FightMainUI->SetEnemyHPScale(0);
                            m_FightMainUI->SetPlayerHPScale(m_CurrentPlayerPokemon);
                            m_FightMainUI->SetTextHP(m_CurrentPlayerPokemon);
                        }
                    }
                    FightCounter++;
                } else if (!m_FightTextUI->GetPlayerVisibility() && FightCounter == 1) {
                    if (!Enemy->GetPokemonBag()->GetPokemons()[0]->IsPokemonDying()) {
                        m_FightTextUI->SetEnemy(0, m_CurrentPlayerPokemon, EnemySkillChoose);
                        if (Enemy->GetPokemonBag()->GetPokemons()[0]->GetSkillClass()[EnemySkillChoose] ==
                            "變化") {
                            LOG_DEBUG("Status is not ready");
                        } else {
                            m_SFX->Play("PokeSound" + Enemy->GetPokemonBag()->GetPokemons()[0]->GetID());
                            Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->PokemonHurt(
                                    Enemy->GetPokemonBag()->GetPokemons()[0], EnemySkillChoose);
                            Enemy->GetPokemonBag()->GetPokemons()[0]->ReducePP(EnemySkillChoose);
                            m_FightMainUI->SetEnemyHPScale(0);
                            m_FightMainUI->SetPlayerHPScale(m_CurrentPlayerPokemon);
                            m_FightMainUI->SetTextHP(m_CurrentPlayerPokemon);
                        }
                    }
                    FightCounter++;
                }
            } else {
                if (FightCounter == 0) {
                    if (!Enemy->GetPokemonBag()->GetPokemons()[0]->IsPokemonDying()) {
                        if (Enemy->GetPokemonBag()->GetPokemons()[0]->GetSkillClass()[EnemySkillChoose] ==
                            "變化") {
                            LOG_DEBUG("Status is not ready");
                        } else {
                            m_SFX->Play("PokeSound" + Enemy->GetPokemonBag()->GetPokemons()[0]->GetID());
                            Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->PokemonHurt(
                                    Enemy->GetPokemonBag()->GetPokemons()[0], EnemySkillChoose);
                            Enemy->GetPokemonBag()->GetPokemons()[0]->ReducePP(EnemySkillChoose);
                            m_FightMainUI->SetEnemyHPScale(0);
                            m_FightMainUI->SetPlayerHPScale(m_CurrentPlayerPokemon);
                            m_FightMainUI->SetTextHP(m_CurrentPlayerPokemon);
                        }
                    }
                    FightCounter++;
                } else if (!m_FightTextUI->GetEnemyVisibility() && FightCounter == 1) {
                    if (!Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->IsPokemonDying() &&
                        !IsChangePokemon) {
                        m_FightTextUI->SetPlayer(m_CurrentPlayerPokemon, 0, PlayerSkillChoose);
                        if (Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetSkillClass()[PlayerSkillChoose] ==
                            "變化") {
                            LOG_DEBUG("Status is not ready");
                        } else {
                            m_SFX->Play(
                                    "PokeSound" +
                                    Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetID());
                            Enemy->GetPokemonBag()->GetPokemons()[0]->PokemonHurt(
                                    Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon], PlayerSkillChoose);
                            Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->ReducePP(PlayerSkillChoose);
                            m_FightMainUI->SetEnemyHPScale(0);
                            m_FightMainUI->SetPlayerHPScale(m_CurrentPlayerPokemon);
                            m_FightMainUI->SetTextHP(m_CurrentPlayerPokemon);
                        }
                    }
                    FightCounter++;
                }
            }
            if (Util::Input::IsKeyDown(Util::Keycode::Z)) {
                m_FightTextUI->Next();
            }
            if (!m_FightTextUI->GetPlayerVisibility() && !m_FightTextUI->GetEnemyVisibility() && FightCounter == 2) {
                FightCounter = 0;
                m_FightMainUI->SetArrowVisible(true);
                LOG_DEBUG("State:Home");
                m_CurrentFighting = FightID::HOME;
            }
            break;
            //endregion
            //region ChangePoke
        case FightID::CHANGEPOKE:
            if (Util::Input::IsKeyDown(Util::Keycode::Z)) {
                m_FightTextUI->Next();
            }
            if (!m_FightTextUI->GetChangePokeVisibility()) {
                IsPlayerRound = false;
                IsChangePokemon = true;
                m_FightTextUI->SetEnemy(0, m_CurrentPlayerPokemon, EnemySkillChoose);
                m_CurrentFighting = FightID::UPDATEINFO;
            }
            break;
            //endregion
            //region FailChange
            break;
            //endregion
            //region PokeFainted
        case FightID::POKEFAINTED:
            if (m_PokeFaintedUI->GetCurrentIndex() == 1 && Util::Input::IsKeyDown(Util::Keycode::Z)) {
                m_PokeFaintedUI->SetTFBoxVisible(true);
                m_PokeFaintedUI->Next();
            } else if (m_PokeFaintedUI->GetCurrentIndex() == 2) {
                if (m_PokeFaintedUI->TFBoxChoose()) {
                    m_FightMainUI->SetPlayerPokeVisible(true);
                    m_FightMainUI->SetPlayerHPUIVisible(true);
                    m_FightMainUI->SetPlayerHPTextVisible(true);
                    m_FightMainUI->SetPlayerPokeNameVisible(true);
                    if (m_PokeFaintedUI->GetTF()) {
                        m_PokeFaintedUI->Next();
                        m_PokeFaintedUI->SetTFBoxVisible(false);
                        m_FightMainUI->SetArrowVisible(false);
                        m_PokeBagUI->SetVisible(true);
                        LOG_DEBUG("State:Pokepack");
                        m_CurrentFighting = FightID::POKEPACK;
                    } else {
                        m_PokeFaintedUI->SetVisible(false);
                        LOG_DEBUG("Run");
                        m_CurrentFighting = FightID::RUN;
                    }
                }
            }

            break;
            //endregion
            //region Evolution
        case FightID::EVOLUTION:
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
            //region ObtainSkill
        case FightID::OBTAINSKILL:
            if (m_TB->GetText().find("<PlayerPokemon>") < m_TB->GetText().size()) {
                std::string tempStr = m_TB->GetText();
                tempStr.replace(tempStr.begin() + tempStr.find("<PlayerPokemon>"),
                                tempStr.begin() + tempStr.find("<PlayerPokemon>") + 15,
                                Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetName());
                m_TB->SetText(tempStr);
            }
            if (m_TB->GetText().find("<Skill>") < m_TB->GetText().size()) {
                std::string tempStr = m_TB->GetText();
                tempStr.replace(tempStr.begin() + tempStr.find("<Skill>"),
                                tempStr.begin() + tempStr.find("<Skill>") + 7,
                                Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->NewSkill());
                m_TB->SetText(tempStr);
            }
            if (Util::Input::IsKeyDown(Util::Keycode::Z)) {
                Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetNewSkill();
                m_TB->Next();
                if (Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->IsEvolution()) {
                    m_EvolutionUI->Setting(
                            Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetIDByInt());
                    m_EvolutionUI->SetVisible(true);
                    m_EvolutionUI->SetPokeVisible(false);
                    m_CurrentFighting = FightID::EVOLUTION;
                } else {
                    m_CurrentFighting = FightID::UPDATEINFO;
                }
            }
            break;
            //endregion
            //region ReplaceSKill
        case FightID::REPLACESKILL:
            if (Util::Input::IsKeyDown(Util::Keycode::Z) &&
                (m_ReplaceSkillUI->GetCurrentIndex() <= 2 || m_ReplaceSkillUI->GetCurrentIndex() == 4)
                && m_ReplaceSkillUI->GetVisibility()) {
                switch (m_ReplaceSkillUI->GetCurrentIndex()) {
                    case 1:
                        m_ReplaceSkillUI->Next();
                        break;
                    case 2:
                        m_ReplaceSkillUI->SetTFBoxVisible(true);
                        m_ReplaceSkillUI->Next();
                        break;
                    case 4:
                        m_FightMainUI->SetArrowVisible(false);
                        m_FightSkillUI->SetVisible(true);
                        m_ReplaceSkillUI->Next();
                        break;
                }
            } else if (m_ReplaceSkillUI->GetCurrentIndex() == 3) {
                if (m_ReplaceSkillUI->TFBoxChoose()) {
                    if (m_ReplaceSkillUI->GetTF()) {
                        m_ReplaceSkillUI->SetTFBoxVisible(false);
                        m_ReplaceSkillUI->Next();
                    } else {
                        m_ReplaceSkillUI->SetVisible(false);
                        if (Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->IsEvolution()) {
                            m_EvolutionUI->Setting(
                                    Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetIDByInt());
                            m_EvolutionUI->SetVisible(true);
                            m_EvolutionUI->SetPokeVisible(false);
                            m_CurrentFighting = FightID::EVOLUTION;
                        } else {
                            m_CurrentFighting = FightID::UPDATEINFO;
                        }
                    }
                }
            } else if (!m_ReplaceSkillUI->GetVisibility()) {
                m_FightSkillUI->ShowSkillInfo(m_CurrentPlayerPokemon);
                if (m_FightSkillUI->Choose(m_CurrentPlayerPokemon)) {
                    PlayerSkillChoose = m_FightSkillUI->GetDecision();
                    Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetNewSkill(PlayerSkillChoose);
                    m_FightSkillUI->SetVisible(false);
                    m_FightMainUI->SetArrowVisible(true);
                    if (Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->IsEvolution()) {
                        m_EvolutionUI->Setting(
                                Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetIDByInt());
                        m_EvolutionUI->SetVisible(true);
                        m_EvolutionUI->SetPokeVisible(false);
                        m_CurrentFighting = FightID::EVOLUTION;
                    } else {
                        m_CurrentFighting = FightID::UPDATEINFO;
                    }
                }
            }
            break;
            //endregion
            //region WildFinish
        case FightID::WILDFINISH:
            Timer++;
            m_FightMainUI->SetEnemyPokeVisible(false);
            m_FightMainUI->SetEnemyHPUIVisible(false);
            m_FightMainUI->SetEnemyPokeNameVisible(false);
            if (FightCounter == 0) {
                m_FightTextUI->SetDefeat(Enemy->GetPokemonBag()->GetPokemons()[0]->GetName());
                FightCounter++;
            } else if (!m_FightTextUI->GetDefeatVisibility() && FightCounter == 1) {
                m_Experience = Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GainExperince(
                        Enemy->GetPokemonBag()->GetPokemons()[0]->GetLV());
                Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GainBasePoints(m_Experience.second);
                m_FightTextUI->SetGainEXP(Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetName(),
                                          m_Experience.second);
                FightCounter++;
            } else if (!m_FightTextUI->GetGainEXPVisibility() && m_Experience.first && FightCounter == 2) {
                m_BGM->Pause();
                m_SFX->Play("LevelUp");
                m_FightTextUI->SetLevelUP(Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetName(),
                                          Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetLV());
                FightCounter++;
            } else if (!m_FightTextUI->GetLevelUPVisibility() && FightCounter == 3) {
                m_CurrentFighting = FightID::UPDATEINFO;
                FightCounter = 0;
                if (Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->IsGetNewSkill()) {
                    m_SFX->Play("LevelUp");
                    if (Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->IsSkillFull()) {
                        m_ReplaceSkillUI->SetText(
                                Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetName(),
                                Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->NewSkill());
                        m_CurrentFighting = FightID::REPLACESKILL;
                    } else {
                        m_TB->SetVisible(true);
                        m_TB->ReadLines(RESOURCE_DIR"/Lines/ObtainSkill.txt");
                        m_CurrentFighting = FightID::OBTAINSKILL;
                    }
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
            switch (FightCounter) {
                case 1:
                    if (Util::Input::IsKeyDown(Util::Keycode::Z) && Timer >= 60) {
                        m_FightTextUI->Next();
                        Timer = 0;
                    }
                    break;
                case 2:
                    if (Util::Input::IsKeyDown(Util::Keycode::Z) && Timer >= 60) {
                        m_FightTextUI->Next();
                        Timer = 0;
                    }
                    break;
                case 3:
                    if (Util::Input::IsKeyDown(Util::Keycode::Z) && Timer >= 120) {
                        m_FightTextUI->Next();
                        Timer = 0;
                    }
                    break;
            }
            if (!m_FightTextUI->GetDefeatVisibility() && !m_FightTextUI->GetGainEXPVisibility() &&
                !m_Experience.first && FightCounter == 2) {
                FightCounter = 0;
                m_CurrentFighting = FightID::UPDATEINFO;
            }
            break;
            //endregion
            //region UpdateInfo
        case FightID::UPDATEINFO:
            m_FightMainUI->SetPlayerPokeImage(m_CurrentPlayerPokemon);
            m_FightMainUI->SetTextPlayerPokeName(m_CurrentPlayerPokemon);
            m_FightMainUI->SetPlayerHPScale(m_CurrentPlayerPokemon);
            m_FightMainUI->SetTextEnemyPokeName(0);
            m_FightMainUI->SetTextHP(m_CurrentPlayerPokemon);
            m_FightSkillUI->SetText(m_CurrentPlayerPokemon);
            if (Enemy->GetPokemonBag()->GetPokemons()[0]->IsPokemonDying()) {
                m_WhiteBG->SetVisible(false);
                m_WhiteBG->SetZIndex(0);
                m_FightMainUI->SetVisible(false);
                m_PlayerPokeInfo->SetVisible(false);
                m_EnemyPokeInfo->SetVisible(false);
                m_FightMainUI->SetVisible(false);
                m_BGM->LoadMedia(RESOURCE_DIR"/BGM/PalletTown.mp3");
                m_BGM->Play();
                if (m_CurrentEvent == EventID::NPC) {
                    m_CurrentEvent = EventID::NPC_END;
                }
                LOG_DEBUG("State:UPDATE");
                m_CurrentState = State::UPDATE;
            } else if (IsChangePokemon) {
                m_CurrentFighting = FightID::FIGHT;
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
        LOG_DEBUG(Enemy->GetPokemonBag()->GetPokemons()[0]->GetID());
    }

    m_FightMainUI->DetectBlood();

    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }

    m_Root.Update();
}