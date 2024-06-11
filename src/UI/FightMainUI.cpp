#include "UI/FightMainUI.hpp"

FightMainUI::FightMainUI(const std::shared_ptr<Character> &Player, const std::shared_ptr<Character> &Enemy) {
    m_PlayerImage = std::make_shared<Image>(RESOURCE_DIR"/Fight/Player.png");
    m_PlayerImage->SetZIndex(52);
    m_PlayerImage->SetVisible(false);
    m_PlayerImage->SetPosition({630, -10});
    m_PlayerPokemonImage = std::make_shared<Image>(RESOURCE_DIR"/transparent.png");
    m_PlayerPokemonImage->SetZIndex(52);
    m_PlayerPokemonImage->SetVisible(false);
    m_PlayerPokemonImage->SetPosition({-210, -10});
    m_EnemyPokemonImage = std::make_shared<Image>(RESOURCE_DIR"/transparent.png");
    m_EnemyPokemonImage->SetZIndex(52);
    m_EnemyPokemonImage->SetVisible(false);
    m_EnemyPokemonImage->SetPosition({210, 230});
    m_PlayerHPImage = std::make_shared<Image>(RESOURCE_DIR"/Fight/GreenHealth.png");
    m_PlayerHPImage->SetZIndex(52);
    m_PlayerHPImage->SetVisible(false);
    m_PlayerHPImage->SetPosition({63, -11});
    m_EnemyHPImage = std::make_shared<Image>(RESOURCE_DIR"/Fight/GreenHealth.png");
    m_EnemyHPImage->SetZIndex(52);
    m_EnemyHPImage->SetVisible(false);
    m_EnemyHPImage->SetPosition({-217, 257});
    m_PlayerHPUI = std::make_shared<Image>(RESOURCE_DIR"/Fight/PlayerUI.png");
    m_PlayerHPUI->SetZIndex(53);
    m_PlayerHPUI->SetVisible(false);
    m_PlayerHPUI->SetPosition({150, -55});
    m_EnemyHPUI = std::make_shared<Image>(RESOURCE_DIR"/Fight/EnemyUI.png");
    m_EnemyHPUI->SetZIndex(53);
    m_EnemyHPUI->SetVisible(false);
    m_EnemyHPUI->SetPosition({-140, 245});
    m_PlayerBalls = std::make_shared<Image>(RESOURCE_DIR"/transparent.png");
    m_PlayerBalls->SetZIndex(53);
    m_PlayerBalls->SetVisible(false);
    m_PlayerBalls->SetPosition({150, -55});
    m_Arrow = std::make_shared<Image>(RESOURCE_DIR"/Fight/arrow.png");
    m_Arrow->SetZIndex(55);
    m_Arrow->SetVisible(false);
    m_Arrow->SetPosition({-25, -200});
    m_FightBG = std::make_shared<Image>(RESOURCE_DIR"/Fight/Fightselectbox.png");
    m_FightBG->SetZIndex(52);
    m_FightBG->SetVisible(false);
    std::vector<std::string> tempBallPath;
    for (int i = 1; i < 6; i++) {
        tempBallPath.push_back(RESOURCE_DIR"/Fight/BallEffect" + std::to_string(i) + ".png");
    }
    m_BallAnimation = std::make_shared<GIF>(tempBallPath);
    m_BallAnimation->SetZIndex(52);
    m_BallAnimation->SetScale({1.3, 1.3});
    m_BallAnimation->SetInterval(200);
    m_BallAnimation->SetVisible(false);
    m_BallAnimation->SetPosition({-210, -10});
    m_PlayerHP = std::make_shared<Text>();
    m_PlayerHP->SetZIndex(52);
    m_PlayerHP->SetVisible(false);
    m_PlayerHP->SetPosition({170, -60});
    m_PlayerPokeName = std::make_shared<Text>();
    m_PlayerPokeName->SetZIndex(52);
    m_PlayerPokeName->SetVisible(false);
    m_PlayerPokeName->SetPosition({175, 25});
    m_EnemyPokeName = std::make_shared<Text>();
    m_EnemyPokeName->SetZIndex(52);
    m_EnemyPokeName->SetVisible(false);
    m_EnemyPokeName->SetPosition({-110, 295});
    m_Player = Player;
    m_Enemy = Enemy;
}

std::vector<std::shared_ptr<Util::GameObject>> FightMainUI::GetChildren() const {
    return {m_PlayerImage, m_PlayerPokemonImage, m_EnemyPokemonImage, m_PlayerHPImage, m_EnemyHPImage, m_PlayerHPUI,
            m_EnemyHPUI, m_PlayerBalls, m_BallAnimation, m_PlayerHP, m_PlayerPokeName, m_EnemyPokeName, m_Arrow,
            m_FightBG};
}

void FightMainUI::SetVisible(bool visible) {
    m_PlayerImage->SetVisible(visible);
    m_PlayerHPImage->SetVisible(visible);
    m_PlayerHPUI->SetVisible(visible);
    m_EnemyHPImage->SetVisible(visible);
    m_EnemyHPUI->SetVisible(visible);
    m_PlayerPokemonImage->SetVisible(visible);
    m_EnemyPokemonImage->SetVisible(visible);
    m_PlayerBalls->SetVisible(visible);
    m_BallAnimation->SetVisible(visible);
    m_PlayerHP->SetVisible(visible);
    m_PlayerPokeName->SetVisible(visible);
    m_EnemyPokeName->SetVisible(visible);
    m_Arrow->SetVisible(visible);
    m_FightBG->SetVisible(visible);
}

void FightMainUI::SetFightBGVisible(bool visible) {
    m_FightBG->SetVisible(visible);
}

void FightMainUI::SetArrowVisible(bool visible) {
    m_Arrow->SetVisible(visible);
    m_Arrow->SetPosition({-25, -200});
}

void FightMainUI::SetPlayerVisible(bool visible) {
    m_PlayerImage->SetVisible(visible);
}

void FightMainUI::SetPlayerHPUIVisible(bool visible) {
    m_PlayerHPImage->SetVisible(visible);
    m_PlayerHPUI->SetVisible(visible);
}

void FightMainUI::SetEnemyHPUIVisible(bool visible) {
    m_EnemyHPImage->SetVisible(visible);
    m_EnemyHPUI->SetVisible(visible);
}

void FightMainUI::SetPlayerPokeVisible(bool visible) {
    m_PlayerPokemonImage->SetVisible(visible);
}

void FightMainUI::SetEnemyPokeVisible(bool visible) {
    m_EnemyPokemonImage->SetVisible(visible);
}

void FightMainUI::SetPlayerBallVisible(bool visible) {
    m_PlayerBalls->SetVisible(visible);
}

void FightMainUI::SetBallAnimationVisible(bool visible) {
    m_BallAnimation->Reset();
    m_BallAnimation->SetVisible(visible);
    m_BallAnimation->Play();
}

void FightMainUI::SetPlayerHPTextVisible(bool visible) {
    m_PlayerHP->SetVisible(visible);
}

void FightMainUI::SetPlayerPokeNameVisible(bool visible) {
    m_PlayerPokeName->SetVisible(visible);
}

void FightMainUI::SetEnemyPokeNameVisible(bool visible) {
    m_EnemyPokeName->SetVisible(visible);
}

void FightMainUI::SetPlayerPokeScale(const glm::vec2 &scale) {
    m_PlayerPokemonImage->SetScale(scale);
}


void FightMainUI::SetEnemyPokeScale(const glm::vec2 &scale) {
    m_EnemyPokemonImage->SetScale(scale);
}

const glm::vec2 &FightMainUI::GetPlayerPokeScale() const {
    return m_PlayerPokemonImage->GetScale();
}

const glm::vec2 &FightMainUI::GetEnemyPokeScale() const {
    return m_EnemyPokemonImage->GetScale();
}

void FightMainUI::ZoomImage(bool isPlayer) {
    if (isPlayer) {
        m_PlayerPokemonImage->SetScale(
                {m_PlayerPokemonImage->GetScale().x + 0.1,
                 m_PlayerPokemonImage->GetScale().y + 0.1});
    } else {
        m_EnemyPokemonImage->SetScale(
                {m_EnemyPokemonImage->GetScale().x + 0.1,
                 m_EnemyPokemonImage->GetScale().y + 0.1});
    }

}

void FightMainUI::ReSetWildPosition() {
    m_PlayerImage->SetPosition({630, -10});
    m_EnemyPokemonImage->SetPosition({-630, 230});
}

bool FightMainUI::BeginMoving() {
    if (m_PlayerImage->GetPosition().x != -210) {
        m_PlayerImage->Move({-20, 0});
        m_EnemyPokemonImage->Move({20, 0});
        return false;
    }
    return true;
}

bool FightMainUI::EndMoving() {
    if (m_PlayerImage->GetPosition().x != -750) {
        m_PlayerImage->Move({-20, 0});
        return false;
    }
    return true;
}

void FightMainUI::SetEnemyPokeImage(int EnemyIndex) {
    m_EnemyPokemonImage->SetImage(RESOURCE_DIR"/Pokemon/PokeImage/Pokemonfront" +
                                  m_Enemy->GetPokemonBag()->GetPokemons()[EnemyIndex]->GetID() + ".png");
}

void FightMainUI::SetPlayerPokeImage(int PlayerIndex) {
    m_PlayerPokemonImage->SetImage(RESOURCE_DIR"/Pokemon/PokeImage/Pokemonback" +
                                   m_Player->GetPokemonBag()->GetPokemons()[PlayerIndex]->GetID() + ".png");
}

void FightMainUI::SetBallsImage() {
    m_PlayerBalls->SetImage(
            RESOURCE_DIR"/Fight/PlayerBall" + std::to_string(m_Player->GetPokemonBag()->size()) + ".png");
}

void FightMainUI::ReSetBallAnimation() {
    m_BallAnimation->SetCurrentFrame(0);
}

void FightMainUI::SetTextHP(int PokeIndex) {
    int CurrentHP = m_Player->GetPokemonBag()->GetPokemons()[PokeIndex]->GetCurrentHP();
    int HP = m_Player->GetPokemonBag()->GetPokemons()[PokeIndex]->GetHP();
    m_PlayerHP->SetText(std::to_string(CurrentHP) + " / " + std::to_string(HP));
}

void FightMainUI::SetTextPlayerPokeName(int PokeIndex) {
    std::string PokeName = m_Player->GetPokemonBag()->GetPokemons()[PokeIndex]->GetName();
    std::string LV = std::to_string(m_Player->GetPokemonBag()->GetPokemons()[PokeIndex]->GetLV());
    m_PlayerPokeName->SetText(PokeName + " LV:" + LV);
}

void FightMainUI::SetTextEnemyPokeName(int PokeIndex) {
    std::string PokeName = m_Enemy->GetPokemonBag()->GetPokemons()[PokeIndex]->GetName();
    std::string LV = std::to_string(m_Enemy->GetPokemonBag()->GetPokemons()[PokeIndex]->GetLV());
    m_EnemyPokeName->SetText(PokeName + " LV:" + LV);
}

void FightMainUI::SetPlayerHPScale(int PokeIndex) {
    int CurrentHP = m_Player->GetPokemonBag()->GetPokemons()[PokeIndex]->GetCurrentHP();
    int HP = m_Player->GetPokemonBag()->GetPokemons()[PokeIndex]->GetHP();
    float X = (1.0 * CurrentHP / HP);
    if (X < 0) {
        X = 0;
    }
    m_PlayerHPImage->SetScale({X, 1});
}

void FightMainUI::SetEnemyHPScale(int PokeIndex) {
    int CurrentHP = m_Enemy->GetPokemonBag()->GetPokemons()[PokeIndex]->GetCurrentHP();
    int HP = m_Enemy->GetPokemonBag()->GetPokemons()[PokeIndex]->GetHP();
    float X = (1.0 * CurrentHP / HP);
    if (X < 0) {
        X = 0;
    }
    m_EnemyHPImage->SetScale({X, 1});
}

void FightMainUI::DetectBlood() {
    if ((m_PlayerHPImage->GetScaledSize().x) <= 91.200005) {
        m_PlayerHPImage->SetImage(RESOURCE_DIR"/Fight/RedHealth.png");
    } else {
        m_PlayerHPImage->SetImage(RESOURCE_DIR"/Fight/GreenHealth.png");
    }
    if ((m_EnemyHPImage->GetScaledSize().x) <= 91.200005) {
        m_EnemyHPImage->SetImage(RESOURCE_DIR"/Fight/RedHealth.png");
    } else {
        m_EnemyHPImage->SetImage(RESOURCE_DIR"/Fight/GreenHealth.png");
    }
}

bool FightMainUI::Choose() {
    if (Util::Input::IsKeyDown(Util::Keycode::UP) && m_Arrow->GetPosition().y != -200) {
        m_Arrow->SetPosition({m_Arrow->GetPosition().x, m_Arrow->GetPosition().y + 100});
    } else if (Util::Input::IsKeyDown(Util::Keycode::DOWN) && m_Arrow->GetPosition().y != -300) {
        m_Arrow->SetPosition({m_Arrow->GetPosition().x, m_Arrow->GetPosition().y - 100});
    } else if (Util::Input::IsKeyDown(Util::Keycode::RIGHT) && m_Arrow->GetPosition().x != 135) {
        m_Arrow->SetPosition({m_Arrow->GetPosition().x + 160, m_Arrow->GetPosition().y});
    } else if (Util::Input::IsKeyDown(Util::Keycode::LEFT) && m_Arrow->GetPosition().x != -25) {
        m_Arrow->SetPosition({m_Arrow->GetPosition().x - 160, m_Arrow->GetPosition().y});
    }
    if (Util::Input::IsKeyDown(Util::Keycode::Z)) {
        return true;
    }
    return false;
}

std::string FightMainUI::GetDecision() {
    //Fight select Skill(-25,-200) PokePack(135,-200)
    //             BackPack(-25,-300) Run(135,-300)
    if (m_Arrow->GetPosition().x == -25 && m_Arrow->GetPosition().y == -200) {
        return "Skill";
    } else if (m_Arrow->GetPosition().x == 135 && m_Arrow->GetPosition().y == -200) {
        return "PokePack";
    } else if (m_Arrow->GetPosition().x == -25 && m_Arrow->GetPosition().y == -300) {
        return "BackPack";
    } else if (m_Arrow->GetPosition().x == 135 && m_Arrow->GetPosition().y == -300) {
        return "Run";
    }
}