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
                if (eventID != 0) {
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
        if (currnetMap == "MainMap") {
            if (PlayerPosition.x == 83 && PlayerPosition.y == 65) {
                m_MapSystem->SetMap("PlayerHouse1F");
                m_MapSystem->SetPosition({144, 216});
            } else {
                LOG_DEBUG("({},{})'s door has not implement", PlayerPosition.x, PlayerPosition.y);
            }
        } else if (currnetMap == "PlayerHouse1F") {
            if (PlayerPosition.x == 8 && (PlayerPosition.y == 3 || PlayerPosition.y == 4)) {
                m_MapSystem->SetMap("MainMap");
                m_MapSystem->SetPosition({-1224, 2592});
            } else {
                LOG_DEBUG("({},{})'s door has not implement", PlayerPosition.x, PlayerPosition.y);
            }
        } else {
            LOG_DEBUG("({},{})'s door has not implement", PlayerPosition.x, PlayerPosition.y);
        }
        m_CurrentState = State::UPDATE;
        m_CurrentEvent = EventID::NONE;
        //endregion
    } else if (m_CurrentEvent == EventID::GRASS) {
        //region
        if (rand() % 100 < 25) {
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
        } else {
            m_CurrentState = State::UPDATE;
        }
        m_CurrentEvent = EventID::NONE;
        //endregion
    } else if (m_CurrentEvent == EventID::BILLBOARD) {

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

    } else if (m_CurrentEvent == EventID::NONE) {

    }


    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }

    m_Root.Update();
}