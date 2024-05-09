#ifndef POKEMON_LOADINGUI_HPP
#define POKEMON_LOADINGUI_HPP

#include "Image.hpp"

class LoadingUI{
private:
    std::vector<std::vector<std::shared_ptr<Image>>> m_LoadingImages;
public:
    LoadingUI();

    [[nodiscard]] std::vector<std::vector<std::shared_ptr<Util::GameObject>>> GetChildren() const;


};

#endif //POKEMON_LOADINGUI_HPP
