#include "App.hpp"

void App::Update() {
    LOG_TRACE("Update");

    if (Util::Input::IsKeyPressed(Util::Keycode::UP)) {
        Displacement = {0, -72.0 / Player->GetSpeed()};
        DisplacementCount = Player->GetSpeed();
        currentDirection = "UP";
        Player->SetCurrentImagePath(0);
        m_CurrentEvent = EventID::MOVE;
    } else if (Util::Input::IsKeyPressed(Util::Keycode::DOWN)) {
        Displacement = {0, 72.0 / Player->GetSpeed()};
        DisplacementCount = Player->GetSpeed();
        currentDirection = "DOWN";
        Player->SetCurrentImagePath(1);
        m_CurrentEvent = EventID::MOVE;
    } else if (Util::Input::IsKeyPressed(Util::Keycode::LEFT)) {
        Displacement = {72.0 / Player->GetSpeed(), 0};
        DisplacementCount = Player->GetSpeed();
        currentDirection = "LEFT";
        Player->SetCurrentImagePath(2);
        m_CurrentEvent = EventID::MOVE;
    } else if (Util::Input::IsKeyPressed(Util::Keycode::RIGHT)) {
        Displacement = {-72.0 / Player->GetSpeed(), 0};
        DisplacementCount = Player->GetSpeed();
        currentDirection = "RIGHT";
        Player->SetCurrentImagePath(3);
        m_CurrentEvent = EventID::MOVE;
    }

    if (Util::Input::IsKeyDown(Util::Keycode::Z)) {
        glm::vec2 targetPosition = m_MapSystem->GetPlayerPosition();
        if (currentDirection == "UP") targetPosition.x--;
        else if (currentDirection == "DOWN") targetPosition.x++;
        else if (currentDirection == "LEFT") targetPosition.y--;
        else if (currentDirection == "RIGHT") targetPosition.y++;

        int temp = m_MapSystem->GetBlocks()[targetPosition.x][targetPosition.y]->GetEventID();

        if (temp != 0 && !m_MapSystem->GetBlocks()[targetPosition.x][targetPosition.y]->GetTraversable()) {
            m_CurrentEvent = (EventID) temp;
            m_CurrentState = State::EVENT;
        }
    }


    if (m_CurrentEvent != EventID::NONE) {
        m_CurrentState = State::EVENT;
    }

    if (Util::Input::IsKeyDown(Util::Keycode::Q)) {
        glm::vec2 PlayerPosition = m_MapSystem->GetPlayerPosition();
        LOG_DEBUG("({},{}),({},{})", m_MapSystem->GetPosition().x, m_MapSystem->GetPosition().y, PlayerPosition.x,
                  PlayerPosition.y);
    }

    if (Util::Input::IsKeyDown(Util::Keycode::A)) {
        Player->SetSpeed(Player->GetSpeed() == 15 ? 5 : 15);
        LOG_DEBUG("Set speed:{}", Player->GetSpeed());
    }

    if (Util::Input::IsKeyDown(Util::Keycode::S)) {
        encounterable = !encounterable;
        LOG_DEBUG("Encounterable:{}", encounterable);
    }

    if (Util::Input::IsKeyPressed(Util::Keycode::F)) {
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
    }
    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
    m_Root.Update();
}