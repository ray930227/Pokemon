#ifndef POKEMON_LOADINGUI_HPP
#define POKEMON_LOADINGUI_HPP

#include "Image.hpp"
#include "TextBox.hpp"
#include "Character.hpp"

class LoadingUI {
private:
    std::vector<std::vector<std::shared_ptr<Image>>> m_LoadingImages;
    std::shared_ptr<TextBox> m_TextBox;
    std::shared_ptr<Character> m_Player;
    std::shared_ptr<Character> m_Enemy;
    std::shared_ptr<Image> m_WhiteBG;
    int m_Mode;
public:
    LoadingUI(const std::shared_ptr<Character> &Player, const std::shared_ptr<Character> &Enemy);

    void RandomMode();

    [[nodiscard]] std::vector<std::vector<std::shared_ptr<Util::GameObject>>> GetChildren() const;

    void StartLoading();

    [[nodiscard]] bool GetVisibility();

    void LoadText(int PokeIndex, int EnemyIndex, bool IsWildPokemon);

    void Next();

    size_t GetCurrentIndex();

    [[nodiscard]] bool GetTBVisibility();

    void SetTBVisible(bool Visible);
};

#endif //POKEMON_LOADINGUI_HPP
