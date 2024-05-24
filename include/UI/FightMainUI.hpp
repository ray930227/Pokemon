#ifndef POKEMON_FIGHTMAINUI_HPP
#define POKEMON_FIGHTMAINUI_HPP

#include "Image.hpp"
#include "GIF.hpp"
#include "Text.hpp"
#include "Util/Input.hpp"

class FightMainUI {
private:
    std::shared_ptr<Image> m_Player;
    std::shared_ptr<Image> m_PlayerPokemonImage;
    std::shared_ptr<Image> m_EnemyPokemonImage;
    std::shared_ptr<Image> m_PlayerHPImage;
    std::shared_ptr<Image> m_EnemyHPImage;
    std::shared_ptr<Image> m_PlayerHPUI;
    std::shared_ptr<Image> m_EnemyHPUI;
    std::shared_ptr<Image> m_PlayerBalls;
    std::shared_ptr<Image> m_Arrow;
    std::shared_ptr<Image> m_FightBG;
    std::shared_ptr<GIF> m_BallAnimation;
    std::shared_ptr<Text> m_PlayerHP;
    std::shared_ptr<Text> m_PlayerPokeName;
    std::shared_ptr<Text> m_EnemyPokeName;
public:
    FightMainUI();

    [[nodiscard]] std::vector<std::shared_ptr<Util::GameObject>> GetChildren() const;

    void SetVisible(bool visible);

    void SetFightBGVisible(bool visible);

    void SetArrowVisible(bool visible);

    void SetPlayerVisible(bool visible);

    void SetPlayerHPUIVisible(bool visible);

    void SetEnemyHPUIVisible(bool visible);

    void SetPlayerPokeVisible(bool visible);

    void SetEnemyPokeVisible(bool visible);

    void SetPlayerBallVisible(bool visible);

    void SetBallAnimationVisible(bool visible);

    void SetPlayerHPTextVisible(bool visible);

    void SetPlayerPokeNameVisible(bool visible);

    void SetEnemyPokeNameVisible(bool visible);

    void SetPlayerPokeScale(const glm::vec2 &scale);

    [[nodiscard]] const glm::vec2 &GetPlayerPokeScale() const;

    void ZoomPlayerImage();

    void ReSetWildPosition();

    bool BeginMoving();

    bool EndMoving();

    void SetEnemyPokeImage(const std::string &Path);

    void SetPlayerPokeImage(const std::string &Path);

    void SetBallsImage(const std::string &Path);

    void ReSetBallAnimation();

    void SetTextHP(const std::string &str);

    void SetTextPlayerPokeName(const std::string &str);

    void SetTextEnemyPokeName(const std::string &str);

    void SetPlayerHPScale(const glm::vec2 &scale);

    void SetEnemyHPScale(const glm::vec2 &scale);

    void DetectBlood();

    bool Choose();

    std::string GetDecision();
};

#endif //POKEMON_FIGHTMAINUI_HPP
