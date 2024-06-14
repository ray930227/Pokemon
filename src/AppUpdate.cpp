#include "App.hpp"

void App::Update() {
    LOG_TRACE("Update");
    if (m_CurrentEvent != EventID::NONE) {
        m_CurrentState = State::EVENT;
    } else if (Util::Input::IsKeyPressed(Util::Keycode::UP)) {
        m_Displacement = {0, -72.0 / m_Player->GetSpeed()};
        m_DisplacementCount = m_Player->GetSpeed();
        m_CurrentDirection = "UP";
        m_Player->SetCurrentImagePath(0);
        m_CurrentEvent = EventID::MOVE;
    } else if (Util::Input::IsKeyPressed(Util::Keycode::DOWN)) {
        m_Displacement = {0, 72.0 / m_Player->GetSpeed()};
        m_DisplacementCount = m_Player->GetSpeed();
        m_CurrentDirection = "DOWN";
        m_Player->SetCurrentImagePath(1);
        m_CurrentEvent = EventID::MOVE;
    } else if (Util::Input::IsKeyPressed(Util::Keycode::LEFT)) {
        m_Displacement = {72.0 / m_Player->GetSpeed(), 0};
        m_DisplacementCount = m_Player->GetSpeed();
        m_CurrentDirection = "LEFT";
        m_Player->SetCurrentImagePath(2);
        m_CurrentEvent = EventID::MOVE;
    } else if (Util::Input::IsKeyPressed(Util::Keycode::RIGHT)) {
        m_Displacement = {-72.0 / m_Player->GetSpeed(), 0};
        m_DisplacementCount = m_Player->GetSpeed();
        m_CurrentDirection = "RIGHT";
        m_Player->SetCurrentImagePath(3);
        m_CurrentEvent = EventID::MOVE;
    }

    if (Util::Input::IsKeyDown(Util::Keycode::Z)) {
        glm::vec2 targetPosition = m_MapSystem->GetPlayerPosition();
        if (m_CurrentDirection == "UP") targetPosition.x--;
        else if (m_CurrentDirection == "DOWN") targetPosition.x++;
        else if (m_CurrentDirection == "LEFT") targetPosition.y--;
        else if (m_CurrentDirection == "RIGHT") targetPosition.y++;

        int temp = m_MapSystem->GetBlocks()[targetPosition.x][targetPosition.y]->GetEventID();

        if (temp != 0 && !m_MapSystem->GetBlocks()[targetPosition.x][targetPosition.y]->GetTraversable()) {
            m_CurrentEvent = (EventID) temp;
            m_CurrentState = State::EVENT;
        }
    }
    if (Util::Input::IsKeyDown(Util::Keycode::X)) {
        m_CurrentEvent = EventID::SETTING;
        m_CurrentState = State::EVENT;
    }

    if (m_CurrentEvent != EventID::NONE) {
        m_CurrentState = State::EVENT;
    }

    if (Util::Input::IsKeyDown(Util::Keycode::A)) {
        m_Player->SetSpeed(m_Player->GetSpeed() == 15 ? 5 : 15);
        if (m_Player->GetSpeed() == 5)
            LOG_DEBUG("Speed UP!");
        else
            LOG_DEBUG("Speed DOWN!");
    }

    if (Util::Input::IsKeyDown(Util::Keycode::S)) {
        m_Encounterable = !m_Encounterable;
        LOG_DEBUG("Encounterable:{}", m_Encounterable);
    }

    if (Util::Input::IsKeyDown(Util::Keycode::D)) {
        LOG_DEBUG("It's so powerful!!!!!!!!");
        std::vector<std::shared_ptr<Pokemon>> Pokemons;
        Pokemons.push_back(std::make_shared<Pokemon>("150"));
        Pokemons.push_back(std::make_shared<Pokemon>("146"));
        Pokemons.push_back(std::make_shared<Pokemon>("145"));
        Pokemons.push_back(std::make_shared<Pokemon>("144"));
        Pokemons.push_back(std::make_shared<Pokemon>("149"));
        Pokemons.push_back(std::make_shared<Pokemon>("006"));
        for (auto Poke: Pokemons) {
            Poke->SetLevel(100);
        }
        m_Player->GetPokemonBag()->SetPokemons(Pokemons);
    }

    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
    m_Root.Update();
}