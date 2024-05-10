#include "UI/FightMainUI.hpp"

FightMainUI::FightMainUI() {
    m_Player = std::make_shared<Image>(RESOURCE_DIR"/Fight/Player.png");
    m_Player->SetZIndex(52);
    m_Player->SetVisible(false);
    m_Player->SetPosition({630, -10});
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
    std::vector<std::string> tempBallPath;
    for (int i = 1; i < 6; i++) {
        tempBallPath.push_back(RESOURCE_DIR"/Fight/BallEffect" + std::to_string(i) + ".png");
    }
    m_BallAnimation = std::make_shared<GIF>(tempBallPath);
    m_BallAnimation->SetZIndex(52);
    m_BallAnimation->SetScale({1.3, 1.3});
    m_BallAnimation->SetInterval(400);
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
}

std::vector<std::shared_ptr<Util::GameObject>> FightMainUI::GetChildren() const {
    return {m_Player, m_PlayerPokemonImage, m_EnemyPokemonImage, m_PlayerHPImage, m_EnemyHPImage, m_PlayerHPUI,
            m_EnemyHPUI, m_PlayerBalls, m_BallAnimation, m_PlayerHP, m_PlayerPokeName, m_EnemyPokeName};
}

void FightMainUI::SetVisible(bool visible) {
    m_Player->SetVisible(visible);
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
}

void FightMainUI::SetPlayer(bool visible) {
    m_Player->SetVisible(visible);
}

void FightMainUI::SetPlayerHPUI(bool visible) {
    m_PlayerHPImage->SetVisible(visible);
    m_PlayerHPUI->SetVisible(visible);
}

void FightMainUI::SetEnemyHPUI(bool visible) {
    m_EnemyHPImage->SetVisible(visible);
    m_EnemyHPUI->SetVisible(visible);
}

void FightMainUI::SetPlayerPoke(bool visible) {
    m_PlayerPokemonImage->SetVisible(visible);
}

void FightMainUI::SetEnemyPoke(bool visible) {
    m_EnemyPokemonImage->SetVisible(visible);
}

void FightMainUI::SetPlayerBall(bool visible) {
    m_PlayerBalls->SetVisible(visible);
}

void FightMainUI::SetBallAnimation(bool visible) {
    m_BallAnimation->Reset();
    m_BallAnimation->SetVisible(visible);
    m_BallAnimation->Play();
}

void FightMainUI::SetPlayerHPText(bool visible) {
    m_PlayerHP->SetVisible(visible);
}

void FightMainUI::SetPlayerPokeName(bool visible) {
    m_PlayerPokeName->SetVisible(visible);
}

void FightMainUI::SetEnemyPokeName(bool visible) {
    m_EnemyPokeName->SetVisible(visible);
}

void FightMainUI::SetPlayerPokeScale(const glm::vec2 &scale) {
    m_PlayerPokemonImage->SetScale(scale);
}

const glm::vec2 &FightMainUI::GetPlayerPokeScale() const {
    return m_PlayerPokemonImage->GetScale();
}

void FightMainUI::ZoomPlayerImage() {
    m_PlayerPokemonImage->SetScale(
            {m_PlayerPokemonImage->GetScale().x + 0.05,
             m_PlayerPokemonImage->GetScale().y + 0.05});
}

void FightMainUI::ReSetWildPosition() {
    m_Player->SetPosition({630, -10});
    m_EnemyPokemonImage->SetPosition({-630, 230});
}

bool FightMainUI::BeginMoving() {
    if (m_Player->GetPosition().x != -210) {
        m_Player->Move({-15, 0});
        m_EnemyPokemonImage->Move({15, 0});
        return false;
    }
    return true;
}

bool FightMainUI::EndMoving() {
    if (m_Player->GetPosition().x != -750) {
        m_Player->Move({-15, 0});
        return false;
    }
    return true;
}

void FightMainUI::SetEnemyPokeImage(const std::string &Path) {
    m_EnemyPokemonImage->SetImage(Path);
}

void FightMainUI::SetPlayerPokeImage(const std::string &Path) {
    m_PlayerPokemonImage->SetImage(Path);
}

void FightMainUI::SetBallsImage(const std::string &Path) {
    m_PlayerBalls->SetImage(Path);
}

void FightMainUI::ReSetBallAnimation() {
    m_BallAnimation->SetCurrentFrame(0);
}

void FightMainUI::SetTextHP(const std::string &str) {
    m_PlayerHP->SetText(str);
}

void FightMainUI::SetTextPlayerPokeName(const std::string &str) {
    m_PlayerPokeName->SetText(str);
}

void FightMainUI::SetTextEnemyPokeName(const std::string &str) {
    m_EnemyPokeName->SetText(str);
}

void FightMainUI::SetPlayerHPScale(const glm::vec2 &scale) {
    m_PlayerHPImage->SetScale(scale);
}

void FightMainUI::SetEnemyHPScale(const glm::vec2 &scale) {
    m_EnemyHPImage->SetScale(scale);
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