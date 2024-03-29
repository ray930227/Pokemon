#include "App.hpp"

void App::Update() {
    LOG_TRACE("Update");

//    if (DisplacementCount != 0) {
//        glm::vec2 PlayerPosition = m_Map->GetPlayerPosition();
//
//        bool up = Displacement.y < 0 && m_Map->GetBlocks()[PlayerPosition.x - 1][PlayerPosition.y]->GetTraversable();
//        bool down = Displacement.y > 0 && m_Map->GetBlocks()[PlayerPosition.x + 1][PlayerPosition.y]->GetTraversable();
//        bool left = Displacement.x > 0 && m_Map->GetBlocks()[PlayerPosition.x][PlayerPosition.y - 1]->GetTraversable();
//        bool right = Displacement.x < 0 && m_Map->GetBlocks()[PlayerPosition.x][PlayerPosition.y + 1]->GetTraversable();
//        bool canMove = up || down || left || right;
//
//        if (!((DisplacementCount == Player->GetSpeed() && canMove) || DisplacementCount != Player->GetSpeed())) {
//            Displacement = {0, 0};
//        }
//        m_Map->Move(Displacement);
//        DisplacementCount--;
//        if (DisplacementCount == 0) {
//            m_Map->SetPosition({round(m_Map->GetPosition().x), round(m_Map->GetPosition().y)});
//            int eventID = m_Map->GetBlocks()[m_Map->GetPlayerPosition().x][m_Map->GetPlayerPosition().y]->GetEventID();
//            if (eventID == 2 && rand() % 100 < 25) {
//                m_FightLoad1_1->SetVisible(true);
//                m_FightLoad1_2->SetVisible(true);
//                m_BGM->LoadMedia(RESOURCE_DIR"/BGM/Battle.mp3");
//                m_BGM->Play();
//                m_CurrentState = State::FIGHT;
//            }
//
//        }
//        LOG_DEBUG(Player->GetImage()->IsPlaying());
//    } else if (Util::Input::IsKeyPressed(Util::Keycode::UP)) {
//        Displacement = {0, -72.0 / Player->GetSpeed()};
//        DisplacementCount = Player->GetSpeed();
//        Player->SetCurrentImage(0);
//        Player->GetImage()->Play();
//        currentDirection = "UP";
//    } else if (Util::Input::IsKeyPressed(Util::Keycode::DOWN)) {
//        Displacement = {0, 72.0 / Player->GetSpeed()};
//        DisplacementCount = Player->GetSpeed();
//        Player->SetCurrentImage(1);
//        Player->GetImage()->Play();
//        currentDirection = "DOWN";
//    } else if (Util::Input::IsKeyPressed(Util::Keycode::LEFT)) {
//        Displacement = {72.0 / Player->GetSpeed(), 0};
//        DisplacementCount = Player->GetSpeed();
//        Player->SetCurrentImage(2);
//        Player->GetImage()->Play();
//        currentDirection = "LEFT";
//    } else if (Util::Input::IsKeyPressed(Util::Keycode::RIGHT)) {
//        Displacement = {-72.0 / Player->GetSpeed(), 0};
//        DisplacementCount = Player->GetSpeed();
//        Player->SetCurrentImage(3);
//        Player->GetImage()->Play();
//        currentDirection = "RIGHT";
//    }


    if (Util::Input::IsKeyPressed(Util::Keycode::UP)) {
        Displacement = {0, -72.0 / Player->GetSpeed()};
        DisplacementCount = Player->GetSpeed();
        currentDirection="UP";
        Player->SetCurrentImagePath(0);
        m_CurrentEvent=EventID::MOVE;
    } else if (Util::Input::IsKeyPressed(Util::Keycode::DOWN)) {
        Displacement = {0, 72.0 / Player->GetSpeed()};
        DisplacementCount = Player->GetSpeed();
        currentDirection="DOWN";
        Player->SetCurrentImagePath(1);
        m_CurrentEvent=EventID::MOVE;
    } else if (Util::Input::IsKeyPressed(Util::Keycode::LEFT)) {
        Displacement = {72.0/ Player->GetSpeed(), 0 };
        DisplacementCount = Player->GetSpeed();
        currentDirection="LEFT";
        Player->SetCurrentImagePath(2);
        m_CurrentEvent=EventID::MOVE;
    } else if (Util::Input::IsKeyPressed(Util::Keycode::RIGHT)) {
        Displacement = {-72.0/ Player->GetSpeed(), 0 };
        DisplacementCount = Player->GetSpeed();
        currentDirection="RIGHT";
        Player->SetCurrentImagePath(3);
        m_CurrentEvent=EventID::MOVE;
    }

    if(Util::Input::IsKeyPressed(Util::Keycode::Z)){
        glm::vec2 targetPosition = m_Map->GetPlayerPosition();
        if(currentDirection=="UP") targetPosition.x--;
        else if(currentDirection=="DOWN") targetPosition.x++;
        else if(currentDirection=="LEFT") targetPosition.y--;
        else if(currentDirection=="RIGHT") targetPosition.y++;

        int temp=m_Map->GetBlocks()[targetPosition.x][targetPosition.y]->GetEventID();

        if(temp!=0) {
            m_CurrentEvent=(EventID)temp;
            m_CurrentState=State::EVENT;
        }
    }


    if(m_CurrentEvent!=EventID::NONE){
        m_CurrentState=State::EVENT;
    }

    if (Util::Input::IsKeyPressed(Util::Keycode::A)) {
        Player->SetSpeed(5);
        glm::vec2 PlayerPosition = m_Map->GetPlayerPosition();
        LOG_DEBUG("({},{}),({},{})", m_Map->GetPosition().x, m_Map->GetPosition().y, PlayerPosition.x,
                  PlayerPosition.y);

    }

    if (Util::Input::IsKeyPressed(Util::Keycode::F)) {
        m_FightLoad1_1->SetVisible(true);
        m_FightLoad1_2->SetVisible(true);
        m_CurrentState = State::FIGHT;
    }
    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
    m_Root.Update();
}