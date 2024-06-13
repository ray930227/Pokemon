#include "App.hpp"

void App::Event() {
    auto PlayerPosition = m_MapSystem->GetPlayerPosition();
    auto currnetMap = m_MapSystem->GetCurrnetMap();
    glm::vec2 TargetPosition = m_MapSystem->GetPlayerPosition();
    if (currentDirection == "UP") TargetPosition.x--;
    else if (currentDirection == "DOWN") TargetPosition.x++;
    else if (currentDirection == "LEFT") TargetPosition.y--;
    else TargetPosition.y++;

    if (m_CurrentEvent == EventID::MOVE) {
        //region
        if (DisplacementCount != 0) {
            glm::vec2 PlayerPosition = m_MapSystem->GetPlayerPosition();

            bool up = currentDirection == "UP" &&
                      m_MapSystem->GetBlocks()[PlayerPosition.x - 1][PlayerPosition.y]->GetTraversable();
            bool down = currentDirection == "DOWN" &&
                        m_MapSystem->GetBlocks()[PlayerPosition.x + 1][PlayerPosition.y]->GetTraversable();
            bool left = currentDirection == "LEFT" &&
                        m_MapSystem->GetBlocks()[PlayerPosition.x][PlayerPosition.y - 1]->GetTraversable();
            bool right = currentDirection == "RIGHT" &&
                         m_MapSystem->GetBlocks()[PlayerPosition.x][PlayerPosition.y + 1]->GetTraversable();
            bool canMove = up || down || left || right;

            if (!((DisplacementCount == Player->GetSpeed() && canMove) ||
                  DisplacementCount != Player->GetSpeed())) {
                if (currentDirection == "DOWN" &&
                    m_MapSystem->GetBlocks()[PlayerPosition.x + 1][PlayerPosition.y]->GetEventID() ==
                    (int) EventID::JUMP) {
                    m_CurrentEvent = EventID::JUMP;
                    DisplacementCount *= 2;
                } else if (currentDirection == "DOWN" &&
                           m_MapSystem->GetBlocks()[PlayerPosition.x + 1][PlayerPosition.y]->GetEventID() ==
                           (int) EventID::DOOR) {
                    m_CurrentEvent = EventID::DOOR;
                    Displacement = {0, 0};
                } else {
                    Displacement = {0, 0};
                }
            }
            m_MapSystem->Move(Displacement);
            if (DisplacementCount == Player->GetSpeed() / 4 || DisplacementCount == Player->GetSpeed() / 3 * 2) {
                size_t FrameCount = Player->GetImage()->GetFrameCount();
                size_t CurrentFrameIndex = Player->GetImage()->GetCurrentFrameIndex();
                Player->GetImage()->SetCurrentFrame((CurrentFrameIndex + 1) % FrameCount);
            }

            DisplacementCount--;
            if (DisplacementCount == 0) {
                m_MapSystem->SetPosition({round(m_MapSystem->GetPosition().x), round(m_MapSystem->GetPosition().y)});
                glm::vec2 playerPosition = m_MapSystem->GetPlayerPosition();
                std::shared_ptr<Block> block = m_MapSystem->GetBlocks()[playerPosition.x][playerPosition.y];
                if (block->GetEventID() != 0 && (Displacement.x != 0 || Displacement.y != 0)) {
                    if (block->GetEventID() == (int) EventID::GRASS && Player->GetPokemonBag()->size() == 0) {
                        m_TB->ReadLines(RESOURCE_DIR"/Lines/FirstInGrass.txt");
                        m_TB->SetVisible(true);
                        m_CurrentEvent = EventID::CHOOSE_POKEMON;
                    } else {
                        m_CurrentEvent = (EventID) block->GetEventID();
                    }
                } else if (currentDirection == "UP" && Util::Input::IsKeyPressed(Util::Keycode::UP)) {
                    DisplacementCount = Player->GetSpeed();
                } else if (currentDirection == "DOWN" && Util::Input::IsKeyPressed(Util::Keycode::DOWN)) {
                    DisplacementCount = Player->GetSpeed();
                } else if (currentDirection == "LEFT" && Util::Input::IsKeyPressed(Util::Keycode::LEFT)) {
                    DisplacementCount = Player->GetSpeed();
                } else if (currentDirection == "RIGHT" && Util::Input::IsKeyPressed(Util::Keycode::RIGHT)) {
                    DisplacementCount = Player->GetSpeed();
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
                } else {
                    LOG_DEBUG("({},{})'s door has not implement", PlayerPosition.x, PlayerPosition.y);
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
            } else {
                LOG_DEBUG("({},{})'s door has not implement", PlayerPosition.x, PlayerPosition.y);
            }
            m_WhiteBG->SetVisible(false);
            m_WhiteBG->SetZIndex(0);
            if (m_MapSystem->GetCurrnetMap() == "MainMap") {
                Displacement = {0, 72.0 / Player->GetSpeed()};
                DisplacementCount = Player->GetSpeed();
                currentDirection = "DOWN";
                Player->SetCurrentImagePath(1);
                m_CurrentEvent = EventID::MOVE;
            } else {
                m_CurrentState = State::UPDATE;
                m_CurrentEvent = EventID::NONE;
            }
        }
        //endregion
    } else if (m_CurrentEvent == EventID::GRASS) {
        //region
        if (encounterable && rand() % 100 < 20) {
            isWildPokemon = true;
            std::vector<int> tempID = {13, 16, 19, 21, 23, 25, 26, 27, 29, 31, 32, 34, 35, 36, 37, 38, 39, 40, 41, 43,
                                       45, 46, 48, 50, 52, 54, 56, 58, 59, 60, 62, 63, 65, 66, 68, 69, 71, 72, 74, 76,
                                       77, 79, 81, 83, 84, 86, 88, 90, 92, 95, 96, 98, 100, 102, 103, 104, 106, 107,
                                       108, 109, 111, 113, 114, 115, 116, 118, 120, 121, 122, 124, 125, 126, 127,
                                       128, 129, 131, 132};
            int r = rand() % tempID.size();
            std::stringstream ToString;
            ToString << std::setw(3) << std::setfill('0') << tempID[r];
            std::string StringID = ToString.str();
            auto temp = std::make_shared<Pokemon>(StringID);
            int average = 0;
            for (auto &i: Player->GetPokemonBag()->GetPokemons())
                average += i->GetLV();
            temp->SetLevel(average / Player->GetPokemonBag()->GetPokemons().size()-2+rand()%5);
            Enemy->GetPokemonBag()->SetPokemons({temp});
            m_CurrentLoading = LoadingID::INIT;
            m_CurrentState = State::LOADING;
            m_CurrentEvent = EventID::NONE;

        } else {
            m_CurrentEvent = EventID::MOVE;
            m_CurrentState = State::EVENT;
            if (currentDirection == "UP" && Util::Input::IsKeyPressed(Util::Keycode::UP)) {
                DisplacementCount = Player->GetSpeed();
            } else if (currentDirection == "DOWN" && Util::Input::IsKeyPressed(Util::Keycode::DOWN)) {
                DisplacementCount = Player->GetSpeed();
            } else if (currentDirection == "LEFT" && Util::Input::IsKeyPressed(Util::Keycode::LEFT)) {
                DisplacementCount = Player->GetSpeed();
            } else if (currentDirection == "RIGHT" && Util::Input::IsKeyPressed(Util::Keycode::RIGHT)) {
                DisplacementCount = Player->GetSpeed();
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
                m_TB->SetText(Player->GetName() + "的家");
            } else if (TargetPosition.x == 83 && TargetPosition.y == 71) {
                m_TB->SetText(NPC_Bromance->GetName() + "的家");
            } else if (TargetPosition.x == 87 && TargetPosition.y == 67) {
                m_TB->SetText("真新鎮");
            } else if (TargetPosition.x == 91 && TargetPosition.y == 73) {
                m_TB->SetText("大木博士的實驗室");
            } else if (TargetPosition.x == 13 && TargetPosition.y == 77) {
                m_TB->SetText("深灰市神奇寶貝道館館主：小剛\n如岩石般强大的男人。");
            } else if(TargetPosition.x == 69 && TargetPosition.y == 69) {
                m_TB->SetText("↑↑↑\n深灰市");
            } else if(TargetPosition.x == 35 && TargetPosition.y == 71) {
                m_TB->SetText("這裡是深灰市。\n深灰即是堅若磐石的灰黑之色。");
            } else if(TargetPosition.x == 23 && TargetPosition.y == 67) {
                m_TB->AddText("戰鬥招式的使用次數受招式點數的限制，它的簡稱ＰＰ。");
                m_TB->AddText("想要補充ＰＰ的話，那就到寶可夢中心，讓你的寶可夢好好休息吧！");
            } else if(TargetPosition.x == 7 && TargetPosition.y == 69) {
                m_TB->AddText("前方不可通行!!!");
            } else if(TargetPosition.x == 23 && TargetPosition.y == 43) {
                m_TB->SetText("歡迎來到華藍市");
            } else if(TargetPosition.x == 33 && TargetPosition.y == 29) {
                m_TB->SetText("這裡是華藍市。\n華藍即是神秘莫測的水藍之色。");
            } else if(TargetPosition.x == 13 && TargetPosition.y == 25) {
                m_TB->AddText("在寶可夢進化過程中，連按X鍵可以取消進化。");
            } else if(TargetPosition.x == 21 && TargetPosition.y == 21) {
                m_TB->SetText("華藍市神奇寶貝道館館主：小霞\n俏皮的美人魚。");
            } else if(TargetPosition.x == 27 && TargetPosition.y == 35) {
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
            if(!m_TB->GetVisibility()) {
                m_CurrentEvent = EventID::NONE;
                m_CurrentState = State::UPDATE;
            }
        }
        //endregion
    } else if (m_CurrentEvent == EventID::JUMP) {
        //region
        if (DisplacementCount != 0) {
            m_MapSystem->Move(Displacement);
            if (DisplacementCount > Player->GetSpeed()) {
                Player->GetImage()->Move(Displacement);
            } else {
                Player->GetImage()->Move({0, Displacement.y * -1});
            }
            DisplacementCount--;
        } else {
            m_MapSystem->SetPosition({round(m_MapSystem->GetPosition().x), round(m_MapSystem->GetPosition().y)});
            Player->GetImage()->SetPosition({36, -36});
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
            for (auto &i: Player->GetPokemonBag()->GetPokemons()) {
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
                            Player->GetPokemonBag()->addPomekon(std::make_shared<Pokemon>("004"));
                            Lines.push_back(Player->GetName() + "選擇了小火龍");
                        } else if (TargetPosition.x == 4 && TargetPosition.y == 9) {
                            Player->GetPokemonBag()->addPomekon(std::make_shared<Pokemon>("007"));
                            Lines.push_back(Player->GetName() + "選擇了傑尼龜");
                        } else if (TargetPosition.x == 4 && TargetPosition.y == 10) {
                            Player->GetPokemonBag()->addPomekon(std::make_shared<Pokemon>("001"));
                            Lines.push_back(Player->GetName() + "選擇了妙蛙種子");
                        }
                        m_Root.RemoveChild(m_MapSystem->GetBlocks()[TargetPosition.x][TargetPosition.y]);
                        m_TB->ReadLines(Lines);
                        auto poke=Player->GetPokemonBag()->GetPokemons()[0];
                        auto Ability=poke->GetAbility();
                        Ability["IV"]=31;
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
                if (Player->GetPokemonBag()->size() == 0) {
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
                    Player->SetCurrentImagePath(1);
                    NPC_Oak->SetCurrentImagePath(0);
                    NPC_Oak->GetImage()->SetVisible(true);
                    NPC_Oak->GetImage()->SetPosition({36, -180});
                    for (int i = 0; i < Player->GetSpeed(); i++) {
                        NPC_Oak->GetImage()->Move({0, 72.0 / Player->GetSpeed()});
                        if (i == Player->GetSpeed() / 4 || i == Player->GetSpeed() / 3 * 2) {
                            size_t FrameCount = NPC_Oak->GetImage()->GetFrameCount();
                            size_t CurrentFrameIndex = NPC_Oak->GetImage()->GetCurrentFrameIndex();
                            NPC_Oak->GetImage()->SetCurrentFrame((CurrentFrameIndex + 1) % FrameCount);
                        }

                        m_Root.Update();
                        auto context = Core::Context::GetInstance();
                        context->Update();
                    }
                    NPC_Oak->GetImage()->SetPosition(
                            {round(NPC_Oak->GetImage()->GetPosition().x), round(NPC_Oak->GetImage()->GetPosition().y)});
                }

            }
            if (m_TB->GetText().find("<Player>") < m_TB->GetText().size()) {
                std::string tempStr = m_TB->GetText();
                tempStr.replace(tempStr.begin() + tempStr.find("<Player>"),
                                tempStr.begin() + tempStr.find("<Player>") + 8,
                                Player->GetName());
                m_TB->SetText(tempStr);
            }
            if (m_TB->GetText().find("<NPC_Bromance>") < m_TB->GetText().size()) {
                std::string tempStr = m_TB->GetText();
                tempStr.replace(tempStr.begin() + tempStr.find("<NPC_Bromance>"),
                                tempStr.begin() + tempStr.find("<NPC_Bromance>") + 14,
                                NPC_Bromance->GetName());
                m_TB->SetText(tempStr);
            }
        } else {
            std::vector<std::pair<int, glm::vec2>> temp;
            temp.push_back({1, {0, 72.0 / Player->GetSpeed()}});
            temp.push_back({m_MapSystem->GetPosition().x == -1584 ? 1 : 2, {72.0 / Player->GetSpeed(), 0}});
            temp.push_back({10, {0, 72.0 / Player->GetSpeed()}});
            temp.push_back({3, {-72.0 / Player->GetSpeed(), 0}});
            temp.push_back({1, {0, -72.0 / Player->GetSpeed()}});

            for (size_t i = 0; i < temp.size(); i++) {
                if (temp[i].second.y < 0) Player->SetCurrentImagePath(0);
                else if (temp[i].second.y > 0) Player->SetCurrentImagePath(1);
                else if (temp[i].second.x > 0) Player->SetCurrentImagePath(2);
                else Player->SetCurrentImagePath(3);

                for (int times = 0; times < temp[i].first; times++) {
//                    NPC_Oak->SetCurrentImagePath(1);
                    if (i == temp.size() - 1)
                        NPC_Oak->GetImage()->SetVisible(false);
                    for (int count = Player->GetSpeed(); count > 0; count--) {
                        m_MapSystem->Move(temp[i].second);
                        if (i + 1 < temp.size() && times == temp[i].first - 1) {
                            if (temp[i].second.x == 0)
                                NPC_Oak->GetImage()->Move({0 - temp[i + 1].second.x, temp[i].second.y});
                            else
                                NPC_Oak->GetImage()->Move({temp[i].second.x, 0 - temp[i + 1].second.y});

                            if (temp[i + 1].second.y < 0)
                                NPC_Oak->SetCurrentImagePath(0);
                            else if (temp[i + 1].second.y > 0)
                                NPC_Oak->SetCurrentImagePath(1);
                            else if (temp[i + 1].second.x > 0)
                                NPC_Oak->SetCurrentImagePath(2);
                            else
                                NPC_Oak->SetCurrentImagePath(3);


                        }

                        if (count == Player->GetSpeed() / 4 || count == Player->GetSpeed() / 3 * 2) {
                            size_t FrameCount = Player->GetImage()->GetFrameCount();
                            size_t CurrentFrameIndex = Player->GetImage()->GetCurrentFrameIndex();
                            Player->GetImage()->SetCurrentFrame((CurrentFrameIndex + 1) % FrameCount);
                            FrameCount = NPC_Oak->GetImage()->GetFrameCount();
                            CurrentFrameIndex = NPC_Oak->GetImage()->GetCurrentFrameIndex();
                            NPC_Oak->GetImage()->SetCurrentFrame((CurrentFrameIndex + 1) % FrameCount);
                        }

                        m_Root.Update();
                        auto context = Core::Context::GetInstance();
                        context->Update();
                    }
                    m_MapSystem->SetPosition(
                            {round(m_MapSystem->GetPosition().x), round(m_MapSystem->GetPosition().y)});
                    auto NPC_OakImage = NPC_Oak->GetImage();
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
        isWildPokemon= false;
        if (m_TB->GetVisibility()) {
            if (Util::Input::IsKeyDown(Util::Keycode::Z)) {
                m_TB->Next();
                if (!m_TB->GetVisibility()) {
                    if (Enemy->GetPokemonBag()->GetPokemons().size()==0) {
                        m_CurrentState = State::UPDATE;
                        m_CurrentEvent = EventID::NONE;
                    } else {
                        m_CurrentLoading = LoadingID::INIT;
                        m_CurrentState = State::LOADING;
                    }
                }
            }
        } else if (currnetMap == "OakLab"){
            m_TB->Reload();
            m_TB->SetVisible(true);
            if(Player->GetPokemonBag()->GetPokemons().size()==0){
                m_TB->AddText("喔你來啦!");
                m_TB->AddText("我曾經也是個神奇寶貝訓練家");
                m_TB->AddText("如今我只剩三隻神奇寶貝了");
                m_TB->AddText("旁邊那三個神奇寶貝球挑一隻送你吧!");
            } else if(Player->GetItemBag()->GetItemQuantity("寶可夢圖鑑")==0){
                Player->GetItemBag()->AddItemQuantity("寶可夢圖鑑",1);
                m_TB->AddText("對了!");
                m_TB->AddText("這個精靈圖鑑給你");
                m_TB->AddText("只要獲得新的神奇寶貝，精靈圖鑑就會更新");
                m_TB->AddText("祝你能收集到所有的神奇寶貝");
            } else{
                m_TB->AddText("努力的訓練你擁有的神奇寶貝並擊敗道館館主吧!");
            }
        } else if (currnetMap == "GYM1") {
            if (TargetPosition.x == 2 && TargetPosition.y == 7) {
                if(Player->GetItemBag()->GetItemQuantity(21) > 0) {
                    m_TB->ReadLines(RESOURCE_DIR"/Lines/Brock.txt");
                } else {
                    std::vector<std::shared_ptr<Pokemon>> Pokemons;
                    Pokemons.push_back(std::make_shared<Pokemon>("074"));
                    Pokemons.push_back(std::make_shared<Pokemon>("095"));
                    Pokemons[0]->SetLevel(12);
                    Pokemons[1]->SetLevel(14);
                    Pokemons[0]->SetSkillByID({33, 111});
                    Pokemons[1]->SetSkillByID({33, 103, 117});
                    Enemy->GetPokemonBag()->SetPokemons(Pokemons);
                    Enemy->SetName("小剛");
                    m_TB->ReadLines(RESOURCE_DIR"/Lines/GYM1.txt");
                }
            } else {
                LOG_DEBUG("{}:({},{}) NPC has not implement", currnetMap, TargetPosition.x, TargetPosition.y);
                m_TB->Reload();
                m_TB->SetText("NPC has not implement");
            }
            m_TB->SetVisible(true);
        } else {
            LOG_DEBUG("{}:({},{}) NPC has not implement", currnetMap, TargetPosition.x, TargetPosition.y);
            m_TB->Reload();
            m_TB->SetText("NPC has not implement");
            m_TB->SetVisible(true);
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
                        for (auto &i: Player->GetPokemonBag()->GetPokemons()) {
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
            if(m_SettingUI->IsSave()){
                m_SettingUI->Save(Player,NPC_Bromance,m_ComputerUI,m_MapSystem);
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
                    m_CurrentState = State::UPDATE;
                    m_CurrentEvent = EventID::NONE;
                }
            }
        } else if (currnetMap == "GYM1") {
            if (TargetPosition.x == 2 && TargetPosition.y == 7) {
                m_TB->Reload();
                m_TB->AddText("你戰勝了我!!!");
                m_TB->AddText("給你神奇寶貝聯盟認證的灰色徽章");
                m_TB->AddText("還有這個，給你");
                m_TB->AddText("獲得了招式學習器３４（忍耐）");
                m_TB->AddText("使用忍耐後，在２回合內忍受攻擊");
                m_TB->AddText("受到的傷害會２倍返還給對手。");
                m_TB->AddText("招式學習器只能給一個神奇寶貝學");
                m_TB->AddText("所以要冷靜選擇，做出最好的選擇");
                m_TB->SetVisible(true);
                Player->GetItemBag()->AddItemQuantity("招式學習器３４（忍耐）", 1);
                Player->GetItemBag()->AddItemQuantity("灰色徽章", 1);
            } else {
                LOG_DEBUG("{}:({},{}) NPC has not implement", currnetMap, TargetPosition.x, TargetPosition.y);
                Enemy = nullptr;
                m_TB->Reload();
                m_TB->SetText("NPC has not implement");
            }
            m_TB->SetVisible(true);
        } else {
            LOG_DEBUG("{}:({},{}) NPC has not implement", currnetMap, TargetPosition.x, TargetPosition.y);
            m_TB->Reload();
            m_TB->SetText("NPC has not implement");
            m_TB->SetVisible(true);
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
        Player->SetCurrentImagePath(1);
        for (auto &i: Player->GetPokemonBag()->GetPokemons()) {
            i->SetCurrentHP(i->GetHP());
            i->SetCurrentSkillPP(i->GetSkillPP());
        }
        m_CurrentEvent = EventID::NONE;
        m_CurrentState = State::UPDATE;
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