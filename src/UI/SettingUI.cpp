#include "UI/SettingUI.hpp"

SettingUI::SettingUI(const std::shared_ptr<Character> &Player, std::shared_ptr<ComputerUI> ComputerUI) {
    m_SettingBG = std::make_shared<Image>(RESOURCE_DIR"/Background/SettingBG.png");
    m_SettingBG->SetZIndex(51);
    m_SettingBG->SetVisible(false);

    m_Arrow = std::make_shared<Image>(RESOURCE_DIR"/Background/BlockArrow.png");
    m_Arrow->SetZIndex(52);
    m_Arrow->SetVisible(false);

    m_PokeBagUI = std::make_shared<PokeBagUI>(Player);
    m_PokeBagUI->SetVisible(false);

    m_ItemUI = std::make_shared<ItemUI>(Player);
    m_ItemUI->SetVisible(false);

    m_PokedexUI = std::make_shared<PokedexUI>(Player, ComputerUI);
    m_PokedexUI->SetVisible(false);

    m_TB = std::make_shared<TextBox>();
    m_TB->SetZIndex(53);
    m_TB->SetVisible(false);

    m_Player = Player;
}

void SettingUI::Start() {
    m_SettingBG->SetVisible(true);
    m_Arrow->SetVisible(true);
    m_Arrow->SetPosition({80, 250});
}

void SettingUI::Run() {
    if (m_TB->GetVisibility()) {
        if (Util::Input::IsKeyDown(Util::Keycode::Z)) {
            m_TB->Next();
        }
    } else if (m_PokedexUI->GetVisible()) {
        m_PokedexUI->Run();
    } else if (m_PokeBagUI->GetVisible()) {
        m_PokeBagUI->Run(3);
    } else if (m_ItemUI->GetVisible()) {
        m_ItemUI->Run(0);
    } else if (Util::Input::IsKeyDown(Util::Keycode::Z)) {
        switch ((int) m_Arrow->GetPosition().y) {
            case 250:
                if (m_Player->GetItemBag()->GetItemQuantity("寶可夢圖鑑") == 0) {
                    m_TB->SetVisible(true);
                    m_TB->SetText("尚無神奇寶貝圖鑑!");
                } else {
                    m_PokedexUI->SetVisible(true);
                }
                break;
            case 178:
                if (m_Player->GetPokemonBag()->GetPokemons().size() == 0) {
                    m_TB->SetVisible(true);
                    m_TB->SetText("尚無任何神奇寶貝!");
                } else {
                    m_PokeBagUI->SetVisible(true);
                }
                break;
            case 106:
                if(m_Player->GetItemBag()->isEmpty()){
                    m_TB->SetVisible(true);
                    m_TB->SetText("尚無任何道具!");
                } else {
                    m_ItemUI->Start();
                }

                break;
            case 34:
                break;
            case -38:
                SetVisible(false);
        }
    } else if (Util::Input::IsKeyDown(Util::Keycode::UP) && m_Arrow->GetPosition().y < 250) {
        m_Arrow->SetPosition({m_Arrow->GetPosition().x, m_Arrow->GetPosition().y + 72});
    } else if (Util::Input::IsKeyDown(Util::Keycode::DOWN) && m_Arrow->GetPosition().y > -38) {
        m_Arrow->SetPosition({m_Arrow->GetPosition().x, m_Arrow->GetPosition().y - 72});
    }

}

std::vector<std::shared_ptr<Util::GameObject>> SettingUI::GetChildren() {
    std::vector<std::shared_ptr<Util::GameObject>> result;
    result.push_back(m_SettingBG);
    result.push_back(m_Arrow);

    for (auto &i: m_PokeBagUI->GetChildren()) {
        result.push_back(i);
    }

    for (auto &i: m_ItemUI->GetChildren()) {
        result.push_back(i);
    }

    for (auto &i: m_TB->GetChildren()) {
        result.push_back(i);
    }

    for (auto &i: m_PokedexUI->GetChildren()) {
        result.push_back(i);
    }

    return result;
}

bool SettingUI::GetVisible() {
    return m_SettingBG->GetVisible();
}

void SettingUI::SetVisible(bool Visible) {
    m_SettingBG->SetVisible(Visible);
    m_Arrow->SetVisible(Visible);
}