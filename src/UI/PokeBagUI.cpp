
#include "UI/PokeBagUI.hpp"

PokeBagUI::PokeBagUI(const std::shared_ptr<Character> &Player) {
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

    m_Arrow.resize(2);

    m_Arrow[0] = std::make_shared<Image>(RESOURCE_DIR"/Fight/arrow.png");
    m_Arrow[0]->SetZIndex(55);
    m_Arrow[0]->SetVisible(false);
    m_Arrow[0]->SetPosition({-320, 300});

    m_Arrow[1] = std::make_shared<Image>(RESOURCE_DIR"/Fight/arrow.png");
    m_Arrow[1]->SetZIndex(59);
    m_Arrow[1]->SetVisible(false);
    m_Arrow[1]->SetPosition({150, 240});

    m_PokeBagBG = std::make_shared<Image>(RESOURCE_DIR"/Fight/FightPokemon.png");
    m_PokeBagBG->SetZIndex(54);
    m_PokeBagBG->SetVisible(false);

    m_Player = Player;

    m_TB = std::make_shared<TextBox>();
    m_TB->SetVisible(false);
    m_TB->SetZIndex(59);

    m_ChooseBG.resize(2);
    for (int i = 0; i < 2; i++) {
        m_ChooseBG[i] = std::make_shared<Image>(
                RESOURCE_DIR"/Background/PokeBagChoose" + std::to_string(i + 1) + ".png");
        m_ChooseBG[i]->SetVisible(false);
        m_ChooseBG[i]->SetZIndex(56 + i);
    }

    m_StatusBG = std::make_shared<Image>(RESOURCE_DIR"/Background/StatusBG1.png");
    m_StatusBG->SetVisible(false);
    m_StatusBG->SetZIndex(60);

    std::vector<std::string> texts = {"Attack", "Defence", "Speed", "Special", "Name",
                                      "ID", "Type1", "Type2", "State", "Skill1", "Skill2", "Skill3", "Skill4",
                                      "PP1", "PP2", "PP3", "PP4", "EXP"};
    std::vector<glm::vec2> positions = {{-80,  0},
                                        {-80,  -96},
                                        {-80,  -192},
                                        {-80,  -288},
                                        {160,  300},
                                        {-200, 80},
                                        {250,  -96},
                                        {250,  -288},
                                        {250,  190},
                                        {-200, -10},
                                        {-200, -106},
                                        {-200, -202},
                                        {-200, -298},
                                        {200,  -10},
                                        {200,  -106},
                                        {200,  -202},
                                        {200,  -298},
                                        {160,  190}};
    for (auto &i: texts) {
        m_Texts.insert(std::pair<std::string, std::shared_ptr<Text>>(i, std::make_shared<Text>()));
        m_Texts[i]->SetVisible(false);
        m_Texts[i]->SetZIndex(61);
        m_Texts[i]->SetText(i);
        m_Texts[i]->SetSize(48);
        m_Texts[i]->SetPosition(positions.front());
        positions.erase(positions.begin());
    }

    m_PokemonImage = std::make_shared<Image>(RESOURCE_DIR"/Pokemon/PokeImage/Pokemonfront001.png");
    m_PokemonImage->SetVisible(false);
    m_PokemonImage->SetZIndex(61);
    m_PokemonImage->SetPosition({-128, 232});

    m_PokemonHPImage = std::make_shared<Image>(RESOURCE_DIR"/Fight/GreenHealth.png");
    m_PokemonHPImage->SetVisible(false);
    m_PokemonHPImage->SetZIndex(61);
    m_PokemonHPImage->SetPosition({82, 245});
}

std::vector<std::shared_ptr<Util::GameObject>> PokeBagUI::GetChildren() const {
    std::vector<std::shared_ptr<Util::GameObject>> Result;
    for (size_t i = 0; i < 6; i++) {
        Result.push_back(m_PokedexImage[i]);
        Result.push_back(m_PokedexCurrentHP[i]);
        Result.push_back(m_PokedexHPImage[i]);
        Result.push_back(m_PokeLV[i]);
        Result.push_back(m_PokeHP[i]);
        Result.push_back(m_PokeName[i]);
    }

    for (auto &i: m_TB->GetChildren()) {
        Result.push_back(i);
    }

    for (auto &i: m_Texts) {
        Result.push_back(i.second);
    }

    Result.push_back(m_Arrow[0]);
    Result.push_back(m_Arrow[1]);
    Result.push_back(m_PokeBagBG);
    Result.push_back(m_ChooseBG[0]);
    Result.push_back(m_ChooseBG[1]);
    Result.push_back(m_StatusBG);
    Result.push_back(m_PokemonImage);
    Result.push_back(m_PokemonHPImage);
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

void PokeBagUI::SetVisible(bool visible) {
    for (size_t i = 0; i < m_Player->GetPokemonBag()->GetPokemons().size(); i++) {
        m_PokedexImage[i]->SetVisible(visible);
        m_PokedexCurrentHP[i]->SetVisible(visible);
        m_PokedexHPImage[i]->SetVisible(visible);
        m_PokeLV[i]->SetVisible(visible);
        m_PokeHP[i]->SetVisible(visible);
        m_PokeName[i]->SetVisible(visible);
    }
    Updata();
    m_Arrow[0]->SetVisible(visible);
    m_Arrow[0]->SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR"/Background/BlockArrow.png"));
    m_PokeBagBG->SetVisible(visible);
}

void PokeBagUI::Run(unsigned int mode) {
    if (m_TB->GetVisibility()) {
        switch (mode) {
            case 1:
                if (Util::Input::IsKeyDown(Util::Keycode::Z)) {
                    m_TB->SetVisible(false);
                }
                break;
        }
    } else if (m_StatusBG->GetVisibility()) {
        if (Util::Input::IsKeyDown(Util::Keycode::Z)) {
            if (m_Texts["Attack"]->GetVisible()) {
                m_StatusBG->SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR"/Background/StatusBG2.png"));
                m_Texts["Attack"]->SetVisible(false);
                m_Texts["Defence"]->SetVisible(false);
                m_Texts["Speed"]->SetVisible(false);
                m_Texts["Special"]->SetVisible(false);
                m_Texts["Type1"]->SetVisible(false);
                m_Texts["Type2"]->SetVisible(false);
                m_Texts["State"]->SetVisible(false);
                for (int i = 1; i < 5; i++) {
                    m_Texts["Skill" + std::to_string(i)]->SetVisible(true);
                    m_Texts["PP" + std::to_string(i)]->SetVisible(true);
                }
                m_PokemonHPImage->SetVisible(false);
                m_Texts["EXP"]->SetVisible(true);
            } else {
                m_Texts["ID"]->SetVisible(false);
                m_Texts["Name"]->SetVisible(false);
                m_Texts["EXP"]->SetVisible(false);
                m_StatusBG->SetVisible(false);
                m_PokemonImage->SetVisible(false);
                for (int i = 1; i < 5; i++) {
                    m_Texts["Skill" + std::to_string(i)]->SetVisible(false);
                    m_Texts["PP" + std::to_string(i)]->SetVisible(false);
                }
            }
        }
    } else if (m_ChooseBG[mode - 2]->GetVisibility()) {
        if (ChooseAction()) {
            Action(mode);
        }
    } else if (m_Arrow[1]->GetVisibility()) {
        if (ChoosePokemon()) {
            auto PokemonBag = m_Player->GetPokemonBag();
            auto Pokemons = PokemonBag->GetPokemons();
            auto temp = Pokemons[(int) (m_Arrow[0]->GetPosition().y - 300) / (-80)];
            Pokemons[(int) (m_Arrow[0]->GetPosition().y - 300) / (-80)] = Pokemons[
                    (int) (m_Arrow[1]->GetPosition().y - 300) / (-80)];
            Pokemons[(int) (m_Arrow[1]->GetPosition().y - 300) / (-80)] = temp;
            PokemonBag->SetPokemons(Pokemons);
            Updata();
            m_Arrow[0]->SetZIndex(55);
            m_Arrow[1]->SetVisible(false);
            m_Arrow[1]->SetPosition({150, 240});
            m_Arrow[1]->SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR"/Background/BlockArrow.png"));
        }
    } else {
        if (mode == 1) {
            if (ChoosePokemon()) {
                if (m_Player->GetPokemonBag()->GetPokemons()[GetDecision()]->GetCurrentHP() == 0) {
                    m_TB->SetVisible(true);
                    m_TB->SetText("這隻神奇寶貝已昏厥，無法上場!");
                } else {
                    SetVisible(false);
                }
            }
        } else {
            if (ChoosePokemon()) {
                m_ChooseBG[mode - 2]->SetVisible(true);
                m_Arrow[0]->SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR"/Background/WhiteArrow.png"));
                m_Arrow[1]->SetVisible(true);
                m_Arrow[1]->SetPosition({150, 240});
                m_Arrow[1]->SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR"/Background/BlockArrow.png"));
            }
        }
        if (Util::Input::IsKeyDown(Util::Keycode::X)) {
            SetVisible(false);
        }
    }

}

bool PokeBagUI::GetVisible() {
    return m_PokeBagBG->GetVisibility();
}

int PokeBagUI::GetDecision() {
    return (int) (m_Arrow[0]->GetPosition().y - 300) / (-80);
}

void PokeBagUI::Updata() {
    auto Pokemons = m_Player->GetPokemonBag()->GetPokemons();
    for (int i = 0; i < Pokemons.size(); i++) {
        SetImage(i, RESOURCE_DIR"/Pokemon/Pokedex/Pokedex" + Pokemons[i]->GetID() + ".png");
        SetHP(i, std::to_string(Pokemons[i]->GetCurrentHP()) + "/" + std::to_string(Pokemons[i]->GetHP()));
        SetLV(i, "LV:" + std::to_string(Pokemons[i]->GetLV()));
        SetName(i, Pokemons[i]->GetName());
        SetScale(i, {1.0 * Pokemons[i]->GetCurrentHP() / Pokemons[i]->GetHP(), 1});
        IsHpLower(i);
    }
}

bool PokeBagUI::ChoosePokemon() {
    if (Util::Input::IsKeyDown(Util::Keycode::UP) && m_Arrow[0]->GetPosition().y < 300) {
        m_Arrow[0]->SetPosition({-320, m_Arrow[0]->GetPosition().y + 80});
    } else if (Util::Input::IsKeyDown(Util::Keycode::DOWN) &&
               m_Arrow[0]->GetPosition().y > (380 - (80 * (int) m_Player->GetPokemonBag()->GetPokemons().size()))) {
        m_Arrow[0]->SetPosition({-320, m_Arrow[0]->GetPosition().y - 80});
    }
    if (Util::Input::IsKeyDown(Util::Keycode::Z)) {
        return true;
    }
    return false;
}

bool PokeBagUI::ChooseAction() {
    if (Util::Input::IsKeyDown(Util::Keycode::UP) && m_Arrow[1]->GetPosition().y < 240) {
        m_Arrow[1]->SetPosition({150, m_Arrow[1]->GetPosition().y + 72});
    } else if (Util::Input::IsKeyDown(Util::Keycode::DOWN) && m_Arrow[1]->GetPosition().y > 96) {
        m_Arrow[1]->SetPosition({150, m_Arrow[1]->GetPosition().y - 72});
    }
    if (Util::Input::IsKeyDown(Util::Keycode::Z)) {
        return true;
    }
    return false;
}

void PokeBagUI::Action(unsigned mode) {
    m_ChooseBG[mode - 2]->SetVisible(false);
    m_Arrow[1]->SetVisible(false);
    m_Arrow[0]->SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR"/Background/BlockArrow.png"));
    if (m_Arrow[1]->GetPosition().y == 240) {
        m_Arrow[1]->SetVisible(false);
        if (mode == 2) {
            SetVisible(false);
        } else {
            m_Arrow[1]->SetPosition(m_Arrow[0]->GetPosition());
            m_Arrow[1]->SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR"/Background/WhiteArrow.png"));
            m_Arrow[1]->SetVisible(true);
            m_Arrow[0]->SetPosition({-320, 300});
            m_Arrow[0]->SetZIndex(60);
        }
    } else if (m_Arrow[1]->GetPosition().y == 168) {

        auto Pokemon = m_Player->GetPokemonBag()->GetPokemons()[GetDecision()];
        m_StatusBG->SetVisible(true);
        m_StatusBG->SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR"/Background/StatusBG1.png"));
        for (auto &i: m_Texts) {
            i.second->SetVisible(true);
        }
        m_PokemonImage->SetVisible(true);
        m_PokemonImage->SetDrawable(std::make_shared<Util::Image>(
                RESOURCE_DIR"/Pokemon/PokeImage/Pokemonfront" + Pokemon->GetID() + ".png"));
        m_PokemonHPImage->SetVisible(true);
        m_PokemonHPImage->SetScale({1.0 * Pokemon->GetCurrentHP() / Pokemon->GetHP(), 1});
        if (m_PokemonHPImage->GetScaledSize().x <= 91.200005)
            m_PokemonHPImage->SetImage(RESOURCE_DIR"/Fight/RedHealth.png");
        else
            m_PokemonHPImage->SetImage(RESOURCE_DIR"/Fight/GreenHealth.png");

        m_Texts["Attack"]->SetText(std::to_string(Pokemon->GetAttack()));
        m_Texts["Defence"]->SetText(std::to_string(Pokemon->GetDefence()));
        m_Texts["Speed"]->SetText(std::to_string(Pokemon->GetSpeed()));
        m_Texts["Special"]->SetText(std::to_string(Pokemon->GetSpecial()));
        m_Texts["Name"]->SetText(Pokemon->GetName() + " LV:" + std::to_string(Pokemon->GetLV()));
        m_Texts["ID"]->SetText(Pokemon->GetID());
        m_Texts["Type1"]->SetText((Pokemon->GetType()[0]));
        if (Pokemon->GetType().size() == 2)
            m_Texts["Type2"]->SetText((Pokemon->GetType()[1]));
        else
            m_Texts["Type2"]->SetText(" ");
        m_Texts["State"]->SetText("普通");
        auto Skills = Pokemon->GetSkill();
        auto SkillPP = Pokemon->GetSkillPP();
        auto CurrentSkillPP = Pokemon->GetCurrentSkillPP();
        for (int i = 0; i < 4; i++) {
            if (i < Skills.size()) {
                m_Texts["Skill" + std::to_string(i + 1)]->SetText(Skills[i]);
                m_Texts["PP" + std::to_string(i + 1)]->SetText(CurrentSkillPP[i] + "/" + SkillPP[i]);
            } else {
                m_Texts["Skill" + std::to_string(i + 1)]->SetText(" ");
                m_Texts["PP" + std::to_string(i + 1)]->SetText(" ");
            }
            m_Texts["Skill" + std::to_string(i + 1)]->SetVisible(false);
            m_Texts["PP" + std::to_string(i + 1)]->SetVisible(false);
        }
        m_Texts["EXP"]->SetText(std::to_string(Pokemon->GetCurrentEXP()) + "/" +
                                std::to_string(Pokemon->GetLV() * Pokemon->GetLV() * Pokemon->GetLV()));
        m_Texts["EXP"]->SetVisible(false);
    }
}