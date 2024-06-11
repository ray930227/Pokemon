#include "UI/ComputerUI.hpp"

ComputerUI::ComputerUI(const std::shared_ptr<Character> &Player) {
    m_ComputerBG = std::make_shared<Image>(RESOURCE_DIR"/Background/ComputerBG.png");
    m_ComputerBG->SetZIndex(51);
    m_ComputerBG->SetVisible(false);

    m_ComputerInsideBG = std::make_shared<Image>(RESOURCE_DIR"/Background/ComputerInsideBG.png");
    m_ComputerInsideBG->SetZIndex(53);
    m_ComputerInsideBG->SetVisible(false);

    m_Arrows.resize(2);
    for (int i = 0; i < 2; i++) {
        m_Arrows[i] = std::make_shared<Image>(RESOURCE_DIR"/Background/BlockArrow.png");
        m_Arrows[i]->SetZIndex(52 + i * 2);
        m_Arrows[i]->SetVisible(false);
    }


    m_TB = std::make_shared<TextBox>();
    m_TB->SetZIndex(52);
    m_TB->SetVisible(false);

    m_Player = Player;

    m_Texts.resize(4);
    for (int i = 0; i < 4; i++) {
        m_Texts[i] = std::make_shared<Text>();
        m_Texts[i]->SetZIndex(54);
        m_Texts[i]->SetVisible(false);
        m_Texts[i]->SetPosition({50, 290 - i * 96});
        m_Texts[i]->SetSize(48);
    }

    m_TFBox = std::make_shared<TFBox>();
    m_TFBox->SetVisible(false);
    m_TFBox->SetZIndex(55);
}

std::vector<std::shared_ptr<Util::GameObject>> ComputerUI::GetChildren() {
    std::vector<std::shared_ptr<Util::GameObject>> result;

    result.push_back(m_ComputerBG);
    result.push_back(m_ComputerInsideBG);
    result.push_back(m_Arrows[0]);
    result.push_back(m_Arrows[1]);

    for (auto &i: m_TB->GetChildren())
        result.push_back(i);

    for (auto &i: m_Texts)
        result.push_back(i);

    for (auto &i: m_TFBox->GetChildren())
        result.push_back(i);

    return result;

}

void ComputerUI::Start() {
    m_ComputerBG->SetVisible(true);
    m_Arrows[0]->SetVisible(true);
    m_Arrows[0]->SetPosition({-290, 290});
    m_TB->SetVisible(true);
    m_TB->SetText("要做甚麼?");
}

void ComputerUI::Run() {
    if (m_TFBox->GetVisible()) {
        if (m_TFBox->Choose()) {
            if (m_TFBox->GetTF()) {
                Action();
            }
            m_TB->SetText("要做甚麼?");
            m_TFBox->SetVisible(false);
            Updata();
        }
    } else if (m_TB->GetText() != "要做甚麼?") {
        if (Util::Input::IsKeyDown(Util::Keycode::Z)) {
            m_TB->SetText("要做甚麼?");
        }
    } else if (m_ComputerInsideBG->GetVisible()) {
        ChoosePokemon();
    } else {
        ChooseAction();
    }
}

bool ComputerUI::GetVisibile() {
    return m_ComputerBG->GetVisible();
}

std::vector<std::shared_ptr<Pokemon>> ComputerUI::GetKeepPokemons() {
    return m_ComputerPokemons;
}

void ComputerUI::Keep(const std::shared_ptr<Pokemon> &Poke) {
    m_ComputerPokemons.push_back(Poke);
}

void ComputerUI::ChooseAction() {
    if (Util::Input::IsKeyDown(Util::Keycode::UP)) {
        if (m_Arrows[0]->GetPosition().y == 290)
            m_Arrows[0]->SetPosition({-290, 2});
        else
            m_Arrows[0]->SetPosition({-290, m_Arrows[0]->GetPosition().y + 96});
    } else if (Util::Input::IsKeyDown(Util::Keycode::DOWN)) {
        if (m_Arrows[0]->GetPosition().y == 2)
            m_Arrows[0]->SetPosition({-290, 290});
        else {
            m_Arrows[0]->SetPosition({-290, m_Arrows[0]->GetPosition().y - 96});
        }
    }

    if (Util::Input::IsKeyDown(Util::Keycode::Z)) {
        if (m_Arrows[0]->GetPosition().y == 2) {
            m_ComputerBG->SetVisible(false);
            m_Arrows[0]->SetVisible(false);
            m_TB->SetVisible(false);
        } else {
            if (m_Arrows[0]->GetPosition().y == 194 && m_Player->GetPokemonBag()->GetPokemons().size() == 1) {
                m_TB->SetVisible(true);
                m_TB->SetText("你身上只有一支神奇寶貝\n身上不能沒有神奇寶貝!!!");
            } else if (m_Arrows[0]->GetPosition().y != 194 && m_ComputerPokemons.empty()) {
                m_TB->SetVisible(true);
                m_TB->SetText("甚麼!!!\n你說我沒有保管過神奇寶貝?!!!");
            } else {
                m_Arrows[0]->SetImage(RESOURCE_DIR"/Background/WhiteArrow.png");
                m_Arrows[1]->SetVisible(true);
                m_Arrows[1]->SetPosition({-200, 290});
                m_ComputerInsideBG->SetVisible(true);
                for (auto &i: m_Texts) {
                    i->SetVisible(true);
                    i->SetText(" ");
                }
                m_RowTopIndex = 0;
            }
        }
    }
}

void ComputerUI::ChoosePokemon() {
    if (Util::Input::IsKeyDown(Util::Keycode::UP)) {
        if (m_Arrows[1]->GetPosition().y == 290)
            m_RowTopIndex--;
        else
            m_Arrows[1]->SetPosition({-200, m_Arrows[1]->GetPosition().y + 96});
    } else if (Util::Input::IsKeyDown(Util::Keycode::DOWN)) {
        if (m_Arrows[1]->GetPosition().y == 2)
            m_RowTopIndex++;
        else
            m_Arrows[1]->SetPosition({-200, m_Arrows[1]->GetPosition().y - 96});
    }
    Updata();

    if (Util::Input::IsKeyDown(Util::Keycode::Z)) {
        size_t index = m_RowTopIndex + 3 - (m_Arrows[1]->GetPosition().y - 2) / 96;
        auto PlayerPokemons = m_Player->GetPokemonBag()->GetPokemons();
        if (m_Arrows[0]->GetPosition().y == 290) {
            m_TB->SetText("是否要取出" + m_ComputerPokemons[index]->GetName() + "?");
        } else if (m_Arrows[0]->GetPosition().y == 194) {
            m_TB->SetText("是否要保管" + PlayerPokemons[index]->GetName() + "?");
        } else {
            m_TB->SetText("是否要放生" + m_ComputerPokemons[index]->GetName() + "?");
        }
        m_TFBox->SetVisible(true);
    }

    if (Util::Input::IsKeyDown(Util::Keycode::X)) {
        m_Arrows[1]->SetVisible(false);
        m_ComputerInsideBG->SetVisible(false);
        for (auto &i: m_Texts)
            i->SetVisible(false);
        m_Arrows[0]->SetImage(RESOURCE_DIR"/Background/BlockArrow.png");
    }
}

void ComputerUI::Updata() {
    std::vector<std::shared_ptr<Pokemon>> Pokemons;
    if (m_Arrows[0]->GetPosition().y == 194)
        Pokemons = m_Player->GetPokemonBag()->GetPokemons();
    else
        Pokemons = m_ComputerPokemons;

    if (m_RowTopIndex < 0) m_RowTopIndex = 0;
    if (m_RowTopIndex != 0 && m_RowTopIndex + 4 > Pokemons.size()) m_RowTopIndex--;

    for (size_t i = 0; i < 4; i++) {
        if (i + m_RowTopIndex >= Pokemons.size()) {
            m_Texts[i]->SetText(" ");
        } else {
            m_Texts[i]->SetText(Pokemons[i + m_RowTopIndex]->GetName() + " LV" +
                                std::to_string(Pokemons[i + m_RowTopIndex]->GetLV()));
        }
    }

    if (4 - (m_Arrows[1]->GetPosition().y - 2) / 96 > Pokemons.size()) {
        m_Arrows[1]->SetPosition({-200, m_Arrows[1]->GetPosition().y + 96});
    }
}

void ComputerUI::Action() {
    size_t index = m_RowTopIndex + 3 - (m_Arrows[1]->GetPosition().y - 2) / 96;
    auto PlayerPokemons = m_Player->GetPokemonBag()->GetPokemons();
    if (m_Arrows[0]->GetPosition().y == 290) {
        PlayerPokemons.push_back(m_ComputerPokemons[index]);
        m_ComputerPokemons.erase(m_ComputerPokemons.begin() + index);
    } else if (m_Arrows[0]->GetPosition().y == 194) {
        m_ComputerPokemons.push_back(PlayerPokemons[index]);
        PlayerPokemons.erase(PlayerPokemons.begin() + index);

    } else {
        m_ComputerPokemons.erase(m_ComputerPokemons.begin() + index);
    }
    if((m_Arrows[0]->GetPosition().y == 194 && PlayerPokemons.size()==1) ||
    (m_Arrows[0]->GetPosition().y != 194 && m_ComputerPokemons.size()==0)){
        m_Arrows[1]->SetVisible(false);
        m_ComputerInsideBG->SetVisible(false);
        for (auto &i: m_Texts)
            i->SetVisible(false);
        m_Arrows[0]->SetImage(RESOURCE_DIR"/Background/BlockArrow.png");
    }
    m_Player->GetPokemonBag()->SetPokemons(PlayerPokemons);
}