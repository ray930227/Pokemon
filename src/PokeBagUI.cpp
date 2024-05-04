#include "FightUI/PokeBagUI.hpp"

PokeBagUI::PokeBagUI() {
    int ImageY=300;
    for (int i = 0; i < 6; ++i) {
        m_PokedexImage.push_back(std::make_shared<Image>(RESOURCE_DIR"/Pokemon/Pokedex/Pokedex003.png"));
        m_PokeInfo.push_back(std::make_shared<Text>());
        m_PokedexCurrentHP.push_back(std::make_shared<Image>(RESOURCE_DIR"/Fight/GreenHealth.png"));
        m_PokedexHPImage.push_back(std::make_shared<Image>(RESOURCE_DIR"/Fight/PokeBagHPUI.png"));
        m_PokeHP.push_back(std::make_shared<Text>());
        m_PokedexImage[i]->SetZIndex(55);
        m_PokedexImage[i]->SetVisible(false);
        m_PokedexImage[i]->SetPosition({-250,ImageY});
        m_PokedexImage[i]->SetScale({2,2});
        m_PokedexCurrentHP[i]->SetZIndex(55);
        m_PokedexCurrentHP[i]->SetVisible(false);
        m_PokedexCurrentHP[i]->SetPosition({93,ImageY});
        m_PokedexHPImage[i]->SetZIndex(56);
        m_PokedexHPImage[i]->SetVisible(false);
        m_PokedexHPImage[i]->SetPosition({170,ImageY});
        m_PokeInfo[i]->SetZIndex(55);
        m_PokeInfo[i]->SetVisible(false);
        m_PokeInfo[i]->SetPosition({-80,ImageY+10});
        m_PokeHP[i]->SetZIndex(55);
        m_PokeHP[i]->SetVisible(false);
        m_PokeHP[i]->SetPosition({215,ImageY+30});
        ImageY-=80;
    }
}

std::vector<std::vector<std::shared_ptr<Util::GameObject>>> PokeBagUI::GetChildren() const {
    std::vector<std::vector<std::shared_ptr<Util::GameObject>>> Result;
    for (size_t i=0;i<6;i++){
        std::vector<std::shared_ptr<Util::GameObject>> temp;
        temp.push_back(m_PokedexImage[i]);
        temp.push_back(m_PokedexCurrentHP[i]);
        temp.push_back(m_PokedexHPImage[i]);
        temp.push_back(m_PokeInfo[i]);
        temp.push_back(m_PokeHP[i]);
        Result.push_back(temp);
    }
    return Result;
}

void PokeBagUI::SetText(const int PokeIndex, const std::string &str) {
    m_PokeInfo[PokeIndex]->SetText(str);
}

void PokeBagUI::SetHP(const int PokeIndex, const std::string &str) {
    m_PokeHP[PokeIndex]->SetText(str);
}

void PokeBagUI::SetImage(const int PokeIndex, const std::string &ImagePath) {
    m_PokedexImage[PokeIndex]->SetImage(ImagePath);
}

void PokeBagUI::SetVisible(const int PokeIndex, bool visible) {
    m_PokedexImage[PokeIndex]->SetVisible(visible);
    m_PokedexCurrentHP[PokeIndex]->SetVisible(visible);
    m_PokedexHPImage[PokeIndex]->SetVisible(visible);
    m_PokeInfo[PokeIndex]->SetVisible(visible);
    m_PokeHP[PokeIndex]->SetVisible(visible);
}

void PokeBagUI::SetVisible(bool visible) {
    for (size_t i=0;i<6;i++){
        m_PokedexImage[i]->SetVisible(visible);
        m_PokedexCurrentHP[i]->SetVisible(visible);
        m_PokedexHPImage[i]->SetVisible(visible);
        m_PokeInfo[i]->SetVisible(visible);
        m_PokeHP[i]->SetVisible(visible);
    }
}