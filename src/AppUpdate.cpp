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
    if (Util::Input::IsKeyDown(Util::Keycode::X)) {
        m_CurrentEvent=EventID::SETTING;
        m_CurrentState=State::EVENT;
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
    if (Util::Input::IsKeyDown(Util::Keycode::D)) {
        m_CurrentEvent = EventID::SHOP;
        m_CurrentState = State::EVENT;
    }

    if (Util::Input::IsKeyDown(Util::Keycode::F)) {
        m_CurrentLoading = LoadingID::INTO;
        m_CurrentState = State::LOADING;
    }

    if (Util::Input::IsKeyDown(Util::Keycode::G)) {
        LOG_DEBUG("GetPokemon!");
        std::shared_ptr<Pokemon> TempPokemon = std::make_shared<Pokemon>("001");
        TempPokemon->SetLevel(23);
        NPC_Bromance->GetPokemonBag()->addPomekon(TempPokemon);
        Enemy = NPC_Bromance;
        std::shared_ptr<Pokemon> FirstPokemon = std::make_shared<Pokemon>("004");
        FirstPokemon->SetLevel(23);
        FirstPokemon->SetSkillByID({15});
        Player->GetPokemonBag()->addPomekon(FirstPokemon);
    }

    if (Util::Input::IsKeyDown(Util::Keycode::H)) {
        LOG_DEBUG("Enemy healing!");
        Enemy->GetPokemonBag()->GetPokemons()[0]->SetCurrentHP(1);
        Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->SetCurrentHP(
                Player->GetPokemonBag()->GetPokemons()[m_CurrentPlayerPokemon]->GetHP());
    }

    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
    m_Root.Update();
}