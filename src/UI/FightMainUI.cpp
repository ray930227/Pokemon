#include "UI/FightMainUI.hpp"

FightMainUI::FightMainUI() {
    m_PlayerPokemonImage = std::make_shared<Image>(RESOURCE_DIR"/transparent.png");
    m_PlayerPokemonImage->SetZIndex(52);
    m_PlayerPokemonImage->SetVisible(false);
    m_PlayerPokemonImage->SetPosition({-210, -10});
    m_EnemyPokemonImage= std::make_shared<Image>(RESOURCE_DIR"/transparent.png");
    m_EnemyPokemonImage->SetZIndex(52);
    m_EnemyPokemonImage->SetVisible(false);
    m_EnemyPokemonImage->SetPosition({210, 230});
    m_PlayerHPImage= std::make_shared<Image>(RESOURCE_DIR"/Fight/GreenHealth.png");
    m_PlayerHPImage->SetZIndex(52);
    m_PlayerHPImage->SetVisible(false);
    m_PlayerHPImage->SetPosition({63, -11});
    m_EnemyHPImage= std::make_shared<Image>(RESOURCE_DIR"/Fight/GreenHealth.png");
    m_EnemyHPImage->SetZIndex(52);
    m_EnemyHPImage->SetVisible(false);
    m_EnemyHPImage->SetPosition({-217, 257});
    m_PlayerHPUI= std::make_shared<Image>(RESOURCE_DIR"/Fight/PlayerUI.png");
    m_PlayerHPUI->SetZIndex(53);
    m_PlayerHPUI->SetVisible(false);
    m_PlayerHPUI->SetPosition({150, -55});
    m_EnemyHPUI= std::make_shared<Image>(RESOURCE_DIR"/Fight/EnemyUI.png");
    m_EnemyHPUI->SetZIndex(53);
    m_EnemyHPUI->SetVisible(false);
    m_EnemyHPUI->SetPosition({-140, 245});
    m_PlayerBalls= std::make_shared<Image>(RESOURCE_DIR"/transparent.png");
    m_PlayerBalls->SetZIndex(53);
    m_PlayerBalls->SetVisible(false);
    m_PlayerBalls->SetPosition({150, -55});
    std::vector<std::string> tempBallPath;
    for (int i = 1; i < 6; i++) {
        tempBallPath.push_back(RESOURCE_DIR"/Fight/BallEffect" + std::to_string(i) + ".png");
    }
    m_BallAnimation =std::make_shared<GIF>(tempBallPath);
    m_BallAnimation->SetZIndex(52);
    m_BallAnimation->SetScale({1.3, 1.3});
    m_BallAnimation->SetInterval(400);
    m_BallAnimation->SetVisible(false);
    m_BallAnimation->SetPosition({-210, -10});
}

