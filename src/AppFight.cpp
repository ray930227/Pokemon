#include "App.hpp"

void App::Fight() {
    switch (m_CurrentFighting) {
        // region Home
        case FightID::HOME:
            if (m_FightMainUI->Choose()) {
                if (m_FightMainUI->GetDecision() == "Skill") {
                    m_FightMainUI->SetArrowVisible(false);
                    m_FightSkillUI->GetArrowCount(
                            Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetSkill().size());
                    m_FightSkillUI->SetVisible(true);
                    LOG_DEBUG("State:Skill");
                    m_CurrentFighting = FightID::SKILL;
                } else if (m_FightMainUI->GetDecision() == "PokePack") {
                    m_FightMainUI->SetArrowVisible(false);
                    m_PokeBagUI->GetArrowCount(Player->GetPokemonBag()->size());
                    for (size_t i = 0; i < Player->GetPokemonBag()->size(); i++) {
                        m_PokeBagUI->SetImage(i, RESOURCE_DIR"/Pokemon/Pokedex/Pokedex" +
                                                 Player->GetPokemonBag()->GetPokemons()[i]->GetID() + ".png");
                        m_PokeBagUI->SetLV(i,
                                           "LV:" + std::to_string(Player->GetPokemonBag()->GetPokemons()[i]->GetLV()));
                        m_PokeBagUI->SetName(i, Player->GetPokemonBag()->GetPokemons()[i]->GetName());
                        m_PokeBagUI->SetHP(i,
                                           std::to_string(Player->GetPokemonBag()->GetPokemons()[i]->GetCurrentHP()) +
                                           "/" +
                                           std::to_string(Player->GetPokemonBag()->GetPokemons()[i]->GetHP()));
                        m_PokeBagUI->SetScale(i, {(1.0 * Player->GetPokemonBag()->GetPokemons()[i]->GetCurrentHP() /
                                                   Player->GetPokemonBag()->GetPokemons()[i]->GetHP()), 1});
                        m_PokeBagUI->IsHpLower(i);
                    }
                    for (size_t i = 0; i < Player->GetPokemonBag()->size(); i++) {
                        m_PokeBagUI->SetVisible(i, true);
                    }
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
            if (Enemy->GetPokemonBag()->GetPokemons()[0]->IsPokemonDying()) {
                m_CurrentFighting = FightID::TEXT;
            }
            if (Util::Input::IsKeyDown(Util::Keycode::U)) {
                if (Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GainExperince(
                        Enemy->GetPokemonBag()->GetPokemons()[0]->GetLV()).first) {
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
                }
                Enemy->GetPokemonBag()->GetPokemons()[0]->GainExperince(
                        Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetLV());
                m_FightMainUI->SetTextPlayerPokeName(
                        Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetName() + " LV:" +
                        std::to_string(Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetLV()));
                m_FightMainUI->SetTextEnemyPokeName(Enemy->GetPokemonBag()->GetPokemons()[0]->GetName() + " LV:" +
                                                    std::to_string(Enemy->GetPokemonBag()->GetPokemons()[0]->GetLV()));
            }
            if (Util::Input::IsKeyDown(Util::Keycode::H)) {
                Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->PokemonHurt(1);
                if (1.0 * Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetCurrentHP() /
                    Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetHP() <= 0) {
                    m_FightMainUI->SetPlayerHPScale({0, 1});
                } else {
                    m_FightMainUI->SetPlayerHPScale(
                            {(1.0 * Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetCurrentHP() /
                              Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetHP()), 1});
                }
                m_CurrentFighting = FightID::UPDATEINFO;
            }
            break;
            //endregion
            // region Skill
        case FightID::SKILL:
            m_FightSkillUI->ShowSkillInfo(
                    Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetSkillType(),
                    Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetCurrentSkillPP(),
                    Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetSkillPP());
            if (m_FightSkillUI->Choose()) {
                PlayerSkillChoose = m_FightSkillUI->GetDecision();
                EnemySkillChoose = Enemy->GetPokemonBag()->GetPokemons()[0]->CaculateDamge(
                        Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetType());
                if (Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetSpeed() >
                    Enemy->GetPokemonBag()->GetPokemons()[0]->GetSpeed()) {
                    IsPlayerRound = true;
                    m_FightTextUI->SetPlayer(Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetName(),
                                             Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetSkill()[PlayerSkillChoose],
                                             PokeFunction::TypeDamage(
                                                     Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetSkillType()[PlayerSkillChoose],
                                                     Enemy->GetPokemonBag()->GetPokemons()[0]->GetType()));
                } else {
                    IsPlayerRound = false;
                    m_FightTextUI->SetEnemy(Enemy->GetPokemonBag()->GetPokemons()[0]->GetName(),
                                            Enemy->GetPokemonBag()->GetPokemons()[0]->GetSkill()[EnemySkillChoose],
                                            PokeFunction::TypeDamage(
                                                    Enemy->GetPokemonBag()->GetPokemons()[0]->GetSkillType()[EnemySkillChoose],
                                                    Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetType()));
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
            if (m_PokeBagUI->Choose()) {
                m_CurrentPlayerPokemon = m_PokeBagUI->GetDecision();
                m_PokeBagUI->SetVisible(false);
                m_FightMainUI->SetArrowVisible(true);
                m_CurrentFighting = FightID::UPDATEINFO;
            }
            if (Util::Input::IsKeyDown(Util::Keycode::X)) {
                m_PokeBagUI->SetVisible(false);
                m_FightMainUI->SetArrowVisible(true);
                m_CurrentFighting = FightID::HOME;
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
            if (!m_FightTextUI->GetRunVisibility()) {
                m_WhiteBG->SetVisible(false);
                m_WhiteBG->SetZIndex(0);
                m_tempImage->SetZIndex(1);
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
                        }
                    }
                    FightCounter++;
                } else if (!m_FightTextUI->GetPlayerVisibility() && FightCounter == 1) {
                    if (!Enemy->GetPokemonBag()->GetPokemons()[0]->IsPokemonDying()) {
                        m_FightTextUI->SetEnemy(Enemy->GetPokemonBag()->GetPokemons()[0]->GetName(),
                                                Enemy->GetPokemonBag()->GetPokemons()[0]->GetSkill()[EnemySkillChoose],
                                                PokeFunction::TypeDamage(
                                                        Enemy->GetPokemonBag()->GetPokemons()[0]->GetSkillType()[EnemySkillChoose],
                                                        Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetType()));
                        m_SFX->Play("PokeSound" + Enemy->GetPokemonBag()->GetPokemons()[0]->GetID());
                        Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->PokemonHurt(
                                Enemy->GetPokemonBag()->GetPokemons()[0], EnemySkillChoose);
                        Enemy->GetPokemonBag()->GetPokemons()[0]->ReducePP(EnemySkillChoose);
                    }
                    FightCounter++;
                }
            } else {
                if (FightCounter == 0) {
                    if (!Enemy->GetPokemonBag()->GetPokemons()[0]->IsPokemonDying()) {
                        m_SFX->Play("PokeSound" + Enemy->GetPokemonBag()->GetPokemons()[0]->GetID());
                        Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->PokemonHurt(
                                Enemy->GetPokemonBag()->GetPokemons()[0], EnemySkillChoose);
                        Enemy->GetPokemonBag()->GetPokemons()[0]->ReducePP(EnemySkillChoose);
                    }
                    FightCounter++;
                } else if (!m_FightTextUI->GetEnemyVisibility() && FightCounter == 1) {
                    if (!Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->IsPokemonDying()) {
                        m_FightTextUI->SetPlayer(
                                Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetName(),
                                Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetSkill()[PlayerSkillChoose],
                                PokeFunction::TypeDamage(
                                        Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetSkillType()[PlayerSkillChoose],
                                        Enemy->GetPokemonBag()->GetPokemons()[0]->GetType()));
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
                        }
                    }
                    FightCounter++;
                }
            }
            if (Util::Input::IsKeyDown(Util::Keycode::Z)) {
                m_FightTextUI->Next();
            }
            if (1.0 * Enemy->GetPokemonBag()->GetPokemons()[0]->GetCurrentHP() /
                Enemy->GetPokemonBag()->GetPokemons()[0]->GetHP() <= 0) {
                m_FightMainUI->SetEnemyHPScale({0, 1});
            } else {
                m_FightMainUI->SetEnemyHPScale({(1.0 * Enemy->GetPokemonBag()->GetPokemons()[0]->GetCurrentHP() /
                                                 Enemy->GetPokemonBag()->GetPokemons()[0]->GetHP()), 1});
            }
            if (1.0 * Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetCurrentHP() /
                Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetHP() <= 0) {
                m_FightMainUI->SetPlayerHPScale({0, 1});
                m_FightMainUI->SetTextHP(
                        std::to_string(Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetCurrentHP()) +
                        " / " +
                        std::to_string(Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetHP()));
            } else {
                m_FightMainUI->SetPlayerHPScale(
                        {(1.0 * Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetCurrentHP() /
                          Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetHP()), 1});
                m_FightMainUI->SetTextHP(
                        std::to_string(Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetCurrentHP()) +
                        " / " +
                        std::to_string(Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetHP()));
            }
            if (!m_FightTextUI->GetPlayerVisibility() && !m_FightTextUI->GetEnemyVisibility() && FightCounter == 2) {
                FightCounter = 0;
                m_FightMainUI->SetArrowVisible(true);
                LOG_DEBUG("State:Home");
                m_CurrentFighting = FightID::HOME;
            }
            break;
            //endregion
            //region Evolution
        case FightID::EVOLUTION:
            switch (m_EvolutionUI->GetTextIndex()) {
                case 1:
                    if (ButtonTrigger >= 5 && FightCounter > 60) {
                        m_EvolutionUI->Pause();
                        m_EvolutionUI->SetCurrentFrame(0);
                        m_EvolutionUI->Next();
                    } else if (FightCounter >= 420) {
                        m_EvolutionUI->Pause();
                        m_EvolutionUI->SetCurrentFrame(1);
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
                    if (ButtonTrigger >= 5) {
                        m_EvolutionUI->StopEvolution();
                    }
                    if (Util::Input::IsKeyDown(Util::Keycode::Z)) {
                        if (ButtonTrigger < 5) {
                            Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->Evolution();
                            m_FightMainUI->SetPlayerPokeImage(
                                    RESOURCE_DIR"/Pokemon/PokeImage/Pokemonback" +
                                    Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetID() + ".png");
                            Enemy->GetPokemonBag()->GetPokemons()[0]->Evolution();
                            m_FightMainUI->SetEnemyPokeImage(
                                    RESOURCE_DIR"/Pokemon/PokeImage/Pokemonfront" +
                                    Enemy->GetPokemonBag()->GetPokemons()[0]->GetID() + ".png");
                        }
                        FightCounter = 0;
                        ButtonTrigger = 0;
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
                        m_FightSkillUI->GetArrowCount(
                                Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetSkill().size());
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
                m_FightSkillUI->ShowSkillInfo(
                        Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetSkillType(),
                        Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetCurrentSkillPP(),
                        Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetSkillPP());
                if (m_FightSkillUI->Choose()) {
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
            //region Text
        case FightID::TEXT:
            if (Enemy->GetPokemonBag()->GetPokemons()[0]->IsPokemonDying()) {
                m_FightMainUI->SetEnemyPokeVisible(false);
                m_FightMainUI->SetEnemyHPUIVisible(false);
                m_FightMainUI->SetEnemyPokeNameVisible(false);
                if (FightCounter == 0) {
                    m_FightTextUI->SetDefeat(Enemy->GetPokemonBag()->GetPokemons()[0]->GetName());
                    FightCounter++;
                } else if (!m_FightTextUI->GetDefeatVisibility() && FightCounter == 1) {
                    m_Experience = Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GainExperince(
                            Enemy->GetPokemonBag()->GetPokemons()[0]->GetLV());
                    m_FightTextUI->SetGainEXP(Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetName(),
                                              m_Experience.second);
                    FightCounter++;
                } else if (!m_FightTextUI->GetDefeatVisibility() && m_Experience.first && FightCounter == 2) {
                    m_FightTextUI->SetLevelUP(Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetName(),
                                              Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetLV());
                    FightCounter++;
                } else if (!m_FightTextUI->GetLevelUPVisibility() && FightCounter == 3) {
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
                }
            }
            if (Util::Input::IsKeyDown(Util::Keycode::Z)) {
                m_FightTextUI->Next();
            }
            if (!m_FightTextUI->GetDefeatVisibility() && !m_FightTextUI->GetGainEXPVisibility() && !m_Experience.first && FightCounter==2){
                m_CurrentFighting=FightID::HOME;
            }
            break;
            //endregion
            //region UpdateInfo
        case FightID::UPDATEINFO:
            m_FightMainUI->SetPlayerPokeImage(RESOURCE_DIR"/Pokemon/PokeImage/Pokemonback" +
                                              Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetID() +
                                              ".png");
            m_FightMainUI->SetTextPlayerPokeName(
                    Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetName() + " LV:" +
                    std::to_string(Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetLV()));
            m_FightMainUI->SetPlayerHPScale(
                    {(1.0 * Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetCurrentHP() /
                      Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetHP()), 1});
            m_FightMainUI->SetTextEnemyPokeName(Enemy->GetPokemonBag()->GetPokemons()[0]->GetName() + " LV:" +
                                                std::to_string(Enemy->GetPokemonBag()->GetPokemons()[0]->GetLV()));
            m_FightMainUI->SetTextHP(
                    std::to_string(Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetCurrentHP()) +
                    " / " +
                    std::to_string(Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetHP()));
            m_FightSkillUI->SetText(Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetSkill());
            m_CurrentFighting = FightID::HOME;
            break;
            //endregion
        case FightID::NONE:
            break;
    }

//Looking for position
    if (Util::Input::IsKeyDown(Util::Keycode::KP_ENTER) || Util::Input::IsKeyPressed(Util::Keycode::RETURN)) {
        LOG_DEBUG("Position:({},{})", Util::Input::GetCursorPosition().x, Util::Input::GetCursorPosition().y);
    }

    m_FightMainUI->DetectBlood();

    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }

    m_Root.Update();
}