#ifndef POKEMON_LOADINGUI_HPP
#define POKEMON_LOADINGUI_HPP

#include "Image.hpp"

class LoadingUI {
private:
    std::vector<std::vector<std::shared_ptr<Image>>> m_LoadingImages;
    int m_Mode;
public:
    LoadingUI();

    void RandomMode();

    [[nodiscard]] std::vector<std::vector<std::shared_ptr<Util::GameObject>>> GetChildren() const;

    void SelectMode();

    [[nodiscard]] bool GetVisibility();

};

#endif //POKEMON_LOADINGUI_HPP
