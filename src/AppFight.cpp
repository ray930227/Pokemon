#include "App.hpp"

void App::Fight() {
    switch (m_CurrentFighting) {
        case FightID::HOME:
            //Fight select Skill(-25,-200) PokeBack(135,-200)
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
                for (size_t i = 0; i < 4; i++) {
                    m_AllSkills[i]->SetVisible(true);
                }
                m_SkillInfo->SetVisible(true);
                m_arrow->SetPosition({-170, -190});
                m_CurrentFighting = FightID::SKILL;
            } else if (!m_Fightitem->GetVisibility() && Util::Input::IsKeyDown(Util::Keycode::Z)
                       && m_arrow->GetPosition().x == -25 && m_arrow->GetPosition().y == -300) {
                m_Fightitem->SetVisible(true);
                m_arrow->SetPosition({-150, 160});
                m_CurrentFighting = FightID::BACKPACK;
            } else if (!m_FightPokemon->GetVisibility() && Util::Input::IsKeyDown(Util::Keycode::Z)
                       && m_arrow->GetPosition().x == 135 && m_arrow->GetPosition().y == -200) {
                m_arrow->SetVisible(false);
                m_FightPokemon->SetVisible(true);
                m_CurrentFighting = FightID::POKEBACK;
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
                m_FightLoad1_1->SetVisible(false);
                m_FightLoad1_2->SetVisible(false);
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
                m_CurrentState = State::UPDATE;
            }
            if (Util::Input::IsKeyDown(Util::Keycode::U)) {
                m_PlayerPokemon->LevelUp();
                m_EnemyPokemon->LevelUp();
                if (m_PlayerPokemon->IsEvolution()) {
                    m_PlayerPokemonImage->SetImage(
                            RESOURCE_DIR"/Pokemon/PokeImage/Pokemonback" + m_PlayerPokemon->GetID() + ".png");
                }
                if (m_EnemyPokemon->IsEvolution()) {
                    m_EnemyPokemonImage->SetImage(
                            RESOURCE_DIR"/Pokemon/PokeImage/Pokemonfront" + m_EnemyPokemon->GetID() + ".png");
                }
                m_PlayerPokeName->SetText(
                        m_PlayerPokemon->GetName() + " LV:" + std::to_string(m_PlayerPokemon->GetLV()));
                m_EnemyPokeName->SetText(m_EnemyPokemon->GetName() + " LV:" + std::to_string(m_EnemyPokemon->GetLV()));
                if (m_PlayerPokemon->IsGetNewSkill()) {
                    m_TB->SetVisible(true);
                    if (m_PlayerPokemon->IsSkillFull()) {
                        m_TB->ReadLines(RESOURCE_DIR"/Lines/ReplaceSkill.txt");
                        m_arrow->SetVisible(false);
                        m_arrow->SetZIndex(100);
                        m_arrow->SetPosition({55, -270});
                        m_CurrentFighting = FightID::REPLACESKILL;
                    } else {
                        m_TB->ReadLines(RESOURCE_DIR"/Lines/ObtainSkill.txt");
                        m_CurrentFighting = FightID::OBTAINSKILL;
                    }
                } else {
                    m_CurrentFighting = FightID::UPDATEINFO;
                }
            }
            if (Util::Input::IsKeyDown(Util::Keycode::H)) {
                m_PlayerPokemon->PokemonHurt(1);
                if (1.0 * m_PlayerPokemon->GetCurrentHP() / m_PlayerPokemon->GetHP() <= 0) {
                    m_PlayerHPimage->SetScale({0, 1});
                } else {
                    m_PlayerHPimage->SetScale({(1.0 * m_PlayerPokemon->GetCurrentHP() / m_PlayerPokemon->GetHP()), 1});
                }
                m_CurrentFighting = FightID::UPDATEINFO;
            }
            break;

        case FightID::SKILL:
            if (Util::Input::IsKeyDown(Util::Keycode::UP) && m_arrow->GetPosition().y != -190) {
                m_arrow->SetPosition({m_arrow->GetPosition().x, m_arrow->GetPosition().y + 40});
            } else if (Util::Input::IsKeyDown(Util::Keycode::DOWN) &&
                       ((m_PlayerPokemon->GetSkill().size() == 4 && m_arrow->GetPosition().y != -310) ||
                        (m_PlayerPokemon->GetSkill().size() == 3 && m_arrow->GetPosition().y != -270) ||
                        (m_PlayerPokemon->GetSkill().size() == 2 && m_arrow->GetPosition().y != -230))) {
                m_arrow->SetPosition({m_arrow->GetPosition().x, m_arrow->GetPosition().y - 40});

            }
            if (m_arrow->GetPosition().y == -190) {
                m_SkillInfo->SetText("型態:" + m_PlayerPokemon->GetSkillType()[0] + "\n" +
                                     m_PlayerPokemon->GetCurrentSkillPP()[0] + " / " +
                                     m_PlayerPokemon->GetSkillPP()[0]);
            } else if (m_arrow->GetPosition().y == -230) {
                m_SkillInfo->SetText("型態:" + m_PlayerPokemon->GetSkillType()[1] + "\n" +
                                     m_PlayerPokemon->GetCurrentSkillPP()[1] + " / " +
                                     m_PlayerPokemon->GetSkillPP()[1]);
            } else if (m_arrow->GetPosition().y == -270) {
                m_SkillInfo->SetText("型態:" + m_PlayerPokemon->GetSkillType()[2] + "\n" +
                                     m_PlayerPokemon->GetCurrentSkillPP()[2] + " / " +
                                     m_PlayerPokemon->GetSkillPP()[2]);
            } else if (m_arrow->GetPosition().y == -310) {
                m_SkillInfo->SetText("型態:" + m_PlayerPokemon->GetSkillType()[3] + "\n" +
                                     m_PlayerPokemon->GetCurrentSkillPP()[3] + " / " +
                                     m_PlayerPokemon->GetSkillPP()[3]);
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
            if (Util::Input::IsKeyPressed(Util::Keycode::X)) {
                m_Fightskill->SetVisible(false);
                for (size_t i = 0; i < 4; i++) {
                    m_AllSkills[i]->SetVisible(false);
                }
                m_arrow->SetVisible(true);
                m_SkillInfo->SetVisible(false);
                m_arrow->SetPosition({-25, -200});
                m_CurrentFighting = FightID::HOME;
            }
            break;

        case FightID::POKEBACK:
            if (Util::Input::IsKeyPressed(Util::Keycode::X)) {
                m_FightPokemon->SetVisible(false);
                m_arrow->SetVisible(true);
                m_arrow->SetPosition({-25, -200});
                m_CurrentFighting = FightID::HOME;
            }
            break;

        case FightID::BACKPACK:
            if (Util::Input::IsKeyPressed(Util::Keycode::X)) {
                m_Fightitem->SetVisible(false);
                m_arrow->SetVisible(true);
                m_arrow->SetPosition({-25, -200});
                m_CurrentFighting = FightID::HOME;
            }
            break;

        case FightID::FIGHT:
            if (m_PlayerPokemon->GetSkillClass()[SkillChoose] == "變化") {
                LOG_DEBUG("Status is not ready");
            } else {
                m_EnemyPokemon->PokemonHurt(
                        round((((2.0 * m_PlayerPokemon->GetLV() + 10) / 250) *
                               (1.0 * m_PlayerPokemon->GetAttack() / m_EnemyPokemon->GetDefence()) *
                               std::stof(m_PlayerPokemon->GetSkillDamge()[SkillChoose]) + 2) *
                              PokeFunction::TypeDamage(m_PlayerPokemon->GetSkillType()[SkillChoose],
                                                       m_EnemyPokemon->GetType())));
                m_PlayerPokemon->ReducePP(SkillChoose);
            }

            if (1.0 * m_EnemyPokemon->GetCurrentHP() / m_EnemyPokemon->GetHP() <= 0) {
                m_EnemyHPimage->SetScale({0, 1});
            } else {
                m_EnemyHPimage->SetScale({(1.0 * m_EnemyPokemon->GetCurrentHP() / m_EnemyPokemon->GetHP()), 1});
            }
            m_TB->SetVisible(true);
            m_SkillInfo->SetVisible(false);
            m_Fightskill->SetVisible(false);
            for (size_t i = 0; i < 4; i++) {
                m_AllSkills[i]->SetVisible(false);
            }
            if (IsPlayerRound){
                m_TB->Reload();
                m_TB->AddText(m_PlayerPokemon->GetName()+"使出了"+m_PlayerPokemon->GetSkill()[SkillChoose]);
                LOG_DEBUG(PokeFunction::TypeDamage(m_PlayerPokemon->GetSkillType()[SkillChoose],
                          {"火"}));
                if (PokeFunction::TypeDamage(m_PlayerPokemon->GetSkillType()[SkillChoose],
                                             m_EnemyPokemon->GetType())>=2.0){
                    m_TB->AddText("效果絕佳!");
                }
                else if (PokeFunction::TypeDamage(m_PlayerPokemon->GetSkillType()[SkillChoose],
                                                  m_EnemyPokemon->GetType())<=0.5){
                    m_TB->AddText("效果不好!");
                }

                m_CurrentFighting = FightID::SHOWPLAYER;
            }
            else{
                m_CurrentFighting = FightID::SHOWENEMY;
            }
            break;

        case FightID::OBTAINSKILL:
            if (m_TB->GetText().find("<PlayerPokemon>") < m_TB->GetText().size()) {
                std::string tempStr = m_TB->GetText();
                tempStr.replace(tempStr.begin() + tempStr.find("<PlayerPokemon>"),
                                tempStr.begin() + tempStr.find("<PlayerPokemon>") + 15,
                                m_PlayerPokemon->GetName());
                m_TB->SetText(tempStr);
            }
            if (m_TB->GetText().find("<Skill>") < m_TB->GetText().size()) {
                std::string tempStr = m_TB->GetText();
                tempStr.replace(tempStr.begin() + tempStr.find("<Skill>"),
                                tempStr.begin() + tempStr.find("<Skill>") + 7,
                                m_PlayerPokemon->NewSkill());
                m_TB->SetText(tempStr);
            }
            if (Util::Input::IsKeyDown(Util::Keycode::Z)) {
                m_PlayerPokemon->GetNewSkill();
                m_TB->Next();
                m_CurrentFighting = FightID::UPDATEINFO;
            }
            break;

        case FightID::REPLACESKILL:
            if (m_TB->GetText().find("<PlayerPokemon>") < m_TB->GetText().size()) {
                std::string tempStr = m_TB->GetText();
                tempStr.replace(tempStr.begin() + tempStr.find("<PlayerPokemon>"),
                                tempStr.begin() + tempStr.find("<PlayerPokemon>") + 15,
                                m_PlayerPokemon->GetName());
                m_TB->SetText(tempStr);
            }
            if (m_TB->GetText().find("<Skill>") < m_TB->GetText().size()) {
                std::string tempStr = m_TB->GetText();
                tempStr.replace(tempStr.begin() + tempStr.find("<Skill>"),
                                tempStr.begin() + tempStr.find("<Skill>") + 7,
                                m_PlayerPokemon->NewSkill());
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
                            m_CurrentFighting = FightID::UPDATEINFO;
                        }
                    } else if (m_TB->GetLineIndex() == 4) {
                        m_arrow->SetPosition({-170, -190});
                        m_arrow->SetVisible(true);
                        m_Fightskill->SetVisible(true);
                        m_SkillInfo->SetVisible(true);
                        for (size_t i = 0; i < 4; i++) {
                            m_AllSkills[i]->SetVisible(true);
                        }
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
                        m_PlayerPokemon->GetNewSkill(SkillChoose);
                        m_Fightskill->SetVisible(false);
                        for (size_t i = 0; i < 4; i++) {
                            m_AllSkills[i]->SetVisible(false);
                        }
                        m_SkillInfo->SetVisible(false);
                        m_arrow->SetPosition({-25, -200});
                        m_CurrentFighting = FightID::UPDATEINFO;
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
                               ((m_PlayerPokemon->GetSkill().size() == 4 && m_arrow->GetPosition().y != -310) ||
                                (m_PlayerPokemon->GetSkill().size() == 3 && m_arrow->GetPosition().y != -270) ||
                                (m_PlayerPokemon->GetSkill().size() == 2 && m_arrow->GetPosition().y != -230))) {
                        m_arrow->SetPosition({m_arrow->GetPosition().x, m_arrow->GetPosition().y - 40});
                    }
                    if (m_arrow->GetPosition().y == -190) {
                        m_SkillInfo->SetText("型態:" + m_PlayerPokemon->GetSkillType()[0] + "\n" +
                                             m_PlayerPokemon->GetCurrentSkillPP()[0] + " / " +
                                             m_PlayerPokemon->GetSkillPP()[0]);
                    } else if (m_arrow->GetPosition().y == -230) {
                        m_SkillInfo->SetText("型態:" + m_PlayerPokemon->GetSkillType()[1] + "\n" +
                                             m_PlayerPokemon->GetCurrentSkillPP()[1] + " / " +
                                             m_PlayerPokemon->GetSkillPP()[1]);
                    } else if (m_arrow->GetPosition().y == -270) {
                        m_SkillInfo->SetText("型態:" + m_PlayerPokemon->GetSkillType()[2] + "\n" +
                                             m_PlayerPokemon->GetCurrentSkillPP()[2] + " / " +
                                             m_PlayerPokemon->GetSkillPP()[2]);
                    } else if (m_arrow->GetPosition().y == -310) {
                        m_SkillInfo->SetText("型態:" + m_PlayerPokemon->GetSkillType()[3] + "\n" +
                                             m_PlayerPokemon->GetCurrentSkillPP()[3] + " / " +
                                             m_PlayerPokemon->GetSkillPP()[3]);
                    }
                    break;
            }
            break;

        case FightID::UPDATEINFO:
            m_PlayerPokeInfo->SetDrawable(std::make_unique<Util::Text>(
                    RESOURCE_DIR"/text.ttf", 30,
                    "IV:" + std::to_string(m_PlayerPokemon->GetIV()) + "\n" +
                    "HP:" + std::to_string(m_PlayerPokemon->GetHP()) + "\n" +
                    "Attack:" + std::to_string(m_PlayerPokemon->GetAttack()) + "\n" +
                    "Defence:" + std::to_string(m_PlayerPokemon->GetDefence()) + "\n" +
                    "Special:" + std::to_string(m_PlayerPokemon->GetSpecial()) + "\n" +
                    "Speed:" + std::to_string(m_PlayerPokemon->GetSpeed()),
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
                    std::to_string(m_PlayerPokemon->GetCurrentHP()) + " / " +
                    std::to_string(m_PlayerPokemon->GetHP()));
            if (m_PlayerPokemon->IsSkillFull()) {
                for (size_t i = 0; i < 4; i++) {
                    m_AllSkills[i]->SetText(m_PlayerPokemon->GetSkill()[i]);
                }
            } else if (m_PlayerPokemon->GetSkill().size() >= 3) {
                for (size_t i = 0; i < 3; i++) {
                    m_AllSkills[i]->SetText(m_PlayerPokemon->GetSkill()[i]);
                }
            } else if (m_PlayerPokemon->GetSkill().size() >= 2) {
                for (size_t i = 0; i < 2; i++) {
                    m_AllSkills[i]->SetText(m_PlayerPokemon->GetSkill()[i]);
                }
            } else if (!m_PlayerPokemon->GetSkill().empty()) {
                for (size_t i = 0; i < 1; i++) {
                    m_AllSkills[i]->SetText(m_PlayerPokemon->GetSkill()[i]);
                }
            }
            m_AllSkills[0]->SetPosition({(m_PlayerPokemon->GetSkill()[0].length() / 4 * 17), -190});
            m_AllSkills[0]->SetPosition({m_AllSkills[0]->GetPosition().x - 120, -190});
            m_Root.AddChild(m_AllSkills[0]);
            m_AllSkills[1]->SetPosition({(m_PlayerPokemon->GetSkill()[1].length() / 4 * 17), -230});
            m_AllSkills[1]->SetPosition({m_AllSkills[1]->GetPosition().x - 120, -230});
            m_Root.AddChild(m_AllSkills[1]);
            m_AllSkills[2]->SetPosition({(m_PlayerPokemon->GetSkill()[2].length() / 4 * 17), -270});
            m_AllSkills[2]->SetPosition({m_AllSkills[2]->GetPosition().x - 120, -270});
            m_Root.AddChild(m_AllSkills[2]);
            m_AllSkills[3]->SetPosition({(m_PlayerPokemon->GetSkill()[3].length() / 4 * 17), -310});
            m_AllSkills[3]->SetPosition({m_AllSkills[3]->GetPosition().x - 120, -310});
            m_Root.AddChild(m_AllSkills[3]);
            m_CurrentFighting = FightID::HOME;
            break;

        case FightID::SHOWPLAYER:
            if (m_TB->GetVisibility() && Util::Input::IsKeyDown(Util::Keycode::Z)){
                m_TB->Next();
            }
            if (!m_TB->GetVisibility()){
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