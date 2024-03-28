#ifndef POKEMON_CHARACTER_HPP
#define POKEMON_CHARACTER_HPP

#include "GIF.hpp"
#include "PokemonBag.hpp"

class Character {
private:
    std::string m_Name;
    float m_Speed;
    PokemonBag m_PokemonBag;
    std::shared_ptr<GIF> m_Image;
    std::vector<std::vector<std::string>> m_ImagePathses;
    size_t m_CurrentImagePath;
public:
    explicit Character(const std::vector<std::vector<std::string>> &ImagePathses);

    std::string &GetName();

    int GetSpeed();

    std::shared_ptr<GIF> GetImage();

    void SetName(const std::string &str);

    void SetSpeed(float value);

    void SetImagePathses(const std::vector<std::vector<std::string>> &ImagePathses);

    void SetCurrentImagePath(size_t index);
};

#endif
