#include "App.hpp"

void App::Event() {

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
                int eventID = m_MapSystem->GetBlocks()[m_MapSystem->GetPlayerPosition().x][m_MapSystem->GetPlayerPosition().y]->GetEventID();
                if (eventID != 0 && (Displacement.x != 0 || Displacement.y != 0)) {
                    m_CurrentEvent = (EventID) eventID;
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
        auto PlayerPosition = m_MapSystem->GetPlayerPosition();
        auto currnetMap = m_MapSystem->GetCurrnetMap();

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
            } else {
                LOG_DEBUG("({},{})'s door has not implement", PlayerPosition.x, PlayerPosition.y);
            }
            m_WhiteBG->SetVisible(false);
            m_WhiteBG->SetZIndex(0);
            m_CurrentState = State::UPDATE;
            m_CurrentEvent = EventID::NONE;
        }
        //endregion
    } else if (m_CurrentEvent == EventID::GRASS) {
        //region
        if (encounterable && rand() % 100 < 20) {
            m_BGM->LoadMedia(RESOURCE_DIR"/BGM/Battle.mp3");
            m_BGM->Play();
            m_TB->ReadLines(RESOURCE_DIR"/Lines/FightLoading.txt");
            m_FightLoad1_1->SetVisible(true);
            m_FightLoad1_2->SetVisible(true);
            m_tempImage->SetImage(RESOURCE_DIR"/Fight/Player.png");
            m_tempImage->SetPosition({620, -10});
            m_EnemyPokemon->SetPosition({-620, 230});
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
            glm::vec2 BillboardPosition = m_MapSystem->GetPlayerPosition();
            if (currentDirection == "UP") BillboardPosition.x--;
            else if (currentDirection == "DOWN") BillboardPosition.x++;
            else if (currentDirection == "LEFT") BillboardPosition.y--;
            else BillboardPosition.y++;

            if (BillboardPosition.x == 83 && BillboardPosition.y == 63) {
                m_TB->SetText(Player->GetName() + "的家");
            } else if (BillboardPosition.x == 83 && BillboardPosition.y == 71) {
                m_TB->SetText(NPC_Bromance->GetName() + "的家");
            } else if (BillboardPosition.x == 87 && BillboardPosition.y == 67) {
                m_TB->SetText("真新鎮");
            } else if (BillboardPosition.x == 91 && BillboardPosition.y == 73) {
                m_TB->SetText("大木博士的實驗室");
            } else {
                m_TB->SetText("(" + std::to_string((int) BillboardPosition.x) + "," +
                              std::to_string((int) BillboardPosition.y) +
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

    } else if (m_CurrentEvent == EventID::BALL) {

    } else if (m_CurrentEvent == EventID::NONE) {
        LOG_WARN("CurrentEvent is NONE");
    }


    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }

    m_Root.Update();
}