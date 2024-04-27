#include "App.hpp"

void App::Fight() {
    switch (m_CurrentFighting) {
        case FightID::SELECT:
            //Fight select 技能(-25,-200) 精靈(135,-200)
            //             道具(-25,-300) 逃跑(135,-300)
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

            //進入技能選單
            if (!m_Fightskill->GetVisibility() && Util::Input::IsKeyDown(Util::Keycode::Z)
                && m_arrow->GetPosition().x == -25 && m_arrow->GetPosition().y == -200) {
                m_Fightskill->SetVisible(true);
                m_Skill1->SetVisible(true);
                m_Skill2->SetVisible(true);
                m_Skill3->SetVisible(true);
                m_Skill4->SetVisible(true);
                m_arrow->SetPosition({-170, -190});
            } else if (m_Fightskill->GetVisibility()) {
                m_SkillInfo->SetVisible(true);
                if (Util::Input::IsKeyDown(Util::Keycode::UP) && m_arrow->GetPosition().y != -190) {
                    m_arrow->SetPosition({m_arrow->GetPosition().x, m_arrow->GetPosition().y + 40});
                } else if (Util::Input::IsKeyDown(Util::Keycode::DOWN) &&
                           ((m_PlayerPokemon->GetSkill().size() == 4 && m_arrow->GetPosition().y != -310) ||
                            (m_PlayerPokemon->GetSkill().size() == 3 && m_arrow->GetPosition().y != -270) ||
                            (m_PlayerPokemon->GetSkill().size() == 2 && m_arrow->GetPosition().y != -230))) {
                    m_arrow->SetPosition({m_arrow->GetPosition().x, m_arrow->GetPosition().y - 40});

                }
                if (Util::Input::IsKeyDown(Util::Keycode::Z)) {
                    m_CurrentFighting = FightID::FIGHT;
                } else if (m_arrow->GetPosition().y == -190) {
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
            }
                //進入道具選單
            else if (!m_Fightitem->GetVisibility() && Util::Input::IsKeyDown(Util::Keycode::Z)
                     && m_arrow->GetPosition().x == -25 && m_arrow->GetPosition().y == -300) {
                m_Fightitem->SetVisible(true);
                m_arrow->SetPosition({-150, 160});
            }
                //進入選擇寶可夢介面
            else if (!m_FightPokemon->GetVisibility() && Util::Input::IsKeyDown(Util::Keycode::Z)
                     && m_arrow->GetPosition().x == 135 && m_arrow->GetPosition().y == -200) {
                m_arrow->SetVisible(false);
                m_FightPokemon->SetVisible(true);
            }
                //逃跑
            else if (!m_Fightskill->GetVisibility() && !m_Fightitem->GetVisibility()
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
                m_PlayerPokemon->SetVisible(false);
                m_EnemyPokemon->SetVisible(false);
                m_PlayerHP->SetVisible(false);
                m_PlayerPokeName->SetVisible(false);
                m_EnemyPokeName->SetVisible(false);
                m_PlayerPokeInfo->SetVisible(false);
                m_EnemyPokeInfo->SetVisible(false);
                m_BGM->LoadMedia(RESOURCE_DIR"/BGM/PalletTown.mp3");
                m_BGM->Play();
                m_CurrentState = State::UPDATE;
            }
            if (Util::Input::IsKeyPressed(Util::Keycode::X)) {
                if (m_Fightskill->GetVisibility()) {
                    m_Fightskill->SetVisible(false);
                    m_Skill1->SetVisible(false);
                    m_Skill2->SetVisible(false);
                    m_Skill3->SetVisible(false);
                    m_Skill4->SetVisible(false);
                    m_arrow->SetVisible(true);
                    m_SkillInfo->SetVisible(false);
                    m_arrow->SetPosition({-25, -200});
                } else if (m_Fightitem->GetVisibility()) {
                    m_Fightitem->SetVisible(false);
                    m_arrow->SetVisible(true);
                    m_arrow->SetPosition({-25, -200});
                } else if (m_FightPokemon->GetVisibility()) {
                    m_FightPokemon->SetVisible(false);
                    m_arrow->SetVisible(true);
                    m_arrow->SetPosition({-25, -200});
                }
            }
            break;
        case FightID::FIGHT:
            if (m_arrow->GetPosition().y == -190) {
                if (m_PlayerPokemon->GetSkillClass()[0] == "變化") {
                    LOG_DEBUG("Status is not ready");
                } else {
                    m_EnemyPokemon->PokemonHurt(
                            round((((2.0 * m_PlayerPokemon->GetLV() + 10) / 250) *
                                   (1.0 * m_PlayerPokemon->GetAttack() / m_EnemyPokemon->GetDefence()) *
                                   std::stof(m_PlayerPokemon->GetSkillDamge()[0]) + 2) *
                                  PokeFunction::TypeDamage(m_PlayerPokemon->GetSkillType()[0],
                                                           m_EnemyPokemon->GetType())));
                    m_PlayerPokemon->ReducePP(0);
                }

            } else if (m_arrow->GetPosition().y == -230) {
                if (m_PlayerPokemon->GetSkillClass()[1] == "變化") {
                    LOG_DEBUG("Status is not ready");
                } else {
                    m_EnemyPokemon->PokemonHurt(
                            round((((2.0 * m_PlayerPokemon->GetLV() + 10) / 250) *
                                   (1.0 * m_PlayerPokemon->GetAttack() / m_EnemyPokemon->GetDefence()) *
                                   std::stof(m_PlayerPokemon->GetSkillDamge()[1]) + 2) *
                                  PokeFunction::TypeDamage(m_PlayerPokemon->GetSkillType()[1],
                                                           m_EnemyPokemon->GetType())));
                    m_PlayerPokemon->ReducePP(1);
                }
            } else if (m_arrow->GetPosition().y == -270) {
                if (m_PlayerPokemon->GetSkillClass()[2] == "變化") {
                    LOG_DEBUG("Status is not ready");
                } else {
                    m_EnemyPokemon->PokemonHurt(
                            round((((2.0 * m_PlayerPokemon->GetLV() + 10) / 250) *
                                   (1.0 * m_PlayerPokemon->GetAttack() / m_EnemyPokemon->GetDefence()) *
                                   std::stof(m_PlayerPokemon->GetSkillDamge()[2]) + 2) *
                                  PokeFunction::TypeDamage(m_PlayerPokemon->GetSkillType()[2],
                                                           m_EnemyPokemon->GetType())));
                    m_PlayerPokemon->ReducePP(2);
                }
            } else if (m_arrow->GetPosition().y == -310) {
                if (m_PlayerPokemon->GetSkillClass()[3] == "變化") {
                    LOG_DEBUG("Status is not ready");
                } else {
                    m_EnemyPokemon->PokemonHurt(
                            round((((2.0 * m_PlayerPokemon->GetLV() + 10) / 250) *
                                   (1.0 * m_PlayerPokemon->GetAttack() / m_EnemyPokemon->GetDefence()) *
                                   std::stof(m_PlayerPokemon->GetSkillDamge()[3]) + 2) *
                                  PokeFunction::TypeDamage(m_PlayerPokemon->GetSkillType()[3],
                                                           m_EnemyPokemon->GetType())));
                    m_PlayerPokemon->ReducePP(3);
                }
            }
            if (1.0 * m_EnemyPokemon->GetCurrentHP() / m_EnemyPokemon->GetHP() <= 0) {
                m_EnemyHPimage->SetScale({0, 1});
            } else {
                m_EnemyHPimage->SetScale({(1.0 * m_EnemyPokemon->GetCurrentHP() / m_EnemyPokemon->GetHP()), 1});
            }
            m_Fightskill->SetVisible(false);
            m_Skill1->SetVisible(false);
            m_Skill2->SetVisible(false);
            m_Skill3->SetVisible(false);
            m_Skill4->SetVisible(false);
            m_arrow->SetVisible(true);
            m_SkillInfo->SetVisible(false);
            m_arrow->SetPosition({-25, -200});
            m_CurrentFighting = FightID::SELECT;
            break;
        case FightID::NONE:
            break;
    }
//    //Looking for position
    if (Util::Input::IsKeyDown(Util::Keycode::KP_ENTER) || Util::Input::IsKeyPressed(Util::Keycode::RETURN)) {
        LOG_DEBUG("Position:({},{})", Util::Input::GetCursorPosition().x, Util::Input::GetCursorPosition().y);
    }

    if (Util::Input::IsKeyDown(Util::Keycode::U)) {
        m_PlayerPokemon->LevelUp();
        m_EnemyPokemon->LevelUp();
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
        m_PlayerPokeName->SetText(m_PlayerPokemon->GetName() + " LV:" + std::to_string(m_PlayerPokemon->GetLV()));
        m_EnemyPokeName->SetText(m_EnemyPokemon->GetName() + " LV:" + std::to_string(m_EnemyPokemon->GetLV()));
        m_PlayerHP->SetText(
                std::to_string(m_PlayerPokemon->GetCurrentHP()) + " / " + std::to_string(m_PlayerPokemon->GetHP()));
        if (m_PlayerPokemon->IsSkillFull()) {
            m_Skill1->SetText(m_PlayerPokemon->GetSkill()[0]);
            m_Skill2->SetText(m_PlayerPokemon->GetSkill()[1]);
            m_Skill3->SetText(m_PlayerPokemon->GetSkill()[2]);
            m_Skill4->SetText(m_PlayerPokemon->GetSkill()[3]);
        } else if (m_PlayerPokemon->GetSkill().size() >= 3) {
            m_Skill1->SetText(m_PlayerPokemon->GetSkill()[0]);
            m_Skill2->SetText(m_PlayerPokemon->GetSkill()[1]);
            m_Skill3->SetText(m_PlayerPokemon->GetSkill()[2]);
        } else if (m_PlayerPokemon->GetSkill().size() >= 2) {
            m_Skill1->SetText(m_PlayerPokemon->GetSkill()[0]);
            m_Skill2->SetText(m_PlayerPokemon->GetSkill()[1]);
        } else if (!m_PlayerPokemon->GetSkill().empty()) {
            m_Skill1->SetText(m_PlayerPokemon->GetSkill()[0]);
        }
        std::vector<std::shared_ptr<Text>> m_SkillAll;
        m_SkillAll.push_back(m_Skill1);
        m_SkillAll.push_back(m_Skill2);
        m_SkillAll.push_back(m_Skill3);
        m_SkillAll.push_back(m_Skill4);
        int GetSkillIndex = 0;
        int SkillOfY = -190;
        for (const auto &skill: m_SkillAll) {
            skill->SetPosition({(m_PlayerPokemon->GetSkill()[GetSkillIndex].length() / 4 * 17), SkillOfY});
            skill->SetPosition({skill->GetPosition().x - 120, SkillOfY});
            GetSkillIndex++;
            SkillOfY -= 40;
            m_Root.AddChild(skill);
        }
    }

    if ((m_PlayerHPimage->GetScaledSize().x) <= 91.200005) {
        m_PlayerHPimage->SetImage(RESOURCE_DIR"/Fight/RedHealth.png");
    }

    if ((m_EnemyHPimage->GetScaledSize().x) <= 91.200005) {
        m_EnemyHPimage->SetImage(RESOURCE_DIR"/Fight/RedHealth.png");
    }

    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }

    m_Root.Update();
}