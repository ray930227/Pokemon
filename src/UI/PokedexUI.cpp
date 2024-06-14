#include "UI/PokedexUI.hpp"

PokedexUI::PokedexUI(const std::shared_ptr<Character> &Player, std::shared_ptr<ComputerUI> computerUI) {
    m_PokedexBG = std::make_shared<Image>(RESOURCE_DIR"/Background/PokedexBG.png");
    m_PokedexBG->SetZIndex(60);
    m_PokedexBG->SetVisible(false);

    m_Arrow = std::make_shared<Image>(RESOURCE_DIR"/Background/BlockArrow.png");
    m_Arrow->SetZIndex(61);
    m_Arrow->SetVisible(false);

    m_PokeImage = std::make_shared<Image>(RESOURCE_DIR"/Pokemon/PokeImage/Pokemonfront001.png");
    m_PokeImage->SetZIndex(61);
    m_PokeImage->SetVisible(false);
    m_PokeImage->SetPosition({232, -232});

    m_NameTexts.resize(8);
    m_IDTexts.resize(8);
    for (int i = 0; i < 8; i++) {
        m_NameTexts[i] = std::make_shared<Text>();
        m_NameTexts[i]->SetVisible(false);
        m_NameTexts[i]->SetZIndex(61);
        m_NameTexts[i]->SetSize(36);
        m_NameTexts[i]->SetPosition({-100, 240 - (72 * i)});

        m_IDTexts[i] = std::make_shared<Text>();
        m_IDTexts[i]->SetVisible(false);
        m_IDTexts[i]->SetZIndex(61);
        m_IDTexts[i]->SetSize(36);
        m_IDTexts[i]->SetPosition({-250, 240 - (72 * i)});
    }

    m_GetText = std::make_shared<Text>();
    m_GetText->SetVisible(false);
    m_GetText->SetZIndex(61);
    m_GetText->SetSize(48);
    m_GetText->SetPosition({280, 240});

    std::ifstream file(RESOURCE_DIR"/Pokemon/Name.txt", std::ios::in);
    std::string tempStr;
    for (int i = 0; i < 151; i++) {
        std::stringstream ToString;
        ToString << std::setw(3) << std::setfill('0') << i + 1;
        std::string StringID = ToString.str();
        std::getline(file, tempStr);
        m_PokeNames.push_back(StringID + " " + tempStr);
    }
    file.close();

    m_Player = Player;
    m_ComputerUI = computerUI;
}

std::vector<std::shared_ptr<Util::GameObject>> PokedexUI::GetChildren() {
    std::vector<std::shared_ptr<Util::GameObject>> result;

    result.push_back(m_PokedexBG);
    result.push_back(m_Arrow);
    result.push_back(m_PokeImage);
    result.push_back(m_GetText);

    for (int i = 0; i < 8; i++) {
        result.push_back(m_NameTexts[i]);
        result.push_back(m_IDTexts[i]);
    }

    return result;
}

void PokedexUI::Start() {
    SetVisible(true);
    Update();
}

void PokedexUI::Run() {
    if (Util::Input::IsKeyDown(Util::Keycode::UP)) {
        if (m_Arrow->GetPosition().y == 240) {
            m_RowTopIndex--;
        } else {
            m_Arrow->SetPosition({m_Arrow->GetPosition().x, m_Arrow->GetPosition().y + 72});
        }
    } else if (Util::Input::IsKeyDown(Util::Keycode::DOWN)) {
        if (m_Arrow->GetPosition().y == -264) {
            m_RowTopIndex++;
        } else {
            m_Arrow->SetPosition({m_Arrow->GetPosition().x, m_Arrow->GetPosition().y - 72});
        }
    } else if (Util::Input::IsKeyDown(Util::Keycode::LEFT)) {
        m_RowTopIndex -= 8;
    } else if (Util::Input::IsKeyDown(Util::Keycode::RIGHT)) {
        m_RowTopIndex += 8;
    }
    Update();

    if (Util::Input::IsKeyDown(Util::Keycode::Z)) {
        m_SFXSystem.Play("PokeSound" + m_IDTexts[7 - (m_Arrow->GetPosition().y + 264) / 72]->GetText());
    }
    if (Util::Input::IsKeyDown(Util::Keycode::X)) {
        SetVisible(false);
    }
}

bool PokedexUI::GetVisible() {
    return m_PokedexBG->GetVisible();
}

void PokedexUI::SetVisible(bool Visible) {
    m_PokedexBG->SetVisible(Visible);
    m_Arrow->SetVisible(Visible);
    m_Arrow->SetPosition({-320, 240});
    m_PokeImage->SetVisible(Visible);
    m_GetText->SetVisible(Visible);
    for (int i = 0; i < 8; i++) {
        m_NameTexts[i]->SetVisible(Visible);
        m_IDTexts[i]->SetVisible(Visible);
    }
}

void PokedexUI::Update() {
    if (m_RowTopIndex < 0) m_RowTopIndex = 0;
    if (m_RowTopIndex + 8 >= 151) m_RowTopIndex = 143;
    for (size_t i = 0; i < 8; i++) {

        m_IDTexts[i]->SetText(m_PokeNames[m_RowTopIndex + i].substr(0, m_PokeNames[m_RowTopIndex + i].find(' ')));
        if (m_PokeGet[m_RowTopIndex + i]) {
            m_NameTexts[i]->SetText(m_PokeNames[m_RowTopIndex + i].substr(m_PokeNames[m_RowTopIndex + i].find(' '),
                                                                          m_PokeNames[m_RowTopIndex + i].length()));
        } else {
            m_NameTexts[i]->SetText("？？？？？");
        }
    }

    if (m_NameTexts[7 - (m_Arrow->GetPosition().y + 264) / 72]->GetText() == "？？？？？") {
        m_PokeImage->SetImage(RESOURCE_DIR"/Pokemon/PokeImage/PokemonUnknown.png");
    } else {
        m_PokeImage->SetImage(RESOURCE_DIR"/Pokemon/PokeImage/Pokemonfront" +
                              m_IDTexts[7 - (m_Arrow->GetPosition().y + 264) / 72]->GetText() + ".png");
    }
    for (auto &i: m_Player->GetPokemonBag()->GetPokemons()) {
        m_PokeGet[std::stoi(i->GetID()) - 1] = true;
    }
    for (auto &i: m_ComputerUI->GetKeepPokemons()) {
        m_PokeGet[std::stoi(i->GetID()) - 1] = true;
    }

    int count = 0;
    for (bool i: m_PokeGet) {
        if (i) count++;
    }
    m_GetText->SetText(std::to_string(count));

}