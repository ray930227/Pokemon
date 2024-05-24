#include "UI/PokeBagUI.hpp"

PokeBagUI::PokeBagUI() {
    int ImageY = 300;
    for (int i = 0; i < 6; ++i) {
        m_PokedexImage.push_back(std::make_shared<Image>(RESOURCE_DIR"/Pokemon/Pokedex/transparent.png"));
        m_PokeLV.push_back(std::make_shared<Text>());
        m_PokeName.push_back(std::make_shared<Text>());
        m_PokedexCurrentHP.push_back(std::make_shared<Image>(RESOURCE_DIR"/Fight/GreenHealth.png"));
        m_PokedexHPImage.push_back(std::make_shared<Image>(RESOURCE_DIR"/Fight/PokeBagHPUI.png"));
        m_PokeHP.push_back(std::make_shared<Text>());
        m_PokedexImage[i]->SetZIndex(55);
        m_PokedexImage[i]->SetVisible(false);
        m_PokedexImage[i]->SetPosition({-225, ImageY});
        m_PokedexImage[i]->SetScale({2, 2});
        m_PokedexCurrentHP[i]->SetZIndex(55);
        m_PokedexCurrentHP[i]->SetVisible(false);
        m_PokedexCurrentHP[i]->SetPosition({93, ImageY});
        m_PokedexHPImage[i]->SetZIndex(56);
        m_PokedexHPImage[i]->SetVisible(false);
        m_PokedexHPImage[i]->SetPosition({170, ImageY});
        m_PokeLV[i]->SetZIndex(55);
        m_PokeLV[i]->SetVisible(false);
        m_PokeLV[i]->SetPosition({-80, ImageY + 15});
        m_PokeName[i]->SetZIndex(55);
        m_PokeName[i]->SetVisible(false);
        m_PokeName[i]->SetPosition({-80, ImageY - 15});
        m_PokeHP[i]->SetZIndex(55);
        m_PokeHP[i]->SetVisible(false);
        m_PokeHP[i]->SetPosition({215, ImageY + 30});
        ImageY -= 80;
    }
    m_Arrow = std::make_shared<Image>(RESOURCE_DIR"/Fight/arrow.png");
    m_Arrow->SetZIndex(55);
    m_Arrow->SetVisible(false);
    m_Arrow->SetPosition({-320, 300});
    m_PokeBagBG = std::make_shared<Image>(RESOURCE_DIR"/Fight/FightPokemon.png");
    m_PokeBagBG->SetZIndex(54);
    m_PokeBagBG->SetVisible(false);
    m_ArrowCount = 0;
}

std::vector<std::vector<std::shared_ptr<Util::GameObject>>> PokeBagUI::GetChildren() const {
    std::vector<std::vector<std::shared_ptr<Util::GameObject>>> Result;
    for (size_t i = 0; i < 6; i++) {
        std::vector<std::shared_ptr<Util::GameObject>> temp;
        temp.push_back(m_PokedexImage[i]);
        temp.push_back(m_PokedexCurrentHP[i]);
        temp.push_back(m_PokedexHPImage[i]);
        temp.push_back(m_PokeLV[i]);
        temp.push_back(m_PokeHP[i]);
        temp.push_back(m_PokeName[i]);
        Result.push_back(temp);
    }
    Result[0].push_back(m_Arrow);
    Result[0].push_back(m_PokeBagBG);
    return Result;
}

void PokeBagUI::SetLV(const int PokeIndex, const std::string &str) {
    m_PokeLV[PokeIndex]->SetText(str);
}

void PokeBagUI::SetHP(const int PokeIndex, const std::string &str) {
    m_PokeHP[PokeIndex]->SetText(str);
}

void PokeBagUI::SetName(const int PokeIndex, const std::string &str) {
    m_PokeName[PokeIndex]->SetText(str);
}

void PokeBagUI::SetImage(const int PokeIndex, const std::string &ImagePath) {
    m_PokedexImage[PokeIndex]->SetImage(ImagePath);
}

void PokeBagUI::SetScale(const int PokeIndex, const glm::vec2 &scale) {
    m_PokedexCurrentHP[PokeIndex]->SetScale(scale);
}

void PokeBagUI::IsHpLower(const int PokeIndex) {
    if ((m_PokedexCurrentHP[PokeIndex]->GetScaledSize().x) <= 91.200005) {
        m_PokedexCurrentHP[PokeIndex]->SetImage(RESOURCE_DIR"/Fight/RedHealth.png");
    } else {
        m_PokedexCurrentHP[PokeIndex]->SetImage(RESOURCE_DIR"/Fight/GreenHealth.png");
    }
}

void PokeBagUI::SetVisible(const int PokeIndex, bool visible) {
    m_PokedexImage[PokeIndex]->SetVisible(visible);
    m_PokedexCurrentHP[PokeIndex]->SetVisible(visible);
    m_PokedexHPImage[PokeIndex]->SetVisible(visible);
    m_PokeLV[PokeIndex]->SetVisible(visible);
    m_PokeHP[PokeIndex]->SetVisible(visible);
    m_PokeName[PokeIndex]->SetVisible(visible);
    m_Arrow->SetPosition({-320, 300});
    m_Arrow->SetVisible(visible);
    m_PokeBagBG->SetVisible(visible);
}

void PokeBagUI::SetVisible(bool visible) {
    for (size_t i = 0; i < 6; i++) {
        m_PokedexImage[i]->SetVisible(visible);
        m_PokedexCurrentHP[i]->SetVisible(visible);
        m_PokedexHPImage[i]->SetVisible(visible);
        m_PokeLV[i]->SetVisible(visible);
        m_PokeHP[i]->SetVisible(visible);
        m_PokeName[i]->SetVisible(visible);
    }
    m_Arrow->SetVisible(visible);
    m_PokeBagBG->SetVisible(visible);
}

void PokeBagUI::GetArrowCount(int PokePackSize) {
    m_ArrowCount = PokePackSize;
}

bool PokeBagUI::Choose() {
    if (Util::Input::IsKeyDown(Util::Keycode::UP) && m_Arrow->GetPosition().y != 300) {
        m_Arrow->SetPosition({-320, m_Arrow->GetPosition().y + 80});
        m_ArrowCount++;
    } else if (Util::Input::IsKeyDown(Util::Keycode::DOWN) && m_ArrowCount != 1) {
        m_Arrow->SetPosition({-320, m_Arrow->GetPosition().y - 80});
        m_ArrowCount--;
    }
    if (Util::Input::IsKeyDown(Util::Keycode::Z)) {
        return true;
    }
    return false;
}

int PokeBagUI::GetDecision() {
    if (m_Arrow->GetPosition().y == 300) {
        return 0;
    } else if (m_Arrow->GetPosition().y == 220) {
        return 1;
    } else if (m_Arrow->GetPosition().y == 140) {
        return 2;
    } else if (m_Arrow->GetPosition().y == 60) {
        return 3;
    } else if (m_Arrow->GetPosition().y == -20) {
        return 4;
    } else if (m_Arrow->GetPosition().y == -100) {
        return 5;
    }
    return -1;
}