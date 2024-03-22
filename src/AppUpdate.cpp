#include "App.hpp"

void App::Update() {
    LOG_TRACE("Update");

    if (DisplacementCount != 0) {
        glm::vec2 PlayerPosition = m_Map->GetPlayerPosition();

        bool up = Displacement.y < 0 && m_Map->GetBlocks()[PlayerPosition.x - 1][PlayerPosition.y]->GetTraversable();
        bool down = Displacement.y > 0 && m_Map->GetBlocks()[PlayerPosition.x + 1][PlayerPosition.y]->GetTraversable();
        bool left = Displacement.x > 0 && m_Map->GetBlocks()[PlayerPosition.x][PlayerPosition.y - 1]->GetTraversable();
        bool right = Displacement.x < 0 && m_Map->GetBlocks()[PlayerPosition.x][PlayerPosition.y + 1]->GetTraversable();
        bool canMove = up || down || left || right;

        if (!((DisplacementCount == Player->GetSpeed() && canMove) || DisplacementCount != Player->GetSpeed())) {
            Displacement = {0, 0};
        }
        m_Map->Move(Displacement);
        DisplacementCount--;
        if (DisplacementCount == 0) {
            m_Map->SetPosition({round(m_Map->GetPosition().x), round(m_Map->GetPosition().y)});
            int eventID = m_Map->GetBlocks()[m_Map->GetPlayerPosition().x][m_Map->GetPlayerPosition().y]->GetEventID();
            if (eventID == 2 && rand() % 100 < 25) {
                m_FightLoad1_1->SetVisible(true);
                m_FightLoad1_2->SetVisible(true);
                m_BGM->LoadMedia(RESOURCE_DIR"/BGM/Battle.mp3");
                m_BGM->Play();
                m_CurrentState = State::FIGHT;
            }

        }
        LOG_DEBUG(Player->GetImage()->IsPlaying());
    } else if (Util::Input::IsKeyPressed(Util::Keycode::UP)) {
        Displacement = {0, -72.0 / Player->GetSpeed()};
        DisplacementCount = Player->GetSpeed();
        Player->SetCurrentImage(0);
        Player->GetImage()->Play();
        currentDirection = "UP";
    } else if (Util::Input::IsKeyPressed(Util::Keycode::DOWN)) {
        Displacement = {0, 72.0 / Player->GetSpeed()};
        DisplacementCount = Player->GetSpeed();
        Player->SetCurrentImage(1);
        Player->GetImage()->Play();
        currentDirection = "DOWN";
    } else if (Util::Input::IsKeyPressed(Util::Keycode::LEFT)) {
        Displacement = {72.0 / Player->GetSpeed(), 0};
        DisplacementCount = Player->GetSpeed();
        Player->SetCurrentImage(2);
        Player->GetImage()->Play();
        currentDirection = "LEFT";
    } else if (Util::Input::IsKeyPressed(Util::Keycode::RIGHT)) {
        Displacement = {-72.0 / Player->GetSpeed(), 0};
        DisplacementCount = Player->GetSpeed();
        Player->SetCurrentImage(3);
        Player->GetImage()->Play();
        currentDirection = "RIGHT";
    }

//    if(Player->GetImage()->IsPlaying()==false) {
//        if (currentDirection=="UP") {
//            std::vector<std::string> tempImagePaths;
//            tempImagePaths.push_back(RESOURCE_DIR"/Charactor/playerBack_2.png");
//            tempImagePaths.push_back(RESOURCE_DIR"/Charactor/playerBack_1.png");
//            tempImagePaths.push_back(RESOURCE_DIR"/Charactor/playerBack_3.png");
//            tempImagePaths.push_back(RESOURCE_DIR"/Charactor/playerBack_1.png");
//            Player->GetImage()->SetImagePaths(tempImagePaths);
//        } else if (currentDirection=="DOWN") {
//            std::vector<std::string> tempImagePaths;
//            tempImagePaths.push_back(RESOURCE_DIR"/Charactor/playerFront_2.png");
//            tempImagePaths.push_back(RESOURCE_DIR"/Charactor/playerFront_1.png");
//            tempImagePaths.push_back(RESOURCE_DIR"/Charactor/playerFront_3.png");
//            tempImagePaths.push_back(RESOURCE_DIR"/Charactor/playerFront_1.png");
//            Player->GetImage()->SetImagePaths(tempImagePaths);
//        } else if (currentDirection=="LEFT") {
//            std::vector<std::string> tempImagePaths;
//            tempImagePaths.push_back(RESOURCE_DIR"/Charactor/playerLeft_2.png");
//            tempImagePaths.push_back(RESOURCE_DIR"/Charactor/playerLeft_1.png");
//            Player->GetImage()->SetImagePaths(tempImagePaths);
//        } else if(currentDirection=="RIGHT") {
//            std::vector<std::string> tempImagePaths;
//            tempImagePaths.push_back(RESOURCE_DIR"/Charactor/playerRight_2.png");
//            tempImagePaths.push_back(RESOURCE_DIR"/Charactor/playerRight_1.png");
//            Player->GetImage()->SetImagePaths(tempImagePaths);
//        }
//    }


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