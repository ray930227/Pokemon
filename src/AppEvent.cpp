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
            Enemy = std::make_shared<Character>();
            std::vector<int> tempID = {13, 16, 19, 21, 23, 25, 26, 27, 29, 31, 32, 34, 35, 36, 37, 38, 39, 40, 41, 43,
                                       45, 46, 48, 50, 52, 54, 56, 58, 59, 60, 62, 63, 65, 66, 68, 69, 71, 72, 74, 76,
                                       77, 79, 81, 83, 84, 86, 88, 90, 91, 92, 94, 95, 96, 98, 100, 102, 103, 104, 106,
                                       107, 108, 109, 111, 113, 114, 115, 116, 118, 120, 121, 122, 124, 125, 126, 127,
                                       128, 129, 131, 132};
            int r = rand() % tempID.size();
            std::stringstream ToString;
            ToString << std::setw(3) << std::setfill('0') << tempID[r];
            std::string StringID = ToString.str();
            auto temp = std::make_shared<Pokemon>(StringID);
            int average = 0;
            for (auto &i: Player->GetPokemonBag()->GetPokemons())
                average += i->GetLV();
            temp->SetLevel(average / Player->GetPokemonBag()->GetPokemons().size());
            Enemy->GetPokemonBag()->addPomekon(temp);
            m_CurrentLoading = LoadingID::INTO;
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
            } else {
                m_TB->SetText("(" + std::to_string((int) TargetPosition.x) + "," +
                              std::to_string((int) TargetPosition.y) +
                              ")'s billboard has not implement");
            }
            m_TB->SetVisible(true);
        }

        if (Util::Input::IsKeyDown(Util::Keycode::Z)) {
            m_TB->SetVisible(false);
            m_CurrentEvent = EventID::NONE;
            m_CurrentState = State::UPDATE;
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
            if (m_TFBox->GetVisibility()) {
                if (m_TFBox->Choose()) {
                    m_TFBox->SetVisibility(false);
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
                        m_TFBox->SetVisibility(true);
                        break;
                    }
                }
                if (m_TFBox->GetVisibility()) break;
            }
        }
        //endregion
    } else if (m_CurrentEvent == EventID::BALL) {
        //region
        if (m_TFBox->GetVisibility()) {
            if (m_TFBox->Choose()) {
                m_TFBox->SetVisibility(false);
                m_TB->SetVisible(false);
                if (m_TFBox->GetTF()) {
                    if (currnetMap == "OakLab") {
                        std::vector<std::string> Lines;
                        m_TB->SetVisible(true);
                        if (TargetPosition.x == 4 && TargetPosition.y == 8) {
                            Player->GetPokemonBag()->addPomekon(std::make_shared<Pokemon>("004"));
                            NPC_Bromance->GetPokemonBag()->addPomekon(std::make_shared<Pokemon>("007"));
                            Enemy = NPC_Bromance;
                            Lines.push_back(Player->GetName() + "選擇了小火龍");
                            Lines.push_back(NPC_Bromance->GetName() + ":那我要傑尼龜");
                        } else if (TargetPosition.x == 4 && TargetPosition.y == 9) {
                            Player->GetPokemonBag()->addPomekon(std::make_shared<Pokemon>("007"));
                            NPC_Bromance->GetPokemonBag()->addPomekon(std::make_shared<Pokemon>("001"));
                            Enemy = NPC_Bromance;
                            Lines.push_back(Player->GetName() + "選擇了傑尼龜");
                            Lines.push_back(NPC_Bromance->GetName() + ":那我要妙蛙種子");
                        } else if (TargetPosition.x == 4 && TargetPosition.y == 10) {
                            Player->GetPokemonBag()->addPomekon(std::make_shared<Pokemon>("001"));
                            NPC_Bromance->GetPokemonBag()->addPomekon(std::make_shared<Pokemon>("004"));
                            Enemy = NPC_Bromance;
                            Lines.push_back(Player->GetName() + "選擇了妙蛙種子");
                            Lines.push_back(NPC_Bromance->GetName() + ":那我要小火龍");
                        }
                        m_Root.RemoveChild(m_MapSystem->GetBlocks()[TargetPosition.x][TargetPosition.y]);
                        m_TB->ReadLines(Lines);
                        while (m_TB->GetVisibility()) {
                            if (Util::Input::IsKeyDown(Util::Keycode::Z)) {
                                m_TB->Next();
                            }
                            m_Root.Update();
                            auto context = Core::Context::GetInstance();
                            context->Update();
                        }
                        m_Root.RemoveChild(
                                m_MapSystem->GetBlocks()[TargetPosition.x][((int) TargetPosition.y - 8 + 1) % 3 + 8]);
                    } else {

                    }
                }
                m_CurrentEvent = EventID::NONE;
                m_CurrentState = State::UPDATE;
            }
        } else {
            if (currnetMap == "OakLab") {
                if (Player->GetPokemonBag()->size() == 0) {
                    m_TFBox->SetVisibility(true);
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
//                    NPC_Oak->SetCurrentImagePath(0);
                    NPC_Oak->GetImage()->SetDrawable(
                            std::make_shared<Util::Image>(RESOURCE_DIR"/Charactor/OakBack.png"));
                    NPC_Oak->GetImage()->SetVisible(true);
                    NPC_Oak->GetImage()->SetPosition({36, -180});
                    for (int i = 0; i < Player->GetSpeed(); i++) {
                        NPC_Oak->GetImage()->Move({0, 72.0 / Player->GetSpeed()});
//                        if (i == Player->GetSpeed() / 4 || i == Player->GetSpeed() / 3 * 2) {
//                            size_t FrameCount = NPC_Oak->GetImage()->GetFrameCount();
//                            size_t CurrentFrameIndex = NPC_Oak->GetImage()->GetCurrentFrameIndex();
//                            NPC_Oak->GetImage()->SetCurrentFrame((CurrentFrameIndex + 1) % FrameCount);
//                        }

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
                                NPC_Oak->GetImage()->SetDrawable(
                                        std::make_shared<Util::Image>(RESOURCE_DIR"/Charactor/OakBack.png"));
                            else if (temp[i + 1].second.y > 0)
                                NPC_Oak->GetImage()->SetDrawable(
                                        std::make_shared<Util::Image>(RESOURCE_DIR"/Charactor/OakFront.png"));
                            else if (temp[i + 1].second.x > 0)
                                NPC_Oak->GetImage()->SetDrawable(
                                        std::make_shared<Util::Image>(RESOURCE_DIR"/Charactor/OakLeft.png"));
                            else
                                NPC_Oak->GetImage()->SetDrawable(
                                        std::make_shared<Util::Image>(RESOURCE_DIR"/Charactor/OakRight.png"));


                        }
                        if (count == Player->GetSpeed() / 4 || count == Player->GetSpeed() / 3 * 2) {
                            size_t FrameCount = Player->GetImage()->GetFrameCount();
                            size_t CurrentFrameIndex = Player->GetImage()->GetCurrentFrameIndex();
                            Player->GetImage()->SetCurrentFrame((CurrentFrameIndex + 1) % FrameCount);
//                            NPC_Oak->GetImage()->SetCurrentFrame((CurrentFrameIndex + 1) % FrameCount);
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
                LOG_DEBUG("({},{})", m_MapSystem->GetPosition().x, m_MapSystem->GetPosition().y);


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
        if (m_TB->GetVisibility()) {
            if (Util::Input::IsKeyDown(Util::Keycode::Z)) {
                m_TB->Next();
                if (!m_TB->GetVisibility()) {
                    if (Enemy == nullptr) {
                        m_CurrentState = State::UPDATE;
                        m_CurrentEvent = EventID::NONE;
                    } else {
                        m_CurrentLoading = LoadingID::INTO;
                        m_CurrentState = State::LOADING;
                    }

                }
            }
        } else if (currnetMap == "GYM1") {
            if (TargetPosition.x == 2 && TargetPosition.y == 7) {
                Enemy = std::make_shared<Character>();
                std::vector<std::shared_ptr<Pokemon>> Pokemons;
                Pokemons.push_back(std::make_shared<Pokemon>("074"));
                Pokemons.push_back(std::make_shared<Pokemon>("095"));
                Pokemons[0]->SetLevel(12);
                Pokemons[1]->SetLevel(14);
                Pokemons[0]->SetSkillByID({33, 111});
                Pokemons[1]->SetSkillByID({33, 103, 117});
                Enemy->GetPokemonBag()->SetPokemons(Pokemons);
                m_TB->ReadLines(RESOURCE_DIR"/Lines/GYM1.txt");
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
    } else if (m_CurrentEvent == EventID::COMPUTER) {

    } else if (m_CurrentEvent == EventID::HEAL) {
        //region
        m_SFX->Play("HealPokemon");
        for (auto &i: Player->GetPokemonBag()->GetPokemons()) {
            i->SetCurrentHP(i->GetHP());
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