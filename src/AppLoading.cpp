#include "App.hpp"

void App::Loading() {
    switch (m_CurrentLoading) {
        case LoadingID::INTO:
            if (m_FightLoad1_1->GetPosition().x != 720 && m_FightLoad1_1->GetVisibility()) {
                m_FightLoad1_1->Move({15, 0});
                m_FightLoad1_2->Move({-15, 0});
            } else {
                m_WhiteBG->SetVisible(true);
                m_WhiteBG->SetZIndex(51);
                m_tempImage->SetVisible(true);
                m_tempImage->SetZIndex(52);
                m_EnemyPokemonImage->SetVisible(true);
                m_TB->SetVisible(true);
                if (m_tempImage->GetPosition().x != -210) {
                    m_tempImage->Move({-10, 0});
                    m_EnemyPokemonImage->Move({10, 0});
                } else {
                    m_TB->Next();
                    m_FightLoad1_1->SetPosition({-720, 0});
                    m_FightLoad1_2->SetPosition({720, 0});
                    m_FightLoad1_1->SetVisible(false);
                    m_FightLoad1_2->SetVisible(false);
                    m_CurrentLoading = LoadingID::TEXT;
                }
            }
            break;
        case LoadingID::TEXT:
            if (m_TB->GetText().find("<WildPokemon>") < m_TB->GetText().size()) {
                std::string tempStr = m_TB->GetText();
                tempStr.replace(tempStr.begin() + tempStr.find("<WildPokemon>"),
                                tempStr.begin() + tempStr.find("<WildPokemon>") + 13,
                                m_EnemyPokemon->GetName());
                m_TB->SetText(tempStr);
            }
            if (m_TB->GetText().find("<PlayerPokemon>") < m_TB->GetText().size()) {
                std::string tempStr = m_TB->GetText();
                tempStr.replace(tempStr.begin() + tempStr.find("<PlayerPokemon>"),
                                tempStr.begin() + tempStr.find("<PlayerPokemon>") + 15,
                                m_PlayerPokemon->GetName());
                m_TB->SetText(tempStr);
            }
            switch (m_TB->GetLineIndex()) {
                case 2:
                    if (m_TB->GetVisibility() && (Util::Input::IsKeyDown(Util::Keycode::Z))) {
                        m_TB->Next();
                        m_BallAnimation->Reset();
                        m_BallAnimation->SetVisible(true);
                        m_BallAnimation->Play();
                        m_PlayerPokemonImage->SetScale({0.5, 0.5});
                    }
                    m_PlayerBalls->SetVisible(true);
                    break;
                case 3:
                    m_PlayerHP->SetText(
                            std::to_string(m_PlayerPokemon->GetCurrentHP()) + " / " +
                            std::to_string(m_PlayerPokemon->GetHP()));
                    m_PlayerPokeName->SetText(
                            m_PlayerPokemon->GetName() + " LV:" + std::to_string(m_PlayerPokemon->GetLV()));
                    m_EnemyPokeName->SetText(
                            m_EnemyPokemon->GetName() + " LV:" + std::to_string(m_EnemyPokemon->GetLV()));
                    std::vector<std::shared_ptr<Text>> m_SkillAll;
                    m_SkillAll.push_back(m_Skill1);
                    m_SkillAll.push_back(m_Skill2);
                    m_SkillAll.push_back(m_Skill3);
                    m_SkillAll.push_back(m_Skill4);
                    if (!m_PlayerPokemon->GetSkill().empty()) {
                        m_Skill1->SetText(m_PlayerPokemon->GetSkill()[0]);
                    }
                    if (m_PlayerPokemon->GetSkill().size() >= 2) {
                        m_Skill2->SetText(m_PlayerPokemon->GetSkill()[1]);
                    }
                    if (m_PlayerPokemon->GetSkill().size() >= 3) {
                        m_Skill3->SetText(m_PlayerPokemon->GetSkill()[2]);
                    }
                    if (m_PlayerPokemon->IsSkillFull()) {
                        m_Skill4->SetText(m_PlayerPokemon->GetSkill()[3]);
                    }
                    int GetSkillIndex = 0;
                    int SkillOfY = -190;
                    for (const auto &skill: m_SkillAll) {
                        skill->SetZIndex(55);
                        skill->SetVisible(false);
                        skill->SetPosition({(m_PlayerPokemon->GetSkill()[GetSkillIndex].length() / 4 * 17), SkillOfY});
                        skill->SetPosition({skill->GetPosition().x - 120, SkillOfY});
                        GetSkillIndex++;
                        SkillOfY -= 40;
                        m_Root.AddChild(skill);
                    }
                    m_PlayerBalls->SetVisible(false);
                    m_EnemyHPUI->SetVisible(true);
                    m_EnemyHPimage->SetVisible(true);
                    m_EnemyPokeName->SetVisible(true);
                    if (m_PlayerPokemonImage->GetScale().x >= 1 && m_TB->GetVisibility() &&
                        (Util::Input::IsKeyDown(Util::Keycode::Z))) {
                        m_TB->Next();
                    }
                    if (m_tempImage->GetPosition().x != -620) {
                        m_tempImage->Move({-10, 0});
                    } else {
                        if (m_BallAnimation->IsAnimationEnds()) {
                            if (m_PlayerPokemonImage->GetScale().x <= 1.0) {
                                m_PlayerPokemonImage->SetScale(
                                        {m_PlayerPokemonImage->GetScale().x + 0.05,
                                         m_PlayerPokemonImage->GetScale().y + 0.05});
                            }
                            m_BallAnimation->SetVisible(false);
                            m_PlayerPokemonImage->SetVisible(true);
                            m_PlayerHPUI->SetVisible(true);
                            m_PlayerHPimage->SetVisible(true);
                            m_PlayerPokeName->SetVisible(true);
                            m_PlayerHP->SetVisible(true);
                        }
                        if (!m_TB->GetVisibility()) {
                            m_arrow->SetVisible(true);
                            m_PlayerPokeInfo->SetVisible(true);
                            m_EnemyPokeInfo->SetVisible(true);
                            m_BallAnimation->SetCurrentFrame(0);
                            m_CurrentFighting = FightID::HOME;
                            m_CurrentState = State::FIGHT;
                        }

                    }
                    break;
            }
            if (!m_TB->GetVisibility()) {
                m_FightBG->SetVisible(true);
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