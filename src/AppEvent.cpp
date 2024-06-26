#include "App.hpp"

void App::Event() {
    auto PlayerPosition = m_MapSystem->GetPlayerPosition();
    auto currnetMap = m_MapSystem->GetCurrnetMap();
    glm::vec2 TargetPosition = m_MapSystem->GetPlayerPosition();
    if (m_CurrentDirection == "UP") TargetPosition.x--;
    else if (m_CurrentDirection == "DOWN") TargetPosition.x++;
    else if (m_CurrentDirection == "LEFT") TargetPosition.y--;
    else TargetPosition.y++;

    if (m_CurrentEvent == EventID::MOVE) {
        //region
        if (m_DisplacementCount != 0) {
            glm::vec2 PlayerPosition = m_MapSystem->GetPlayerPosition();

            bool up = m_CurrentDirection == "UP" &&
                      m_MapSystem->GetBlocks()[PlayerPosition.x - 1][PlayerPosition.y]->GetTraversable();
            bool down = m_CurrentDirection == "DOWN" &&
                        m_MapSystem->GetBlocks()[PlayerPosition.x + 1][PlayerPosition.y]->GetTraversable();
            bool left = m_CurrentDirection == "LEFT" &&
                        m_MapSystem->GetBlocks()[PlayerPosition.x][PlayerPosition.y - 1]->GetTraversable();
            bool right = m_CurrentDirection == "RIGHT" &&
                         m_MapSystem->GetBlocks()[PlayerPosition.x][PlayerPosition.y + 1]->GetTraversable();
            bool canMove = up || down || left || right;

            if (!((m_DisplacementCount == m_Player->GetSpeed() && canMove) ||
                  m_DisplacementCount != m_Player->GetSpeed())) {
                if (m_CurrentDirection == "DOWN" &&
                    m_MapSystem->GetBlocks()[PlayerPosition.x + 1][PlayerPosition.y]->GetEventID() ==
                    (int) EventID::JUMP) {
                    m_CurrentEvent = EventID::JUMP;
                    m_DisplacementCount *= 2;
                } else if (m_CurrentDirection == "DOWN" &&
                           m_MapSystem->GetBlocks()[PlayerPosition.x + 1][PlayerPosition.y]->GetEventID() ==
                           (int) EventID::DOOR) {
                    m_CurrentEvent = EventID::DOOR;
                    m_Displacement = {0, 0};
                } else {
                    m_Displacement = {0, 0};
                }
            }
            m_MapSystem->Move(m_Displacement);
            if (m_DisplacementCount == m_Player->GetSpeed() / 4 ||
                m_DisplacementCount == m_Player->GetSpeed() / 3 * 2) {
                size_t FrameCount = m_Player->GetImage()->GetFrameCount();
                size_t CurrentFrameIndex = m_Player->GetImage()->GetCurrentFrameIndex();
                m_Player->GetImage()->SetCurrentFrame((CurrentFrameIndex + 1) % FrameCount);
            }

            m_DisplacementCount--;
            if (m_DisplacementCount == 0) {
                m_MapSystem->SetPosition({round(m_MapSystem->GetPosition().x), round(m_MapSystem->GetPosition().y)});
                glm::vec2 playerPosition = m_MapSystem->GetPlayerPosition();
                std::shared_ptr<Block> block = m_MapSystem->GetBlocks()[playerPosition.x][playerPosition.y];
                if (block->GetEventID() != 0 && (m_Displacement.x != 0 || m_Displacement.y != 0)) {
                    if (block->GetEventID() == (int) EventID::GRASS && m_Player->GetPokemonBag()->Size() == 0) {
                        m_TB->ReadLines(RESOURCE_DIR"/Lines/FirstInGrass.txt");
                        m_TB->SetVisible(true);
                        m_CurrentEvent = EventID::CHOOSE_POKEMON;
                    } else {
                        m_CurrentEvent = (EventID) block->GetEventID();
                    }
                } else if (m_CurrentDirection == "UP" && Util::Input::IsKeyPressed(Util::Keycode::UP)) {
                    m_DisplacementCount = m_Player->GetSpeed();
                } else if (m_CurrentDirection == "DOWN" && Util::Input::IsKeyPressed(Util::Keycode::DOWN)) {
                    m_DisplacementCount = m_Player->GetSpeed();
                } else if (m_CurrentDirection == "LEFT" && Util::Input::IsKeyPressed(Util::Keycode::LEFT)) {
                    m_DisplacementCount = m_Player->GetSpeed();
                } else if (m_CurrentDirection == "RIGHT" && Util::Input::IsKeyPressed(Util::Keycode::RIGHT)) {
                    m_DisplacementCount = m_Player->GetSpeed();
                } else {
                    m_CurrentEvent = EventID::NONE;
                    m_CurrentState = State::UPDATE;
                }

            }
        }//endregion
    } else if (m_CurrentEvent == EventID::DOOR) {
        //region

        if (m_WhiteBG->GetZIndex() == 0) {
            m_WhiteBG->SetVisible(true);
            m_WhiteBG->SetZIndex(99);
        } else if (m_WhiteBG->GetZIndex() > 90) {
            m_WhiteBG->SetZIndex(m_WhiteBG->GetZIndex() - 1);
        } else {
            if (currnetMap == "MainMap") {
                if (PlayerPosition.x == 83 && PlayerPosition.y == 65) {
                    m_MapSystem->SetMap("PlayerHouse1F");
                    m_MapSystem->SetPosition({144, 216});
                } else if (PlayerPosition.x == 89 && PlayerPosition.y == 72) {
                    m_MapSystem->SetMap("OakLab");
                    m_MapSystem->SetPosition({72, 360});
                } else if ((PlayerPosition.x == 25 && PlayerPosition.y == 79) ||
                           (PlayerPosition.x == 21 && PlayerPosition.y == 33)) {
                    m_MapSystem->SetMap("PokeMart");
                    m_MapSystem->SetPosition({72, 216});
                } else if ((PlayerPosition.x == 31 && PlayerPosition.y == 73) ||
                           (PlayerPosition.x == 29 && PlayerPosition.y == 23)) {
                    m_MapSystem->SetMap("PokeCenter");
                    m_MapSystem->SetPosition({288, 216});
                    m_BGM->LoadMedia(RESOURCE_DIR"/BGM/PokeCenter.mp3");
                    m_BGM->Play();
                } else if (PlayerPosition.x == 13 && PlayerPosition.y == 82) {
                    m_MapSystem->SetMap("GYM1");
                    m_MapSystem->SetPosition({72, 432});
                } else if (PlayerPosition.x == 21 && PlayerPosition.y == 26) {
                    m_MapSystem->SetMap("GYM2");
                    m_MapSystem->SetPosition({72, 432});
                }
            } else if (currnetMap == "PlayerHouse1F") {
                if (PlayerPosition.x == 2 && PlayerPosition.y == 8) {
                    m_MapSystem->SetMap("PlayerHouse2F");
                    m_MapSystem->SetPosition({-216, -216});
                } else {
                    m_MapSystem->SetMap("MainMap");
                    m_MapSystem->SetPosition({-1224, 2520});
                }
            } else if (currnetMap == "PlayerHouse2F") {
                m_MapSystem->SetMap("PlayerHouse1F");
                m_MapSystem->SetPosition({-216, -216});
            } else if (currnetMap == "OakLab") {
                m_MapSystem->SetMap("MainMap");
                m_MapSystem->SetPosition({-1728, 2952});
            } else if (currnetMap == "PokeMart" || currnetMap == "PokeCenter" || currnetMap == "GYM1" ||
                       currnetMap == "GYM2") {
                if (currnetMap == "PokeCenter") {
                    m_BGM->LoadMedia(RESOURCE_DIR"/BGM/PalletTown.mp3");
                    m_BGM->Play();
                }
                m_MapSystem->SetMap("MainMap");
            }
            m_WhiteBG->SetVisible(false);
            m_WhiteBG->SetZIndex(0);
            if (m_MapSystem->GetCurrnetMap() == "MainMap") {
                m_Displacement = {0, 72.0 / m_Player->GetSpeed()};
                m_DisplacementCount = m_Player->GetSpeed();
                m_CurrentDirection = "DOWN";
                m_Player->SetCurrentImagePath(1);
                m_CurrentEvent = EventID::MOVE;
            } else {
                m_CurrentState = State::UPDATE;
                m_CurrentEvent = EventID::NONE;
            }
        }
        //endregion
    } else if (m_CurrentEvent == EventID::GRASS) {
        //region
        if (m_Encounterable && rand() % 100 < 20) {
            m_IsWildPokemon = true;
            std::vector<int> tempID = {13, 16, 19, 21, 23, 25, 26, 27, 29, 31, 32, 34, 35, 36, 37, 38, 39, 40, 41, 43,
                                       45, 46, 48, 50, 52, 54, 56, 58, 59, 60, 62, 63, 65, 66, 68, 69, 71, 72, 74, 76,
                                       77, 79, 81, 83, 84, 86, 88, 90, 92, 95, 96, 98, 100, 102, 103, 104, 106, 107,
                                       108, 109, 111, 113, 114, 115, 116, 118, 120, 121, 122, 124, 125, 126, 127,
                                       128, 129, 131, 132};
            int r;
            std::stringstream ToString;
            if (m_Player->GetItemBag()->GetItemQuantity("藍色徽章") == 0) {
                r = rand() % tempID.size();
                ToString << std::setw(3) << std::setfill('0') << tempID[r];
            } else {
                r = rand() % 151;
                ToString << std::setw(3) << std::setfill('0') << r;
            }
            std::string StringID = ToString.str();
            auto temp = std::make_shared<Pokemon>(StringID);
            int average = 0;
            for (auto &i: m_Player->GetPokemonBag()->GetPokemons())
                average += i->GetLV();
            int lv = average / m_Player->GetPokemonBag()->GetPokemons().size() - 2 + rand() % 5;
            if (lv > 100) lv = 100;
            temp->SetLevel(lv);
            m_Enemy->GetPokemonBag()->SetPokemons({temp});
            m_CurrentLoading = LoadingID::INIT;
            m_CurrentState = State::LOADING;
            m_CurrentEvent = EventID::NONE;

        } else {
            m_CurrentEvent = EventID::MOVE;
            m_CurrentState = State::EVENT;
            if (m_CurrentDirection == "UP" && Util::Input::IsKeyPressed(Util::Keycode::UP)) {
                m_DisplacementCount = m_Player->GetSpeed();
            } else if (m_CurrentDirection == "DOWN" && Util::Input::IsKeyPressed(Util::Keycode::DOWN)) {
                m_DisplacementCount = m_Player->GetSpeed();
            } else if (m_CurrentDirection == "LEFT" && Util::Input::IsKeyPressed(Util::Keycode::LEFT)) {
                m_DisplacementCount = m_Player->GetSpeed();
            } else if (m_CurrentDirection == "RIGHT" && Util::Input::IsKeyPressed(Util::Keycode::RIGHT)) {
                m_DisplacementCount = m_Player->GetSpeed();
            } else {
                m_CurrentEvent = EventID::NONE;
                m_CurrentState = State::UPDATE;
            }
        }


        //endregion
    } else if (m_CurrentEvent == EventID::BILLBOARD) {
        //region
        if (!m_TB->GetVisibility()) {
            m_TB->Reload();
            if (TargetPosition.x == 83 && TargetPosition.y == 63) {
                m_TB->SetText(m_Player->GetName() + "的家");
            } else if (TargetPosition.x == 83 && TargetPosition.y == 71) {
                m_TB->SetText(m_NPCBromance->GetName() + "的家");
            } else if (TargetPosition.x == 87 && TargetPosition.y == 67) {
                m_TB->SetText("真新鎮");
            } else if (TargetPosition.x == 91 && TargetPosition.y == 73) {
                m_TB->SetText("大木博士的實驗室");
            } else if (TargetPosition.x == 13 && TargetPosition.y == 77) {
                m_TB->SetText("深灰市神奇寶貝道館館主：小剛\n如岩石般强大的男人。");
            } else if (TargetPosition.x == 69 && TargetPosition.y == 69) {
                m_TB->SetText("↑↑↑\n深灰市");
            } else if (TargetPosition.x == 35 && TargetPosition.y == 71) {
                m_TB->SetText("這裡是深灰市。\n深灰即是堅若磐石的灰黑之色。");
            } else if (TargetPosition.x == 23 && TargetPosition.y == 67) {
                m_TB->AddText("戰鬥招式的使用次數受招式點數的限制，它的簡稱ＰＰ。");
                m_TB->AddText("想要補充ＰＰ的話，那就到寶可夢中心，讓你的寶可夢好好休息吧！");
            } else if (TargetPosition.x == 7 && TargetPosition.y == 69) {
                m_TB->AddText("前方不可通行!!!");
            } else if (TargetPosition.x == 23 && TargetPosition.y == 43) {
                m_TB->SetText("歡迎來到華藍市");
            } else if (TargetPosition.x == 33 && TargetPosition.y == 29) {
                m_TB->SetText("這裡是華藍市。\n華藍即是神秘莫測的水藍之色。");
            } else if (TargetPosition.x == 13 && TargetPosition.y == 25) {
                m_TB->AddText("在寶可夢進化過程中，連按X鍵可以取消進化。");
            } else if (TargetPosition.x == 21 && TargetPosition.y == 21) {
                m_TB->SetText("華藍市神奇寶貝道館館主：小霞\n俏皮的美人魚。");
            } else if (TargetPosition.x == 27 && TargetPosition.y == 35) {
                m_TB->AddText("超級球提高了收服率，試試用它來抓那些很難收服的神奇寶貝。");
            } else {
                m_TB->SetText("(" + std::to_string((int) TargetPosition.x) + "," +
                              std::to_string((int) TargetPosition.y) +
                              ")'s billboard has not implement");
            }
            m_TB->SetVisible(true);
        }

        if (Util::Input::IsKeyDown(Util::Keycode::Z)) {
            m_TB->Next();
            if (!m_TB->GetVisibility()) {
                m_CurrentEvent = EventID::NONE;
                m_CurrentState = State::UPDATE;
            }
        }
        //endregion
    } else if (m_CurrentEvent == EventID::JUMP) {
        //region
        if (m_DisplacementCount != 0) {
            m_MapSystem->Move(m_Displacement);
            if (m_DisplacementCount > m_Player->GetSpeed()) {
                m_Player->GetImage()->Move(m_Displacement);
            } else {
                m_Player->GetImage()->Move({0, m_Displacement.y * -1});
            }
            m_DisplacementCount--;
        } else {
            m_MapSystem->SetPosition({round(m_MapSystem->GetPosition().x), round(m_MapSystem->GetPosition().y)});
            m_Player->GetImage()->SetPosition({36, -36});
            m_CurrentEvent = EventID::NONE;
            m_CurrentState = State::UPDATE;
        }
        //endregion
    } else if (m_CurrentEvent == EventID::WEEKTREE) {
        //region
        if (m_TB->GetVisibility()) {
            if (m_TFBox->GetVisible()) {
                if (m_TFBox->Choose()) {
                    m_TFBox->SetVisible(false);
                    if (m_TFBox->GetTF()) {
                        m_Root.RemoveChild(m_MapSystem->GetBlocks()[TargetPosition.x][TargetPosition.y]);
                        m_MapSystem->GetBlocks()[TargetPosition.x][TargetPosition.y]->SetTraversable(true);
                        m_MapSystem->GetBlocks()[TargetPosition.x][TargetPosition.y]->SetEvent(false);
                        m_MapSystem->GetBlocks()[TargetPosition.x][TargetPosition.y]->SetEventID(0);
                    }
                    m_CurrentEvent = EventID::NONE;
                    m_CurrentState = State::UPDATE;
                    m_TB->SetVisible(false);
                }
            } else {
                if (Util::Input::IsKeyDown(Util::Keycode::Z)) {
                    m_TB->SetVisible(false);
                    m_CurrentEvent = EventID::NONE;
                    m_CurrentState = State::UPDATE;
                }
            }
        } else {
            m_TB->SetText("沒有神奇寶貝擁有居合斬\n因此無法破換小樹叢");
            m_TB->SetVisible(true);
            for (auto &i: m_Player->GetPokemonBag()->GetPokemons()) {
                for (auto &j: i->GetSkill()) {
                    if (j == "居合斬") {
                        m_TB->SetText("是否要破壞小樹叢?");
                        m_TFBox->SetVisible(true);
                        break;
                    }
                }
                if (m_TFBox->GetVisible()) break;
            }
        }
        //endregion
    } else if (m_CurrentEvent == EventID::BALL) {
        //region
        if (m_TFBox->GetVisible()) {
            if (m_TFBox->Choose()) {
                m_TFBox->SetVisible(false);
                m_TB->SetVisible(false);
                if (m_TFBox->GetTF()) {
                    if (currnetMap == "OakLab") {
                        std::vector<std::string> Lines;
                        m_TB->SetVisible(true);
                        if (TargetPosition.x == 4 && TargetPosition.y == 8) {
                            m_Player->GetPokemonBag()->AddPomekon(std::make_shared<Pokemon>("004"));
                            Lines.push_back(m_Player->GetName() + "選擇了小火龍");
                        } else if (TargetPosition.x == 4 && TargetPosition.y == 9) {
                            m_Player->GetPokemonBag()->AddPomekon(std::make_shared<Pokemon>("007"));
                            Lines.push_back(m_Player->GetName() + "選擇了傑尼龜");
                        } else if (TargetPosition.x == 4 && TargetPosition.y == 10) {
                            m_Player->GetPokemonBag()->AddPomekon(std::make_shared<Pokemon>("001"));
                            Lines.push_back(m_Player->GetName() + "選擇了妙蛙種子");
                        }
                        m_Player->GetPokemonBag()->GetPokemons()[0]->SetLevel(8);
                        m_Root.RemoveChild(m_MapSystem->GetBlocks()[TargetPosition.x][TargetPosition.y]);
                        m_TB->ReadLines(Lines);
                        auto poke = m_Player->GetPokemonBag()->GetPokemons()[0];
                        auto Ability = poke->GetAbility();
                        Ability["IV"] = 31;
                        poke->SetAbility(Ability);
                        while (m_TB->GetVisibility()) {
                            if (Util::Input::IsKeyDown(Util::Keycode::Z)) {
                                m_TB->Next();
                            }
                            m_Root.Update();
                            auto context = Core::Context::GetInstance();
                            context->Update();
                        }
                    } else {

                    }
                }
                m_CurrentEvent = EventID::NONE;
                m_CurrentState = State::UPDATE;
            }
        } else {
            if (currnetMap == "OakLab") {
                if (m_Player->GetPokemonBag()->Size() == 0) {
                    m_TFBox->SetVisible(true);
                    m_TB->SetVisible(true);
                    if (TargetPosition.x == 4 && TargetPosition.y == 8) {
                        m_TB->SetText("是否要選擇小火龍");
                    } else if (TargetPosition.x == 4 && TargetPosition.y == 9) {
                        m_TB->SetText("是否要選擇傑尼龜");
                    } else if (TargetPosition.x == 4 && TargetPosition.y == 10) {
                        m_TB->SetText("是否要選擇妙蛙種子");
                    }
                } else {
                    m_CurrentEvent = EventID::NONE;
                    m_CurrentState = State::UPDATE;
                }
            } else {

            }
        }
        //endregion
    } else if (m_CurrentEvent == EventID::CHOOSE_POKEMON) {
        //region
        if (m_TB->GetVisibility()) {
            if (Util::Input::IsKeyDown(Util::Keycode::Z)) {
                m_TB->Next();
                if (m_TB->GetLineIndex() == 2) {
                    m_Player->SetCurrentImagePath(1);
                    m_NPCOak->SetCurrentImagePath(0);
                    m_NPCOak->GetImage()->SetVisible(true);
                    m_NPCOak->GetImage()->SetPosition({36, -180});
                    for (int i = 0; i < m_Player->GetSpeed(); i++) {
                        m_NPCOak->GetImage()->Move({0, 72.0 / m_Player->GetSpeed()});
                        if (i == m_Player->GetSpeed() / 4 || i == m_Player->GetSpeed() / 3 * 2) {
                            size_t FrameCount = m_NPCOak->GetImage()->GetFrameCount();
                            size_t CurrentFrameIndex = m_NPCOak->GetImage()->GetCurrentFrameIndex();
                            m_NPCOak->GetImage()->SetCurrentFrame((CurrentFrameIndex + 1) % FrameCount);
                        }

                        m_Root.Update();
                        auto context = Core::Context::GetInstance();
                        context->Update();
                    }
                    m_NPCOak->GetImage()->SetPosition(
                            {round(m_NPCOak->GetImage()->GetPosition().x),
                             round(m_NPCOak->GetImage()->GetPosition().y)});
                }

            }
            if (m_TB->GetText().find("<Player>") < m_TB->GetText().size()) {
                std::string tempStr = m_TB->GetText();
                tempStr.replace(tempStr.begin() + tempStr.find("<Player>"),
                                tempStr.begin() + tempStr.find("<Player>") + 8,
                                m_Player->GetName());
                m_TB->SetText(tempStr);
            }
            if (m_TB->GetText().find("<NPC_Bromance>") < m_TB->GetText().size()) {
                std::string tempStr = m_TB->GetText();
                tempStr.replace(tempStr.begin() + tempStr.find("<NPC_Bromance>"),
                                tempStr.begin() + tempStr.find("<NPC_Bromance>") + 14,
                                m_NPCBromance->GetName());
                m_TB->SetText(tempStr);
            }
        } else {
            std::vector<std::pair<int, glm::vec2>> temp;
            temp.push_back({1, {0, 72.0 / m_Player->GetSpeed()}});
            temp.push_back({m_MapSystem->GetPosition().x == -1584 ? 1 : 2, {72.0 / m_Player->GetSpeed(), 0}});
            temp.push_back({10, {0, 72.0 / m_Player->GetSpeed()}});
            temp.push_back({3, {-72.0 / m_Player->GetSpeed(), 0}});
            temp.push_back({1, {0, -72.0 / m_Player->GetSpeed()}});

            for (size_t i = 0; i < temp.size(); i++) {
                if (temp[i].second.y < 0) m_Player->SetCurrentImagePath(0);
                else if (temp[i].second.y > 0) m_Player->SetCurrentImagePath(1);
                else if (temp[i].second.x > 0) m_Player->SetCurrentImagePath(2);
                else m_Player->SetCurrentImagePath(3);

                for (int times = 0; times < temp[i].first; times++) {
//                    NPC_Oak->SetCurrentImagePath(1);
                    if (i == temp.size() - 1)
                        m_NPCOak->GetImage()->SetVisible(false);
                    for (int count = m_Player->GetSpeed(); count > 0; count--) {
                        m_MapSystem->Move(temp[i].second);
                        if (i + 1 < temp.size() && times == temp[i].first - 1) {
                            if (temp[i].second.x == 0)
                                m_NPCOak->GetImage()->Move({0 - temp[i + 1].second.x, temp[i].second.y});
                            else
                                m_NPCOak->GetImage()->Move({temp[i].second.x, 0 - temp[i + 1].second.y});

                            if (temp[i + 1].second.y < 0)
                                m_NPCOak->SetCurrentImagePath(0);
                            else if (temp[i + 1].second.y > 0)
                                m_NPCOak->SetCurrentImagePath(1);
                            else if (temp[i + 1].second.x > 0)
                                m_NPCOak->SetCurrentImagePath(2);
                            else
                                m_NPCOak->SetCurrentImagePath(3);


                        }

                        if (count == m_Player->GetSpeed() / 4 || count == m_Player->GetSpeed() / 3 * 2) {
                            size_t FrameCount = m_Player->GetImage()->GetFrameCount();
                            size_t CurrentFrameIndex = m_Player->GetImage()->GetCurrentFrameIndex();
                            m_Player->GetImage()->SetCurrentFrame((CurrentFrameIndex + 1) % FrameCount);
                            FrameCount = m_NPCOak->GetImage()->GetFrameCount();
                            CurrentFrameIndex = m_NPCOak->GetImage()->GetCurrentFrameIndex();
                            m_NPCOak->GetImage()->SetCurrentFrame((CurrentFrameIndex + 1) % FrameCount);
                        }

                        m_Root.Update();
                        auto context = Core::Context::GetInstance();
                        context->Update();
                    }
                    m_MapSystem->SetPosition(
                            {round(m_MapSystem->GetPosition().x), round(m_MapSystem->GetPosition().y)});
                    auto NPC_OakImage = m_NPCOak->GetImage();
                    NPC_OakImage->SetPosition(
                            {round(NPC_OakImage->GetPosition().x), round(NPC_OakImage->GetPosition().y)});
                }
            }

            m_CurrentEvent = EventID::DOOR;
        }
        //endregion
    } else if (m_CurrentEvent == EventID::SHOP) {
        //region
        if (m_ShopUI->GetVisibile()) {
            m_ShopUI->Run();
            if (!m_ShopUI->GetVisibile()) {
                m_CurrentEvent = EventID::NONE;
                m_CurrentState = State::UPDATE;
            }
        } else {
            m_ShopUI->Start();
        }
        //endregion
    } else if (m_CurrentEvent == EventID::NPC) {
        //region
        m_IsWildPokemon = false;
        if (m_TB->GetVisibility()) {
            if (Util::Input::IsKeyDown(Util::Keycode::Z)) {
                m_TB->Next();
                if (!m_TB->GetVisibility()) {
                    if (m_Enemy->GetPokemonBag()->GetPokemons().size() == 0) {
                        m_CurrentState = State::UPDATE;
                        m_CurrentEvent = EventID::NONE;
                    } else {
                        m_CurrentLoading = LoadingID::INIT;
                        m_CurrentState = State::LOADING;
                    }
                }
            }
        } else if (currnetMap == "OakLab") {
            m_TB->Reload();
            m_TB->SetVisible(true);
            if (m_Player->GetPokemonBag()->GetPokemons().size() == 0) {
                m_TB->AddText("喔你來啦!");
                m_TB->AddText("我曾經也是個神奇寶貝訓練家");
                m_TB->AddText("如今我只剩三隻神奇寶貝了");
                m_TB->AddText("旁邊那三個神奇寶貝球挑一隻送你吧!");
            } else if (m_Player->GetItemBag()->GetItemQuantity("寶可夢圖鑑") == 0) {
                m_Player->GetItemBag()->AddItemQuantity("寶可夢圖鑑", 1);
                m_TB->AddText("對了!");
                m_TB->AddText("這個精靈圖鑑給你");
                m_TB->AddText("只要獲得新的神奇寶貝，精靈圖鑑就會更新");
                m_TB->AddText("祝你能收集到所有的神奇寶貝");
            } else {
                m_TB->AddText("努力的訓練你擁有的神奇寶貝並擊敗道館館主吧!");
            }
        } else if (currnetMap == "GYM1") {
            if (TargetPosition.x == 2 && TargetPosition.y == 7) {
                if (m_Player->GetItemBag()->GetItemQuantity(21) > 0) {
                    m_TB->ReadLines(RESOURCE_DIR"/Lines/Brock.txt");
                } else {
                    std::vector<std::shared_ptr<Pokemon>> Pokemons;
                    Pokemons.push_back(std::make_shared<Pokemon>("074"));
                    Pokemons.push_back(std::make_shared<Pokemon>("095"));
                    Pokemons[0]->SetLevel(12);
                    Pokemons[1]->SetLevel(14);
                    Pokemons[0]->SetSkillByID({33, 111});
                    Pokemons[1]->SetSkillByID({33, 103, 117});
                    m_Enemy->GetPokemonBag()->SetPokemons(Pokemons);
                    m_Enemy->SetName("小剛");
                    m_TB->ReadLines(RESOURCE_DIR"/Lines/GYM1.txt");
                }
            } else if (TargetPosition.x == 7 && TargetPosition.y == 6) {
                std::vector<std::shared_ptr<Pokemon>> Pokemons;
                Pokemons.push_back(std::make_shared<Pokemon>("050"));
                Pokemons.push_back(std::make_shared<Pokemon>("027"));
                Pokemons[0]->SetLevel(11);
                Pokemons[1]->SetLevel(11);
                Pokemons[0]->SetSkillByName({"抓"});
                Pokemons[1]->SetSkillByName({"抓", "潑沙"});
                m_Enemy->GetPokemonBag()->SetPokemons(Pokemons);
                m_Enemy->SetName("童子軍");
                m_TB->Reload();
                m_TB->AddText("來決鬥吧!!!");
            } else {
                m_TB->Reload();
                m_TB->AddText("這個道館得的館主是個很強悍的男人!");
            }
            m_TB->SetVisible(true);
        } else if (currnetMap == "GYM2") {
            m_TB->Reload();
            m_TB->SetVisible(true);
            if (TargetPosition.x == 3 && TargetPosition.y == 7) {
                if (m_Player->GetItemBag()->GetItemQuantity(21) == 0) {
                    m_TB->AddText("你連深灰市道館館主都還沒打贏就想挑戰我?");
                } else if (m_Player->GetItemBag()->GetItemQuantity(22) > 0) {
                    m_TB->ReadLines(RESOURCE_DIR"/Lines/Misty.txt");
                } else {
                    std::vector<std::shared_ptr<Pokemon>> Pokemons;
                    Pokemons.push_back(std::make_shared<Pokemon>("120"));
                    Pokemons.push_back(std::make_shared<Pokemon>("121"));
                    Pokemons[0]->SetLevel(18);
                    Pokemons[1]->SetLevel(21);
                    Pokemons[0]->SetSkillByName({"撞擊", "水槍"});
                    Pokemons[1]->SetSkillByName({"撞擊", "水槍", "泡沫光線"});
                    m_Enemy->GetPokemonBag()->SetPokemons(Pokemons);
                    m_Enemy->SetName("小霞");
                    m_TB->ReadLines(RESOURCE_DIR"/Lines/GYM2.txt");
                }
            } else {
                std::vector<std::shared_ptr<Pokemon>> Pokemons;
                Pokemons.push_back(std::make_shared<Pokemon>("118"));
                Pokemons[0]->SetLevel(19);
                Pokemons[0]->SetSkillByName({"搖尾巴", "啄", "超音波"});
                m_Enemy->GetPokemonBag()->SetPokemons(Pokemons);
                m_Enemy->SetName("女童軍");
                m_TB->AddText("我比你想像中還要厲害!來對決吧!!");
            }
        } else if (currnetMap == "PokeCenter") {
            m_TB->Reload();
            m_TB->SetVisible(true);
            if (TargetPosition.x == 8 && TargetPosition.y == 1) {
                m_TB->AddText("我的波波昏厥了，所以我來這裡治療。");
            } else if (TargetPosition.x == 9 && TargetPosition.y == 6) {
                m_TB->AddText("媽媽告訴我不要跟陌生人講話!!!");
            } else if (TargetPosition.x == 7 && TargetPosition.y == 9) {
                if (m_Player->GetItemBag()->GetItemQuantity("秘傳學習器０１") == 0) {
                    m_TB->AddText("年輕人你相信機緣嗎");
                    m_TB->AddText("這個招式我只教你一人");
                    m_TB->AddText("秘傳學習器０１（居合斬）");
                    m_Player->GetItemBag()->AddItemQuantity("秘傳學習器０１", 1);
                } else {
                    m_TB->AddText("你有好好的利用居合斬嗎?");
                }
            } else {
                m_TB->AddText("這裡只有員工可以進入!");
            }
        }
        //endregion
    } else if (m_CurrentEvent == EventID::COMPUTER) {
        //region
        if (m_ComputerUI->GetVisibile()) {
            m_ComputerUI->Run();
            if (!m_ComputerUI->GetVisibile()) {
                m_CurrentEvent = EventID::NONE;
                m_CurrentState = State::UPDATE;
            }
        } else {
            m_ComputerUI->Start();
        }
        //endregion
    } else if (m_CurrentEvent == EventID::HEAL) {
        //region
        if (m_TB->GetVisibility()) {
            if (m_TFBox->GetVisible()) {
                if (m_TFBox->Choose()) {
                    if (m_TFBox->GetTF()) {
                        m_BGM->LoadMedia(RESOURCE_DIR"/BGM/HealPokemon.mp3");
                        m_BGM->Play();
                        for (auto &i: m_Player->GetPokemonBag()->GetPokemons()) {
                            i->SetCurrentHP(i->GetHP());
                            i->SetCurrentSkillPP(i->GetSkillPP());
                        }
                        SDL_Delay(2000);
                        m_BGM->LoadMedia(RESOURCE_DIR"/BGM/PokeCenter.mp3");
                        m_BGM->Play();

                    }
                    m_TFBox->SetVisible(false);
                    m_TB->SetVisible(false);
                    m_CurrentEvent = EventID::NONE;
                    m_CurrentState = State::UPDATE;
                }
            }
        } else {
            m_TB->SetText("是否要恢復背包內所有神奇寶貝的狀態?");
            m_TB->SetVisible(true);
            m_TFBox->SetVisible(true);
        }
        //endregion
    } else if (m_CurrentEvent == EventID::SETTING) {
        //region
        if (m_SettingUI->GetVisible()) {
            m_SettingUI->Run();
            if (m_SettingUI->IsSave()) {
                m_SettingUI->Save(m_Player, m_NPCBromance, m_ComputerUI, m_MapSystem);
            }
            if (!m_SettingUI->GetVisible()) {
                m_CurrentEvent = EventID::NONE;
                m_CurrentState = State::UPDATE;
            }
        } else {
            m_SettingUI->Start();
        }
        //endregion
    } else if (m_CurrentEvent == EventID::NPC_END) {
        //region
        if (m_TB->GetVisibility()) {
            if (Util::Input::IsKeyDown(Util::Keycode::Z)) {
                m_TB->Next();
                if (!m_TB->GetVisibility()) {
                    if (m_Player->GetItemBag()->GetItemQuantity("灰色徽章") > 0 &&
                        m_Player->GetItemBag()->GetItemQuantity("藍色徽章") > 0 &&
                        currnetMap == "GYM2" && TargetPosition.x == 3 && TargetPosition.y == 7) {
                        m_CurrentEvent = EventID::GAME_COMPLETED;
                    } else {
                        m_CurrentState = State::UPDATE;
                        m_CurrentEvent = EventID::NONE;
                    }
                }
            }
        } else if (currnetMap == "GYM1") {
            m_TB->Reload();
            m_TB->SetVisible(true);
            if (TargetPosition.x == 2 && TargetPosition.y == 7) {
                m_TB->AddText("你戰勝了我!!!");
                m_TB->AddText("給你神奇寶貝聯盟認證的灰色徽章");
                m_Player->GetItemBag()->AddItemQuantity("灰色徽章", 1);
            } else {
                m_TB->AddText("可惡，居然輸了!");
                int money = rand() % 100 + 150;
                m_TB->AddText("戰勝了訓練家，獲得了$" + std::to_string(money));
                m_Player->SetMoney(m_Player->GetMoney() + money);
            }
        } else if (currnetMap == "GYM2") {
            m_TB->Reload();
            m_TB->SetVisible(true);
            if (TargetPosition.x == 3 && TargetPosition.y == 7) {
                m_TB->AddText("哇！你太厲害了!");
                m_TB->AddText("好吧!");
                m_TB->AddText("你可以拿到藍色徽章來證明你打敗了我！");
                m_Player->GetItemBag()->AddItemQuantity("藍色徽章", 1);

            } else {
                m_TB->AddText("你比我想像中還要厲害!");
                int money = rand() % 100 + 150;
                m_TB->AddText("戰勝了訓練家，獲得了$" + std::to_string(money));
                m_Player->SetMoney(m_Player->GetMoney() + money);
            }
        }
        //endregion
    } else if (m_CurrentEvent == EventID::ALL_POKEMON_DIE) {
        //region
        int temp = m_MapSystem->GetCurrentArea();
        m_MapSystem->SetMap("MainMap");
        auto Position = m_MapSystem->GetPlayerPosition();
        double distance1 = sqrt(pow(Position.x - 84, 2) + pow(Position.y - 65, 2));
        double distance2 = sqrt(pow(Position.x - 32, 2) + pow(Position.y - 73, 2));
        double distance3 = sqrt(pow(Position.x - 30, 2) + pow(Position.y - 23, 2));
        if (distance1 < distance2 && distance1 < distance3) {
            m_MapSystem->SetPosition({-1224, 2592});
        } else if (distance2 < distance1 && distance2 < distance3) {
            m_MapSystem->SetPosition({-1800, -1152});
        } else {
            m_MapSystem->SetPosition({1800, -1296});
        }
        m_Player->SetCurrentImagePath(1);
        for (auto &i: m_Player->GetPokemonBag()->GetPokemons()) {
            i->SetCurrentHP(i->GetHP());
            i->SetCurrentSkillPP(i->GetSkillPP());
        }
        m_CurrentEvent = EventID::NONE;
        m_CurrentState = State::UPDATE;
        //endregion
    } else if (m_CurrentEvent == EventID::GAME_COMPLETED) {
        //region
        if (m_TB->GetVisibility()) {
            if (Util::Input::IsKeyDown(Util::Keycode::Z)) {
                m_TB->Next();
                if (!m_TB->GetVisibility()) {
                    m_WhiteBG->SetVisible(false);
                    m_WhiteBG->SetImage(RESOURCE_DIR"/Background/WhiteBG.png");
                    m_Player->GetImage()->SetVisible(true);
                    m_CurrentState = State::UPDATE;
                    m_CurrentEvent = EventID::NONE;
                }
            }
        } else {
            m_WhiteBG->SetVisible(true);
            m_WhiteBG->SetImage(RESOURCE_DIR"/Background/Congratulations.png");
            m_SFX->Play("victory");
            m_TB->Reload();
            m_TB->ReadLines(RESOURCE_DIR"/Lines/GameCompleted.txt");
            m_TB->SetVisible(true);
            m_Player->GetImage()->SetVisible(false);
        }
        //endregion
    } else if (m_CurrentEvent == EventID::NONE) {
        LOG_WARN("CurrentEvent is NONE");
    }


    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }

    m_Root.Update();
}