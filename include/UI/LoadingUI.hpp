#ifndef POKEMON_LOADINGUI_HPP
#define POKEMON_LOADINGUI_HPP

#include "Image.hpp"
#include "TextBox.hpp"

class LoadingUI {
private:
    std::vector<std::vector<std::shared_ptr<Image>>> m_LoadingImages;
    std::shared_ptr<TextBox> m_TextBox;
    int m_Mode;
public:
    LoadingUI();

    void RandomMode();

    [[nodiscard]] std::vector<std::vector<std::shared_ptr<Util::GameObject>>> GetChildren() const;

    void StartLoading();

    [[nodiscard]] bool GetVisibility();

    void LoadText(const std::string &MyPokeName, const std::string &EnemyPokeName);

    void Next();

    size_t GetCurrentIndex();

    [[nodiscard]] bool GetTBVisibility();
};

#endif //POKEMON_LOADINGUI_HPP
