#include "App.hpp"

void App::Event() {

    switch (m_CurrentEvent) {
        case EventID::MOVE:
            if (DisplacementCount != 0) {
                glm::vec2 PlayerPosition = m_Map->GetPlayerPosition();

                bool up = currentDirection=="UP" &&
                          m_Map->GetBlocks()[PlayerPosition.x - 1][PlayerPosition.y]->GetTraversable();
                bool down = currentDirection=="DOWN" &&
                            m_Map->GetBlocks()[PlayerPosition.x + 1][PlayerPosition.y]->GetTraversable();
                bool left = currentDirection=="LEFT" &&
                            m_Map->GetBlocks()[PlayerPosition.x][PlayerPosition.y - 1]->GetTraversable();
                bool right = currentDirection=="RIGHT" &&
                             m_Map->GetBlocks()[PlayerPosition.x][PlayerPosition.y + 1]->GetTraversable();
                bool canMove = up || down || left || right;

                if (!((DisplacementCount == Player->GetSpeed() && canMove) ||
                      DisplacementCount != Player->GetSpeed())) {
                    if (currentDirection == "DOWN" &&
                        m_Map->GetBlocks()[PlayerPosition.x +1][PlayerPosition.y]->GetEventID()==(int)EventID::JUMP) {
                        m_CurrentEvent = EventID::JUMP;
                        DisplacementCount*=2;
                    } else{
                        Displacement = {0, 0};
                    }
                }
                m_Map->Move(Displacement);
                if (DisplacementCount == Player->GetSpeed() / 4 || DisplacementCount == Player->GetSpeed() / 3 * 2) {
                    size_t FrameCount = Player->GetImage()->GetFrameCount();
                    size_t CurrentFrameIndex = Player->GetImage()->GetCurrentFrameIndex();
                    Player->GetImage()->SetCurrentFrame((CurrentFrameIndex + 1) % FrameCount);
                }

                DisplacementCount--;
                if (DisplacementCount == 0) {
                    m_Map->SetPosition({round(m_Map->GetPosition().x), round(m_Map->GetPosition().y)});
                    int eventID = m_Map->GetBlocks()[m_Map->GetPlayerPosition().x][m_Map->GetPlayerPosition().y]->GetEventID();
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
            }
            break;

        case EventID::DOOR:
            break;

        case EventID::GRASS:
            if (rand() % 100 < 25) {
                m_FightLoad1_1->SetVisible(true);
                m_FightLoad1_2->SetVisible(true);
                m_BGM->LoadMedia(RESOURCE_DIR"/BGM/Battle.mp3");
                m_BGM->Play();
                m_CurrentState = State::FIGHT;
            } else {
                m_CurrentState = State::UPDATE;
            }
            m_CurrentEvent = EventID::NONE;
            break;
        case EventID::BILLBOARD:
            m_CurrentState = State::UPDATE;
            break;
        case EventID::JUMP:
            if(DisplacementCount!=0){
                m_Map->Move(Displacement);
                if(DisplacementCount>Player->GetSpeed()){
                    Player->GetImage()->Move(Displacement);
                }
                else{
                    Player->GetImage()->Move({0,Displacement.y*-1});
                }
                DisplacementCount--;
            }
            else{
                m_Map->SetPosition({round(m_Map->GetPosition().x), round(m_Map->GetPosition().y)});
                Player->GetImage()->SetPosition({36, -36});
                m_CurrentEvent=EventID::NONE;
                m_CurrentState = State::UPDATE;
            }
            break;

        case EventID::WEEKTREE:
            m_CurrentState = State::UPDATE;
            break;
        case EventID::NONE:
            break;
    }


    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }

    m_Root.Update();
}