#ifndef POKEMON_FIGHTMAINUI_HPP
#define POKEMON_FIGHTMAINUI_HPP

#include "Image.hpp"
#include "GIF.hpp"

class FightMainUI{
private:
    std::shared_ptr<Image> m_PlayerPokemonImage;
    std::shared_ptr<Image> m_EnemyPokemonImage;
    std::shared_ptr<Image> m_PlayerHPImage;
    std::shared_ptr<Image> m_EnemyHPImage;
    std::shared_ptr<Image> m_PlayerHPUI;
    std::shared_ptr<Image> m_EnemyHPUI;
    std::shared_ptr<Image> m_PlayerBalls;
    std::shared_ptr<GIF> m_BallAnimation;
public:
    FightMainUI();

    [[nodiscard]] std::vector<std::vector<std::shared_ptr<Util::GameObject>>> GetChildren() const;

};

#endif //POKEMON_FIGHTMAINUI_HPP
