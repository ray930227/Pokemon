#include "App.hpp"

void App::Fight() {
//    LOG_DEBUG("{},{}",m_arrow->GetPosition().x,m_arrow->GetPosition().y);
    switch (m_CurrentFighting) {
        case FightID::HOME:
            //Fight select Skill(-25,-200) POKEPACK(135,-200)
            //             BackPack(-25,-300) Run(135,-300)
            if (Util::Input::IsKeyPressed(Util::Keycode::UP) && m_arrow->GetPosition().y != -200
                && !m_Fightskill->GetVisibility() && !m_Fightitem->GetVisibility() &&
                !m_FightPokemon->GetVisibility()) {
                m_arrow->SetPosition({m_arrow->GetPosition().x, m_arrow->GetPosition().y + 100});
            } else if (Util::Input::IsKeyPressed(Util::Keycode::DOWN) && m_arrow->GetPosition().y != -300
                       && !m_Fightskill->GetVisibility() && !m_Fightitem->GetVisibility() &&
                       !m_FightPokemon->GetVisibility()) {
                m_arrow->SetPosition({m_arrow->GetPosition().x, m_arrow->GetPosition().y - 100});
            } else if (Util::Input::IsKeyPressed(Util::Keycode::RIGHT) && m_arrow->GetPosition().x != 135
                       && !m_Fightskill->GetVisibility() && !m_Fightitem->GetVisibility() &&
                       !m_FightPokemon->GetVisibility()) {
                m_arrow->SetPosition({m_arrow->GetPosition().x + 160, m_arrow->GetPosition().y});
            } else if (Util::Input::IsKeyPressed(Util::Keycode::LEFT) && m_arrow->GetPosition().x != -25
                       && !m_Fightskill->GetVisibility() && !m_Fightitem->GetVisibility() &&
                       !m_FightPokemon->GetVisibility()) {
                m_arrow->SetPosition({m_arrow->GetPosition().x - 160, m_arrow->GetPosition().y});
            }
            if (!m_Fightskill->GetVisibility() && Util::Input::IsKeyDown(Util::Keycode::Z)
                && m_arrow->GetPosition().x == -25 && m_arrow->GetPosition().y == -200) {
                m_Fightskill->SetVisible(true);
                m_FightSkillUI->SetVisible(true);
                m_SkillInfo->SetVisible(true);
                m_arrow->SetPosition({-170, -190});
                LOG_DEBUG("State:Skill");
                m_CurrentFighting = FightID::SKILL;
            } else if (!m_Fightitem->GetVisibility() && Util::Input::IsKeyDown(Util::Keycode::Z)
                       && m_arrow->GetPosition().x == -25 && m_arrow->GetPosition().y == -300) {
                m_Fightitem->SetVisible(true);
                m_arrow->SetPosition({-150, 160});
                LOG_DEBUG("State:Backpack");
                m_CurrentFighting = FightID::BACKPACK;
            } else if (!m_FightPokemon->GetVisibility() && Util::Input::IsKeyDown(Util::Keycode::Z)
                       && m_arrow->GetPosition().x == 135 && m_arrow->GetPosition().y == -200) {
                m_arrow->SetVisible(false);
                m_FightPokemon->SetVisible(true);
                for (size_t i = 0; i < Player->GetPokemonBag()->size(); i++) {
                    m_PokeBagUI->SetImage(i, RESOURCE_DIR"/Pokemon/Pokedex/Pokedex" +
                                             Player->GetPokemonBag()->GetPokemons()[i]->GetID() + ".png");
                    m_PokeBagUI->SetLV(i, "LV:" + std::to_string(Player->GetPokemonBag()->GetPokemons()[i]->GetLV()));
                    m_PokeBagUI->SetName(i, Player->GetPokemonBag()->GetPokemons()[i]->GetName());
                    m_PokeBagUI->SetHP(i,
                                       std::to_string(Player->GetPokemonBag()->GetPokemons()[i]->GetCurrentHP()) + "/" +
                                       std::to_string(Player->GetPokemonBag()->GetPokemons()[i]->GetHP()));
                }
                for (size_t i = 0; i < Player->GetPokemonBag()->size(); i++) {
                    m_PokeBagUI->SetVisible(i, true);
                }
                LOG_DEBUG("State:Pokepack");
                m_CurrentFighting = FightID::POKEPACK;
            } else if (!m_Fightskill->GetVisibility() && !m_Fightitem->GetVisibility() &&
                       !m_FightPokemon->GetVisibility()
                       && Util::Input::IsKeyDown(Util::Keycode::Z)
                       && m_arrow->GetPosition().x == 135 && m_arrow->GetPosition().y == -300) {
                m_arrow->SetPosition({-25, -200});
                m_WhiteBG->SetVisible(false);
                m_WhiteBG->SetZIndex(0);
                m_tempImage->SetZIndex(1);
                m_PlayerHPUI->SetVisible(false);
                m_EnemyHPUI->SetVisible(false);
                m_FightBG->SetVisible(false);
                m_Fightskill->SetVisible(false);
                m_arrow->SetVisible(false);
                m_PlayerHPimage->SetVisible(false);
                m_EnemyHPimage->SetVisible(false);
                m_PlayerPokemonImage->SetVisible(false);
                m_EnemyPokemonImage->SetVisible(false);
                m_PlayerHP->SetVisible(false);
                m_PlayerPokeName->SetVisible(false);
                m_EnemyPokeName->SetVisible(false);
                m_PlayerPokeInfo->SetVisible(false);
                m_EnemyPokeInfo->SetVisible(false);
                m_BGM->LoadMedia(RESOURCE_DIR"/BGM/PalletTown.mp3");
                m_BGM->Play();
                LOG_DEBUG("State:UPDATE");
                m_CurrentState = State::UPDATE;
            }
            if (Util::Input::IsKeyDown(Util::Keycode::U)) {
                Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->LevelUp();
                m_EnemyPokemon->LevelUp();
                m_PlayerPokeName->SetText(
                        Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetName() + " LV:" +
                        std::to_string(Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetLV()));
                m_EnemyPokeName->SetText(m_EnemyPokemon->GetName() + " LV:" + std::to_string(m_EnemyPokemon->GetLV()));
                if (Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->IsGetNewSkill()) {
                    m_TB->SetVisible(true);
                    if (Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->IsSkillFull()) {
                        m_TB->ReadLines(RESOURCE_DIR"/Lines/ReplaceSkill.txt");
                        m_arrow->SetVisible(false);
                        m_arrow->SetZIndex(100);
                        m_arrow->SetPosition({55, -270});
                        m_CurrentFighting = FightID::REPLACESKILL;
                    } else {
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
            if (Util::Input::IsKeyDown(Util::Keycode::H)) {
                Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->PokemonHurt(1);
                if (1.0 * Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetCurrentHP() /
                    Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetHP() <= 0) {
                    m_PlayerHPimage->SetScale({0, 1});
                } else {
                    m_PlayerHPimage->SetScale(
                            {(1.0 * Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetCurrentHP() /
                              Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetHP()), 1});
                }
                m_CurrentFighting = FightID::UPDATEINFO;
            }
            break;

        case FightID::SKILL:
            if (Util::Input::IsKeyDown(Util::Keycode::UP) && m_arrow->GetPosition().y != -190) {
                m_arrow->SetPosition({m_arrow->GetPosition().x, m_arrow->GetPosition().y + 40});
            } else if (Util::Input::IsKeyDown(Util::Keycode::DOWN) &&
                       ((Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetSkill().size() == 4 &&
                         m_arrow->GetPosition().y != -310) ||
                        (Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetSkill().size() == 3 &&
                         m_arrow->GetPosition().y != -270) ||
                        (Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetSkill().size() == 2 &&
                         m_arrow->GetPosition().y != -230))) {
                m_arrow->SetPosition({m_arrow->GetPosition().x, m_arrow->GetPosition().y - 40});

            }
            if (m_arrow->GetPosition().y == -190) {
                m_SkillInfo->SetText(
                        "型態:" + Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetSkillType()[0] +
                        "\n" +
                        Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetCurrentSkillPP()[0] + " / " +
                        Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetSkillPP()[0]);
            } else if (m_arrow->GetPosition().y == -230) {
                m_SkillInfo->SetText(
                        "型態:" + Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetSkillType()[1] +
                        "\n" +
                        Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetCurrentSkillPP()[1] + " / " +
                        Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetSkillPP()[1]);
            } else if (m_arrow->GetPosition().y == -270) {
                m_SkillInfo->SetText(
                        "型態:" + Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetSkillType()[2] +
                        "\n" +
                        Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetCurrentSkillPP()[2] + " / " +
                        Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetSkillPP()[2]);
            } else if (m_arrow->GetPosition().y == -310) {
                m_SkillInfo->SetText(
                        "型態:" + Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetSkillType()[3] +
                        "\n" +
                        Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetCurrentSkillPP()[3] + " / " +
                        Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetSkillPP()[3]);
            }
            if (Util::Input::IsKeyDown(Util::Keycode::Z)) {
                if (m_arrow->GetPosition().y == -190) {
                    SkillChoose = 0;
                } else if (m_arrow->GetPosition().y == -230) {
                    SkillChoose = 1;
                } else if (m_arrow->GetPosition().y == -270) {
                    SkillChoose = 2;
                } else if (m_arrow->GetPosition().y == -310) {
                    SkillChoose = 3;
                }
                m_CurrentFighting = FightID::FIGHT;
            }
            if (Util::Input::IsKeyDown(Util::Keycode::X)) {
                m_Fightskill->SetVisible(false);
                m_FightSkillUI->SetVisible(false);
                m_arrow->SetVisible(true);
                m_SkillInfo->SetVisible(false);
                m_arrow->SetPosition({-25, -200});
                m_CurrentFighting = FightID::HOME;
            }
            break;

        case FightID::POKEPACK:
            if (Util::Input::IsKeyDown(Util::Keycode::X)) {
                m_PokeBagUI->SetVisible(false);
                m_FightPokemon->SetVisible(false);
                m_arrow->SetVisible(true);
                m_arrow->SetPosition({-25, -200});
                m_CurrentFighting = FightID::HOME;
            }
            break;

        case FightID::BACKPACK:
            if (Util::Input::IsKeyDown(Util::Keycode::X)) {
                m_Fightitem->SetVisible(false);
                m_arrow->SetVisible(true);
                m_arrow->SetPosition({-25, -200});
                m_CurrentFighting = FightID::HOME;
            }
            break;

        case FightID::FIGHT:
            if (Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetSkillClass()[SkillChoose] ==
                "變化") {
                LOG_DEBUG("Status is not ready");
            } else {
                m_EnemyPokemon->PokemonHurt(
                        round((((2.0 * Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetLV() + 10) /
                                250) *
                               (1.0 * Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetAttack() /
                                m_EnemyPokemon->GetDefence()) *
                               std::stof(
                                       Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetSkillDamge()[SkillChoose]) +
                               2) *
                              PokeFunction::TypeDamage(
                                      Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetSkillType()[SkillChoose],
                                      m_EnemyPokemon->GetType())));
                Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->ReducePP(SkillChoose);
            }

            if (1.0 * m_EnemyPokemon->GetCurrentHP() / m_EnemyPokemon->GetHP() <= 0) {
                m_EnemyHPimage->SetScale({0, 1});
            } else {
                m_EnemyHPimage->SetScale({(1.0 * m_EnemyPokemon->GetCurrentHP() / m_EnemyPokemon->GetHP()), 1});
            }
            m_TB->SetVisible(true);
            m_SkillInfo->SetVisible(false);
            m_Fightskill->SetVisible(false);
            m_FightSkillUI->SetVisible(false);
            if (IsPlayerRound) {
                m_TB->Reload();
                m_TB->AddText(Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetName() + "使出了" +
                              Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetSkill()[SkillChoose]);
                if (PokeFunction::TypeDamage(
                        Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetSkillType()[SkillChoose],
                        m_EnemyPokemon->GetType()) >= 2.0) {
                    m_TB->AddText("效果絕佳!");
                } else if (PokeFunction::TypeDamage(
                        Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetSkillType()[SkillChoose],
                        m_EnemyPokemon->GetType()) <= 0.5) {
                    m_TB->AddText("效果不好!");
                }

                m_CurrentFighting = FightID::SHOWPLAYER;
            } else {
                m_CurrentFighting = FightID::SHOWENEMY;
            }
            break;

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
                            m_PlayerPokemonImage->SetImage(
                                    RESOURCE_DIR"/Pokemon/PokeImage/Pokemonback" +
                                    Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetID() + ".png");
                            m_EnemyPokemon->Evolution();
                            m_EnemyPokemonImage->SetImage(
                                    RESOURCE_DIR"/Pokemon/PokeImage/Pokemonfront" + m_EnemyPokemon->GetID() + ".png");
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

        case FightID::REPLACESKILL:
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
                if (m_TB->GetVisibility()) {
                    if (m_TB->GetLineIndex() == 3) {
                        m_arrow->SetVisible(false);
                        m_arrow->SetZIndex(55);
                        if (m_arrow->GetPosition().x == 55) {
                            m_TB->Next();
                        } else {
                            m_TB->SetVisible(false);
                            m_arrow->SetPosition({-25, -200});
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
                    } else if (m_TB->GetLineIndex() == 4) {
                        m_arrow->SetPosition({-170, -190});
                        m_arrow->SetVisible(true);
                        m_Fightskill->SetVisible(true);
                        m_SkillInfo->SetVisible(true);
                        m_FightSkillUI->SetVisible(true);
                        m_TB->Next();
                    } else {
                        m_TB->Next();
                    }
                } else {
                    if (Util::Input::IsKeyDown(Util::Keycode::Z) && !m_TB->GetVisibility()) {
                        if (m_arrow->GetPosition().y == -190) {
                            SkillChoose = 0;
                        } else if (m_arrow->GetPosition().y == -230) {
                            SkillChoose = 1;
                        } else if (m_arrow->GetPosition().y == -270) {
                            SkillChoose = 2;
                        } else if (m_arrow->GetPosition().y == -310) {
                            SkillChoose = 3;
                        }
                        Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetNewSkill(SkillChoose);
                        m_Fightskill->SetVisible(false);
                        m_FightSkillUI->SetVisible(false);
                        m_SkillInfo->SetVisible(false);
                        m_arrow->SetPosition({-25, -200});
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
            }
            switch (m_TB->GetLineIndex()) {
                case 3:
                    m_arrow->SetVisible(true);//Yes::({55,-270}) No:({150,-270})
                    if (Util::Input::IsKeyDown(Util::Keycode::LEFT) && m_arrow->GetPosition().x != 55) {
                        m_arrow->SetPosition({m_arrow->GetPosition().x - 95, m_arrow->GetPosition().y});
                    } else if (Util::Input::IsKeyDown(Util::Keycode::RIGHT) && m_arrow->GetPosition().x != 150) {
                        m_arrow->SetPosition({m_arrow->GetPosition().x + 95, m_arrow->GetPosition().y});
                    }
                    break;
                case 4:
                    if (Util::Input::IsKeyDown(Util::Keycode::UP) && m_arrow->GetPosition().y != -190) {
                        m_arrow->SetPosition({m_arrow->GetPosition().x, m_arrow->GetPosition().y + 40});
                    } else if (Util::Input::IsKeyDown(Util::Keycode::DOWN) &&
                               ((Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetSkill().size() ==
                                 4 && m_arrow->GetPosition().y != -310) ||
                                (Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetSkill().size() ==
                                 3 && m_arrow->GetPosition().y != -270) ||
                                (Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetSkill().size() ==
                                 2 && m_arrow->GetPosition().y != -230))) {
                        m_arrow->SetPosition({m_arrow->GetPosition().x, m_arrow->GetPosition().y - 40});
                    }
                    if (m_arrow->GetPosition().y == -190) {
                        m_SkillInfo->SetText("型態:" +
                                             Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetSkillType()[0] +
                                             "\n" +
                                             Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetCurrentSkillPP()[0] +
                                             " / " +
                                             Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetSkillPP()[0]);
                    } else if (m_arrow->GetPosition().y == -230) {
                        m_SkillInfo->SetText("型態:" +
                                             Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetSkillType()[1] +
                                             "\n" +
                                             Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetCurrentSkillPP()[1] +
                                             " / " +
                                             Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetSkillPP()[1]);
                    } else if (m_arrow->GetPosition().y == -270) {
                        m_SkillInfo->SetText("型態:" +
                                             Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetSkillType()[2] +
                                             "\n" +
                                             Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetCurrentSkillPP()[2] +
                                             " / " +
                                             Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetSkillPP()[2]);
                    } else if (m_arrow->GetPosition().y == -310) {
                        m_SkillInfo->SetText("型態:" +
                                             Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetSkillType()[3] +
                                             "\n" +
                                             Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetCurrentSkillPP()[3] +
                                             " / " +
                                             Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetSkillPP()[3]);
                    }
                    break;
            }
            break;

        case FightID::UPDATEINFO:
            m_PlayerPokeName->SetText(
                    Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetName() + " LV:" +
                    std::to_string(Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetLV()));
            m_EnemyPokeName->SetText(m_EnemyPokemon->GetName() + " LV:" + std::to_string(m_EnemyPokemon->GetLV()));
            m_PlayerPokeInfo->SetDrawable(std::make_unique<Util::Text>(
                    RESOURCE_DIR"/text.ttf", 30,
                    "IV:" + std::to_string(Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetIV()) +
                    "\n" +
                    "HP:" + std::to_string(Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetHP()) +
                    "\n" +
                    "Attack:" +
                    std::to_string(Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetAttack()) + "\n" +
                    "Defence:" +
                    std::to_string(Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetDefence()) +
                    "\n" +
                    "Special:" +
                    std::to_string(Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetSpecial()) +
                    "\n" +
                    "Speed:" +
                    std::to_string(Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetSpeed()),
                    Util::Color::FromName(Util::Colors::WHITE)));
            m_EnemyPokeInfo->SetDrawable(std::make_unique<Util::Text>(
                    RESOURCE_DIR"/text.ttf", 30,
                    "IV:" + std::to_string(m_EnemyPokemon->GetIV()) + "\n" +
                    "HP:" + std::to_string(m_EnemyPokemon->GetHP()) + "\n" +
                    "Attack:" + std::to_string(m_EnemyPokemon->GetAttack()) + "\n" +
                    "Defence:" + std::to_string(m_EnemyPokemon->GetDefence()) + "\n" +
                    "Special:" + std::to_string(m_EnemyPokemon->GetSpecial()) + "\n" +
                    "Speed:" + std::to_string(m_EnemyPokemon->GetSpeed()),
                    Util::Color::FromName(Util::Colors::WHITE)));
            m_PlayerHP->SetText(
                    std::to_string(Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetCurrentHP()) +
                    " / " +
                    std::to_string(Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetHP()));
            m_FightSkillUI->SetText(Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetSkill());
            m_CurrentFighting = FightID::HOME;
            break;

        case FightID::SHOWPLAYER:
            if (m_TB->GetVisibility() && Util::Input::IsKeyDown(Util::Keycode::Z)) {
                m_TB->Next();
            }
            if (!m_TB->GetVisibility()) {
                m_arrow->SetVisible(true);
                m_arrow->SetPosition({-25, -200});
                m_CurrentFighting = FightID::HOME;
            }
            break;

        case FightID::SHOWENEMY:

            break;
        case FightID::NONE:
            break;
    }

//Looking for position
    if (Util::Input::IsKeyDown(Util::Keycode::KP_ENTER) || Util::Input::IsKeyPressed(Util::Keycode::RETURN)) {
        LOG_DEBUG("Position:({},{})", Util::Input::GetCursorPosition().x, Util::Input::GetCursorPosition().y);
    }

    if ((m_PlayerHPimage->GetScaledSize().x) <= 91.200005) {
        m_PlayerHPimage->SetImage(RESOURCE_DIR"/Fight/RedHealth.png");
    } else {
        m_PlayerHPimage->SetImage(RESOURCE_DIR"/Fight/GreenHealth.png");
    }

    if ((m_EnemyHPimage->GetScaledSize().x) <= 91.200005) {
        m_EnemyHPimage->SetImage(RESOURCE_DIR"/Fight/RedHealth.png");
    } else {
        m_EnemyHPimage->SetImage(RESOURCE_DIR"/Fight/GreenHealth.png");
    }

    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }

    m_Root.Update();
}