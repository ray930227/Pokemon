#include "App.hpp"

void App::Update() {
    LOG_TRACE("Update");
    if (m_CurrentEvent != EventID::NONE) {
        m_CurrentState = State::EVENT;
    } else if (Util::Input::IsKeyPressed(Util::Keycode::UP)) {
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
    if (Util::Input::IsKeyDown(Util::Keycode::X)) {
        m_CurrentEvent = EventID::SETTING;
        m_CurrentState = State::EVENT;
    }

    if (m_CurrentEvent != EventID::NONE) {
        m_CurrentState = State::EVENT;
    }

    if (Util::Input::IsKeyDown(Util::Keycode::A)) {
        Player->SetSpeed(Player->GetSpeed() == 15 ? 5 : 15);
        if(Player->GetSpeed() == 5)
            LOG_DEBUG("Speed UP!");
        else
            LOG_DEBUG("Speed DOWN!");
    }

    if (Util::Input::IsKeyDown(Util::Keycode::S)) {
        encounterable = !encounterable;
        LOG_DEBUG("Encounterable:{}", encounterable);
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
        Player->GetPokemonBag()->SetPokemons(Pokemons);
    }

    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
    m_Root.Update();
}