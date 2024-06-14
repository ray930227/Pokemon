#ifndef POKEMON_POKEBAGUI_HPP
#define POKEMON_POKEBAGUI_HPP

#include "Image.hpp"
#include "Text.hpp"
#include "Character.hpp"
#include "TextBox.hpp"
#include "Util/Input.hpp"
#include <map>

class PokeBagUI {
private:
    std::vector<std::shared_ptr<Text>> m_PokeLV;
    std::vector<std::shared_ptr<Text>> m_PokeName;
    std::vector<std::shared_ptr<Image>> m_PokedexImage;
    std::vector<std::shared_ptr<Image>> m_PokedexHPImage;
    std::vector<std::shared_ptr<Image>> m_PokedexCurrentHP;
    std::vector<std::shared_ptr<Text>> m_PokeHP;
    std::vector<std::shared_ptr<Image>> m_Arrow;
    std::shared_ptr<Image> m_PokeBagBG;
    std::shared_ptr<Character> m_Player;
    std::shared_ptr<TextBox> m_TB;
    std::vector<std::shared_ptr<Image>> m_ChooseBG;
    std::shared_ptr<Image> m_StatusBG;
    std::shared_ptr<Image> m_PokemonImage;
    std::shared_ptr<Image> m_PokemonHPImage;
    std::map<std::string, std::shared_ptr<Text>> m_Texts;
    size_t m_CurrentPokemon = 0;
    bool m_IsXleave = false;
public:
    PokeBagUI(const std::shared_ptr<Character> &Player);

    [[nodiscard]] std::vector<std::shared_ptr<Util::GameObject>> GetChildren() const;

    void SetLV(const int PokeIndex, const std::string &str);

    void SetHP(const int PokeIndex, const std::string &str);

    void SetName(const int PokeIndex, const std::string &str);

    void SetImage(const int PokeIndex, const std::string &ImagePath);

    void SetScale(const int PokeIndex, const glm::vec2 &scale);

    void IsHpLower(const int PokeIndex);

    void SetVisible(bool visible);

    void Run(unsigned mode);

    bool GetVisible();

    int GetDecision();

    void ReSetCurrentPokemon();

    int GetCurrentPokemon();

protected:
    void Updata();

    bool ChoosePokemon();

    bool ChooseAction();

    void Action(unsigned mode);
};

#endif //POKEMON_POKEBAGUI_HPP