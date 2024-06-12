#include "UI/ItemUI.hpp"

ItemUI::ItemUI(const std::shared_ptr<Character> &Player) {
    m_ItemBG = std::make_shared<Image>(RESOURCE_DIR"/Background/ComputerInsideBG.png");
    m_ItemBG->SetVisible(false);
    m_ItemBG->SetZIndex(60);

    m_PokeBagUI = std::make_shared<PokeBagUI>(Player);
    m_PokeBagUI->SetVisible(false);

    m_Arrow = std::make_shared<Image>(RESOURCE_DIR"/Background/BlockArrow.png");
    m_Arrow->SetVisible(false);
    m_Arrow->SetZIndex(61);

    m_Arrow2 = std::make_shared<Image>(RESOURCE_DIR"/Background/BlockArrow.png");
    m_Arrow2->SetVisible(false);
    m_Arrow2->SetZIndex(61);

    m_Texts.resize(4);
    for (int i = 0; i < 4; i++) {
        m_Texts[i] = std::make_shared<Text>();
        m_Texts[i]->SetZIndex(61);
        m_Texts[i]->SetVisible(false);
        m_Texts[i]->SetPosition({50, 290 - i * 96});
        m_Texts[i]->SetSize(48);
    }

    m_TB = std::make_shared<TextBox>();
    m_TB->SetVisible(false);
    m_TB->SetZIndex(61);

    m_Player = Player;
}

std::vector<std::shared_ptr<Util::GameObject>> ItemUI::GetChildren() {
    std::vector<std::shared_ptr<Util::GameObject>> result;

    result.push_back(m_ItemBG);
    result.push_back(m_Arrow);
    result.push_back(m_Arrow2);

    for (auto &i: m_PokeBagUI->GetChildren())
        result.push_back(i);

    for (auto &i: m_Texts)
        result.push_back(i);

    for (auto &i: m_TB->GetChildren())
        result.push_back(i);

    return result;
}

void ItemUI::Start() {
    m_ItemBG->SetVisible(true);
    m_Arrow->SetVisible(true);
    m_Arrow->SetPosition({-200, 290});
    m_RowTopIndex = 0;
    for (auto &i: m_Texts)
        i->SetVisible(true);
    Updata();
}

void ItemUI::Run(unsigned mode) {
    if (m_PokeBagUI->GetVisible() && m_ItemBG->GetVisible()) {
        ChangeSkill();
    } else if (m_TB->GetVisibility()) {
        if (Util::Input::IsKeyDown(Util::Keycode::Z)) {
            m_TB->Next();
            m_PokeBagUI->SetVisible(false);
        }
    } else if (m_PokeBagUI->GetVisible()) {
        m_PokeBagUI->Run(0);
        if (!m_PokeBagUI->GetVisible()) {
            size_t index = m_RowTopIndex + 3 - (m_Arrow->GetPosition().y - 2) / 96;
            int id = m_Player->GetItemBag()->GetItemID(m_Items[index].first);
            auto tempPokemon = m_Player->GetPokemonBag()->GetPokemons()[m_PokeBagUI->GetDecision()];
            if (id >= 196 && tempPokemon->GetSkill().size() == 4) {
                m_ItemBG->SetVisible(true);
                for (int i = 0; i < 4; i++) {
                    m_Texts[i]->SetText(tempPokemon->GetSkill()[i]);
                    m_Texts[i]->SetVisible(true);
                }
                m_TB->SetText(tempPokemon->GetName() + "已經擁有4個技能\n請選擇一個做取代");
                m_TB->SetVisible(true);
                m_Arrow2->SetVisible(true);
                m_Arrow2->SetPosition({-200, 290});
            } else {
                Action();
            }
            m_PokeBagUI->SetVisible(true);
        }
    } else if (m_ItemBG->GetVisible()) {
        ChooseItem();
    }
}

bool ItemUI::GetVisible() {
    return m_ItemBG->GetVisible() || m_PokeBagUI->GetVisible();
}

void ItemUI::SetVisible(bool Visibile) {
    m_ItemBG->SetVisible(Visibile);
    m_Arrow->SetVisible(Visibile);
    for (auto &i: m_Texts)
        i->SetVisible(Visibile);
}

void ItemUI::Updata() {
    auto ItemBag = m_Player->GetItemBag();
    m_Items.clear();
    for (int i = 0; i < 256; i++) {
        int Quantity = ItemBag->GetItemQuantity(i);
        std::string ItemName = ItemBag->GetItemName(i);
        if (Quantity > 0) {
            m_Items.push_back({ItemName, Quantity});
        }
    }
    if (m_RowTopIndex < 0) m_RowTopIndex = 0;
    if (m_RowTopIndex != 0 && m_RowTopIndex + 4 > m_Items.size()) m_RowTopIndex--;

    for (size_t i = 0; i < 4; i++) {
        if (i + m_RowTopIndex >= m_Items.size()) {
            m_Texts[i]->SetText(" ");
        } else {
            m_Texts[i]->SetText(m_Items[i + m_RowTopIndex].first + " X" +
                                std::to_string(m_Items[i + m_RowTopIndex].second));
        }
    }

    if (4 - (m_Arrow->GetPosition().y - 2) / 96 > m_Items.size()) {
        m_Arrow->SetPosition({-200, m_Arrow->GetPosition().y + 96});
    }
}

void ItemUI::ChooseItem() {
    if (Util::Input::IsKeyDown(Util::Keycode::UP)) {
        if (m_Arrow->GetPosition().y == 290)
            m_RowTopIndex--;
        else
            m_Arrow->SetPosition({-200, m_Arrow->GetPosition().y + 96});
    } else if (Util::Input::IsKeyDown(Util::Keycode::DOWN)) {
        if (m_Arrow->GetPosition().y == 2)
            m_RowTopIndex++;
        else
            m_Arrow->SetPosition({-200, m_Arrow->GetPosition().y - 96});
    }

    Updata();

    if (Util::Input::IsKeyDown(Util::Keycode::Z)) {
        SetVisible(false);
        size_t index = m_RowTopIndex + 3 - (m_Arrow->GetPosition().y - 2) / 96;
        int id = m_Player->GetItemBag()->GetItemID(m_Items[index].first);
        if ((id >= 16 && id <= 20) || id >= 196) {
            m_PokeBagUI->SetVisible(true);
        } else {
            if (id <= 4) {
                m_TB->SetText("捕捉球只能在戰鬥中使用");
            } else {
                m_TB->SetText("該道具無法使用");
            }
            m_TB->SetVisible(true);
            SetVisible(true);
        }

    }

    if (Util::Input::IsKeyDown(Util::Keycode::X)) {
        SetVisible(false);
    }

}

void ItemUI::ChangeSkill() {
    if (Util::Input::IsKeyDown(Util::Keycode::UP) && m_Arrow2->GetPosition().y < 290) {
        m_Arrow2->SetPosition({-200, m_Arrow2->GetPosition().y + 96});
    } else if (Util::Input::IsKeyDown(Util::Keycode::DOWN) && m_Arrow2->GetPosition().y > 2) {
        m_Arrow2->SetPosition({-200, m_Arrow2->GetPosition().y - 96});
    }

    if (Util::Input::IsKeyDown(Util::Keycode::Z)) {
        m_Arrow2->SetVisible(false);
        m_ItemBG->SetVisible(false);
        for (auto &i: m_Texts)
            i->SetVisible(false);
        Action();
    }

    if (Util::Input::IsKeyDown(Util::Keycode::X)) {
        m_PokeBagUI->SetVisible(false);
    }
}

void ItemUI::Action() {
    size_t index = m_RowTopIndex + 3 - (m_Arrow->GetPosition().y - 2) / 96;
    int id = m_Player->GetItemBag()->GetItemID(m_Items[index].first);
    m_Player->GetItemBag()->AddItemQuantity(id, -1);
    auto tempPokemon = m_Player->GetPokemonBag()->GetPokemons()[m_PokeBagUI->GetDecision()];
    if (id >= 16 && id <= 20) {
        int CurrentHP = tempPokemon->GetCurrentHP();
        int HP = tempPokemon->GetHP();
        int heal = 0;
        if (id == 16)
            heal = HP;
        else if (id == 17)
            heal = HP;
        else if (id == 18)
            heal = 200;
        else if (id == 19)
            heal = 50;
        else if (id == 20)
            heal = 20;

        if (CurrentHP + heal > HP) heal = HP - CurrentHP;

        if (heal == 0) {
            m_TB->SetText(tempPokemon->GetName() + "血量已滿!");
            m_Player->GetItemBag()->AddItemQuantity(id, 1);
        } else {
            m_TB->SetText(tempPokemon->GetName() + "恢复了" + std::to_string(heal) + "HP!");
            m_Player->GetItemBag()->AddItemQuantity(id, -1);
            tempPokemon->SetCurrentHP(CurrentHP + heal);
        }
        m_TB->SetVisible(true);
        m_PokeBagUI->SetVisible(true);
    } else if (id >= 196) {
        std::ifstream file(RESOURCE_DIR"/Pokemon/SkillLearn.txt", std::ios::in);
        std::string skillName;
        for (int i = 196; i <= id; i++)
            std::getline(file, skillName);

        auto skills = tempPokemon->GetSkill();
        if (skills.size() == 4) {
            LOG_DEBUG(3 - ((m_Arrow2->GetPosition().y - 2) / 96));
            m_TB->SetText(tempPokemon->GetName() + "忘記了" + skills[3 - ((m_Arrow2->GetPosition().y - 2) / 96)] +
                          "\n學會了" + skillName);
            skills[3 - ((m_Arrow2->GetPosition().y - 2) / 96)] = skillName;

        } else {
            skills.push_back(skillName);
            m_TB->SetText(tempPokemon->GetName() + "會學了" + skillName);
        }
        m_TB->SetVisible(true);

        Updata();
        tempPokemon->SetSkillByName(skills);
    }
}

int ItemUI::GetDecision() {
    size_t index = m_RowTopIndex + 3 - (m_Arrow->GetPosition().y - 2) / 96;
    return m_Player->GetItemBag()->GetItemID(m_Items[index].first);
}