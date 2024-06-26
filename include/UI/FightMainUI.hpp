#ifndef POKEMON_FIGHTMAINUI_HPP
#define POKEMON_FIGHTMAINUI_HPP

#include "Image.hpp"
#include "GIF.hpp"
#include "TextBox.hpp"
#include "Character.hpp"
#include "SFXSystem.hpp"
#include "Util/Input.hpp"

class FightMainUI {
private:
    std::shared_ptr<Image> m_PlayerImage;
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
    std::shared_ptr<GIF> m_CatchBallAnimation;
    std::shared_ptr<Text> m_PlayerHP;
    std::shared_ptr<Text> m_PlayerPokeName;
    std::shared_ptr<Text> m_EnemyPokeName;
    std::shared_ptr<Character> m_Player;
    std::shared_ptr<Character> m_Enemy;
    std::shared_ptr<TextBox> m_FightTB;
    std::shared_ptr<SFXSystem> m_SFX;
    int m_IsCatching = 0;
    int m_Counter = 0;
public:
    FightMainUI(const std::shared_ptr<Character> &Player, const std::shared_ptr<Character> &Enemy);

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

    void SetBallAnimationVisible(bool visible, bool isPlayer);

    void SetCatchBallAnimationVisible(bool visible);

    void SetPlayerHPTextVisible(bool visible);

    void SetPlayerPokeNameVisible(bool visible);

    void SetEnemyPokeNameVisible(bool visible);

    void SetPlayerPokeScale(const glm::vec2 &scale);

    void SetEnemyPokeScale(const glm::vec2 &scale);

    [[nodiscard]] const glm::vec2 &GetPlayerPokeScale() const;

    [[nodiscard]] const glm::vec2 &GetEnemyPokeScale() const;

    void ZoomImage(bool isPlayer);

    void ReduceImage(bool isPlayer);

    void ReSetWildPosition();

    bool BeginMoving();

    bool EndMoving();

    void SetEnemyPokeImage(int EnemyIndex);

    void SetPlayerPokeImage(int PlayerIndex);

    void SetBallsImage();

    void SetTextHP(int PokeIndex);

    void SetTextPlayerPokeName(int PokeIndex);

    void SetTextEnemyPokeName(int PokeIndex);

    void SetPlayerHPScale(int PokeIndex);

    void SetEnemyHPScale(int PokeIndex);

    void DetectBlood();

    bool Choose();

    std::string GetDecision();

    int GetBallAnimationIndex();

    void RunCatchPokemon(bool SuccessCatch, int EnemyIndex);

    bool IsCatching();

    bool SuccessCatch();

    void ResetCatch();
};

#endif //POKEMON_FIGHTMAINUI_HPP
