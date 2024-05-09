#ifndef POKEMON_POKEBAGUI_HPP
#define POKEMON_POKEBAGUI_HPP

#include "Image.hpp"
#include "Text.hpp"

class PokeBagUI {
private:
    std::vector<std::shared_ptr<Text>> m_PokeLV;
    std::vector<std::shared_ptr<Text>> m_PokeName;
    std::vector<std::shared_ptr<Image>> m_PokedexImage;
    std::vector<std::shared_ptr<Image>> m_PokedexHPImage;
    std::vector<std::shared_ptr<Image>> m_PokedexCurrentHP;
    std::vector<std::shared_ptr<Text>> m_PokeHP;
public:
    PokeBagUI();

    [[nodiscard]] std::vector<std::vector<std::shared_ptr<Util::GameObject>>> GetChildren() const;

    void SetLV(const int PokeIndex, const std::string &str);

    void SetHP(const int PokeIndex, const std::string &str);

    void SetName(const int PokeIndex, const std::string &str);

    void SetImage(const int PokeIndex, const std::string &ImagePath);

    void SetVisible(const int PokeIndex, bool visible);

    void SetVisible(bool visible);
};

#endif //POKEMON_POKEBAGUI_HPP
