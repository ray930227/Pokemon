#include "App.hpp"

void App::Fight() {
    //Looking for position
    if (Util::Input::IsKeyDown(Util::Keycode::KP_ENTER) || Util::Input::IsKeyPressed(Util::Keycode::RETURN)) {
        LOG_DEBUG("Position:({},{})", Util::Input::GetCursorPosition().x, Util::Input::GetCursorPosition().y);
    }

    if (Util::Input::IsKeyPressed(Util::Keycode::H)) {
        m_PlayerHPimage->SetScale({0.2, 1});
    }

    if (Util::Input::IsKeyDown(Util::Keycode::U)) {
        m_PlayerPokemon->LevelUp();
        m_PlayerPokeInfo->SetDrawable(std::make_unique<Util::Text>(
                RESOURCE_DIR"/text.ttf", 30,
                "IV:" + std::to_string(m_PlayerPokemon->GetIV()) + "\n" +
                "HP:" + std::to_string(m_PlayerPokemon->GetHP()) + "\n" +
                "Attack:" + std::to_string(m_PlayerPokemon->GetAttack()) + "\n" +
                "Defence:" + std::to_string(m_PlayerPokemon->GetDefence()) + "\n" +
                "Special:" + std::to_string(m_PlayerPokemon->GetSpecial()) + "\n" +
                "Speed:" + std::to_string(m_PlayerPokemon->GetSpeed()),
                Util::Color::FromName(Util::Colors::WHITE)));
        m_PlayerPokeName->SetText(m_PlayerPokemon->GetName() + " LV:" + std::to_string(m_PlayerPokemon->GetLV()));
    }

    if ((m_PlayerHPimage->GetScaledSize().x) <= 91.200005) {
        m_PlayerHPimage->SetImage(RESOURCE_DIR"/Fight/RedHealth.png");
    }

    if (m_FightLoad1_1->GetPosition().x != 720 && m_FightLoad1_1->GetVisibility()) {
        m_FightLoad1_1->SetPosition({m_FightLoad1_1->GetPosition().x + 15, 0});
        m_FightLoad1_2->SetPosition({m_FightLoad1_2->GetPosition().x - 15, 0});
    } else {
        m_FightLoad1_1->SetPosition({-720, 0});
        m_FightLoad1_2->SetPosition({720, 0});
        m_FightLoad1_1->SetVisible(false);
        m_FightLoad1_2->SetVisible(false);
        m_FightBG->SetVisible(true);
        m_arrow->SetVisible(true);
        m_PlayerHPimage->SetVisible(true);
        m_EnemyHPimage->SetVisible(true);
        m_PlayerPokemon->SetVisible(true);
        m_EnemyPokemon->SetVisible(true);
        m_PlayerHP->SetVisible(true);
        m_PlayerPokeName->SetVisible(true);
        m_EnemyPokeName->SetVisible(true);
        m_PlayerPokeInfo->SetVisible(true);
        m_EnemyPokeInfo->SetVisible(true);
    }

    //Fight select 技能(-25,-200) 精靈(135,-200)
    //             道具(-25,-300) 逃跑(135,-300)
    if (Util::Input::IsKeyPressed(Util::Keycode::UP) && m_arrow->GetPosition().y != -200
        && !m_Fightskill->GetVisibility() && !m_Fightitem->GetVisibility()) {
        m_arrow->SetPosition({m_arrow->GetPosition().x, m_arrow->GetPosition().y + 100});
    } else if (Util::Input::IsKeyPressed(Util::Keycode::DOWN) && m_arrow->GetPosition().y != -300
               && !m_Fightskill->GetVisibility() && !m_Fightitem->GetVisibility()) {
        m_arrow->SetPosition({m_arrow->GetPosition().x, m_arrow->GetPosition().y - 100});
    } else if (Util::Input::IsKeyPressed(Util::Keycode::RIGHT) && m_arrow->GetPosition().x != 135
               && !m_Fightskill->GetVisibility() && !m_Fightitem->GetVisibility()) {
        m_arrow->SetPosition({m_arrow->GetPosition().x + 160, m_arrow->GetPosition().y});
    } else if (Util::Input::IsKeyPressed(Util::Keycode::LEFT) && m_arrow->GetPosition().x != -25
               && !m_Fightskill->GetVisibility() && !m_Fightitem->GetVisibility()) {
        m_arrow->SetPosition({m_arrow->GetPosition().x - 160, m_arrow->GetPosition().y});
    }

    //進入技能選單
    if (!m_Fightskill->GetVisibility() && Util::Input::IsKeyPressed(Util::Keycode::Z)
        && m_arrow->GetPosition().x == -25 && m_arrow->GetPosition().y == -200) {
        m_Fightskill->SetVisible(true);
        m_Skill1->SetVisible(true);
        m_Skill2->SetVisible(true);
        m_Skill3->SetVisible(true);
        m_Skill4->SetVisible(true);
        m_arrow->SetPosition({-170, -190});
    }
    if (m_Fightskill->GetVisibility()) {
        m_SkillInfo->SetVisible(true);
        if (Util::Input::IsKeyDown(Util::Keycode::UP) && m_arrow->GetPosition().y != -190) {
            m_arrow->SetPosition({m_arrow->GetPosition().x, m_arrow->GetPosition().y + 40});
        } else if (Util::Input::IsKeyDown(Util::Keycode::DOWN) && m_arrow->GetPosition().y != -310) {
            m_arrow->SetPosition({m_arrow->GetPosition().x, m_arrow->GetPosition().y - 40});
        }
        if (m_arrow->GetPosition().y == -190) {
            m_SkillInfo->SetText("型態:" + m_PlayerPokemon->GetSkillType()[0] + "\n" +
                                 m_PlayerPokemon->GetSkillPP()[0] + " / " + m_PlayerPokemon->GetSkillPP()[0]);
        } else if (m_arrow->GetPosition().y == -230) {
            m_SkillInfo->SetText("型態:" + m_PlayerPokemon->GetSkillType()[1] + "\n" +
                                 m_PlayerPokemon->GetSkillPP()[1] + " / " + m_PlayerPokemon->GetSkillPP()[1]);
        } else if (m_arrow->GetPosition().y == -270) {
            m_SkillInfo->SetText("型態:" + m_PlayerPokemon->GetSkillType()[2] + "\n" +
                                 m_PlayerPokemon->GetSkillPP()[2] + " / " + m_PlayerPokemon->GetSkillPP()[2]);
        } else if (m_arrow->GetPosition().y == -310) {
            m_SkillInfo->SetText("型態:" + m_PlayerPokemon->GetSkillType()[3] + "\n" +
                                 m_PlayerPokemon->GetSkillPP()[3] + " / " + m_PlayerPokemon->GetSkillPP()[3]);
        }
    }
    //進入道具選單
    if (!m_Fightitem->GetVisibility() && Util::Input::IsKeyPressed(Util::Keycode::Z)
        && m_arrow->GetPosition().x == -25 && m_arrow->GetPosition().y == -300) {
        m_Fightitem->SetVisible(true);
        m_arrow->SetPosition({-150, 160});
    }
    //逃跑
    if (!m_Fightskill->GetVisibility() && !m_Fightitem->GetVisibility()
        && Util::Input::IsKeyPressed(Util::Keycode::Z)
        && m_arrow->GetPosition().x == 135 && m_arrow->GetPosition().y == -300) {
        m_arrow->SetPosition({-25, -200});
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
    //返回
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
        }
    }

    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }

    m_Root.Update();
}