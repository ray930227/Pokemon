#include "UI/ShopUI.hpp"

ShopUI::ShopUI(std::shared_ptr<Character> &Player) {
    for (int i = 0; i < 2; i++) {
        m_Arrows.push_back(std::make_shared<Image>(RESOURCE_DIR"/Background/BlockArrow.png"));
        m_Arrows[i]->SetVisible(false);
        m_Arrows[i]->SetZIndex(91 + i * 2);
    }
    m_Arrows[0]->SetPosition({-300, 300});
    m_Arrows[1]->SetPosition({-150, 180});

    m_ShopBG = std::make_shared<Image>(RESOURCE_DIR"/Background/ShopBG.png");
    m_ShopBG->SetZIndex(90);
    m_ShopBG->SetVisible(false);

    m_ShopInsideBG = std::make_shared<Image>(RESOURCE_DIR"/Background/ShopInsideBG.png");
    m_ShopInsideBG->SetZIndex(92);
    m_ShopInsideBG->SetVisible(false);

    m_TFBox = std::make_shared<TFBox>();

    m_TextBox = std::make_shared<TextBox>();
    m_TextBox->SetVisible(false);

    m_ItemRow.resize(4);
    for (int i = 0; i < 4; i++) {
        m_ItemRow[i] = {std::make_shared<Text>(), 0};
        m_ItemRow[i].first->SetVisible(false);
        m_ItemRow[i].first->SetZIndex(93);
        m_ItemRow[i].first->SetPosition({100, 180 - i * 90});
        m_ItemRow[i].first->SetSize(60);
    }

    std::ifstream file1(RESOURCE_DIR"/Item/BuyNameList.txt", std::ios::in);
    std::ifstream file2(RESOURCE_DIR"/Item/BuyMoneyList.txt", std::ios::in);
    std::string tempStr1, tempStr2;
    while (std::getline(file1, tempStr1) && std::getline(file2, tempStr2)) {
        std::pair<std::string, int> tempPair;
        tempPair.first = tempStr1;
        tempPair.second = std::stoi(tempStr2);
        m_BuyList.push_back(tempPair);
    }
    file1.close();
    file2.close();

    m_Player = Player;

    m_Money = std::make_shared<Text>();
    m_Money->SetVisible(false);
    m_Money->SetZIndex(91);
    m_Money->SetPosition({190, 280});
    m_Money->SetSize(50);
    m_Money->SetText("$" + std::to_string(Player->GetMoney()));
}

void ShopUI::Start() {
    m_ShopBG->SetVisible(true);
    m_Arrows[0]->SetVisible(true);
    m_Arrows[0]->SetPosition({-300, 300});
    m_Money->SetVisible(true);
}

void ShopUI::Run() {
    if (m_TFBox->GetVisibility()) {
        if (m_TFBox->Choose()) {
            m_TFBox->SetVisibility(false);
            if (m_TFBox->GetTF()) {
                if (m_Player->GetMoney() >=
                    m_BuyList[m_RowTopIndex + (180 - m_Arrows[1]->GetPosition().y) / 90].second) {
                    m_TextBox->SetVisible(false);
                    m_Player->SetMoney(m_Player->GetMoney() -
                                       m_BuyList[m_RowTopIndex + (180 - m_Arrows[1]->GetPosition().y) / 90].second);
                    m_Money->SetText("$" + std::to_string(m_Player->GetMoney()));
                    m_Player->GetItemBag()->AddItemQuantity(
                            m_BuyList[m_RowTopIndex + (180 - m_Arrows[1]->GetPosition().y) / 90].first, 1);
                    m_Arrows[1]->SetImage(RESOURCE_DIR"/Background/BlockArrow.png");
                } else {
                    m_TextBox->SetText("金額不夠，無法購買！");
                }
            } else {
                m_TextBox->SetVisible(false);
                m_Arrows[1]->SetImage(RESOURCE_DIR"/Background/BlockArrow.png");
            }

        }
    } else if (Util::Input::IsKeyDown(Util::Keycode::Z)) {
        if (m_TextBox->GetVisibility()) {
            m_TextBox->SetVisible(false);
            m_Arrows[1]->SetImage(RESOURCE_DIR"/Background/BlockArrow.png");
        } else if (m_ShopInsideBG->GetVisibility()) {
            m_TFBox->SetVisibility(true);
            m_TextBox->SetVisible(true);
            m_TextBox->SetText("這樣總共是" + std::to_string(
                    m_BuyList[m_RowTopIndex + (180 - m_Arrows[1]->GetPosition().y) / 90].second) + "元，您要購買嗎?");
            m_Arrows[1]->SetImage(RESOURCE_DIR"/Background/WhiteArrow.png");
        } else {
            auto p = m_Arrows[0]->GetPosition();
            if (p.y == 150) {
                m_ShopBG->SetVisible(false);
                m_Arrows[0]->SetVisible(false);
                m_Money->SetVisible(false);
            } else {
                m_ShopInsideBG->SetVisible(true);
                m_Arrows[1]->SetVisible(true);
                m_Arrows[1]->SetImage(RESOURCE_DIR"/Background/BlockArrow.png");
                m_Arrows[1]->SetPosition({-150, 180});
                m_Arrows[0]->SetImage(RESOURCE_DIR"/Background/WhiteArrow.png");
                m_RowTopIndex = 0;
                for (int i = 0; i < 4; i++) {
                    m_ItemRow[i].first->SetVisible(true);
                }
            }
        }
    } else if (Util::Input::IsKeyDown(Util::Keycode::X)) {
        if (m_ShopInsideBG->GetVisibility()) {
            m_ShopInsideBG->SetVisible(false);
            for (int i = 0; i < 4; i++)
                m_ItemRow[i].first->SetVisible(false);
            m_Arrows[1]->SetVisible(false);
            m_Arrows[0]->SetImage(RESOURCE_DIR"/Background/BlockArrow.png");
        } else {
            m_ShopBG->SetVisible(false);
            m_Arrows[0]->SetVisible(false);
            m_Money->SetVisible(false);
        }
    } else if (Util::Input::IsKeyDown(Util::Keycode::UP)) {
        if (m_ShopInsideBG->GetVisibility()) {
            auto p = m_Arrows[1]->GetPosition();
            if (p.y != 180) {
                m_Arrows[1]->SetPosition({p.x, p.y + 90});
            } else if (m_RowTopIndex != 0) {
                m_RowTopIndex--;
            }
        } else if (m_Arrows[0]->GetPosition().y != 300) {
            auto p = m_Arrows[0]->GetPosition();
            m_Arrows[0]->SetPosition({p.x, p.y + 75});
        }
    } else if (Util::Input::IsKeyDown(Util::Keycode::DOWN)) {
        if (m_ShopInsideBG->GetVisibility()) {
            auto p = m_Arrows[1]->GetPosition();
            if (p.y != -90 && m_ItemRow[(180 - p.y) / 90 + 1].first->GetText() != " ") {
                m_Arrows[1]->SetPosition({p.x, p.y - 90});

            } else if (m_RowTopIndex + 4 < m_BuyList.size()) {
                m_RowTopIndex++;
            }
        } else if (m_Arrows[0]->GetPosition().y != 150) {
            auto p = m_Arrows[0]->GetPosition();
            m_Arrows[0]->SetPosition({p.x, p.y - 75});
        }
    }

    if (m_ShopInsideBG->GetVisibility()) {
        for (int i = 0; i < 4; i++) {
            if (m_Arrows[0]->GetPosition().y == 300) {
                if (m_RowTopIndex + i < m_BuyList.size()) {
                    m_ItemRow[i].first->SetText(m_BuyList[m_RowTopIndex + i].first + "  $" +
                                                std::to_string(m_BuyList[m_RowTopIndex + i].second));
                } else {
                    m_ItemRow[i].first->SetText(" ");
                }
            } else {
                if (false) {
                    m_ItemRow[i].first->SetText(m_BuyList[m_RowTopIndex + i].first + "  $" +
                                                std::to_string(m_BuyList[m_RowTopIndex + i].second));
                } else {
                    m_ItemRow[i].first->SetText(" ");
                }
            }
        }
    }
}

std::vector<std::shared_ptr<Util::GameObject>> ShopUI::GetChildren() {
    std::vector<std::shared_ptr<Util::GameObject>> result;

    result.push_back(m_ShopBG);
    result.push_back(m_ShopInsideBG);
    result.push_back(m_Money);

    for (auto &i: m_Arrows)
        result.push_back(i);

    for (auto &i: m_TFBox->GetChildren())
        result.push_back(i);

    for (auto &i: m_TextBox->GetChildren())
        result.push_back(i);

    for (auto &i: m_ItemRow)
        result.push_back(i.first);

    return result;
}

bool ShopUI::GetVisibile() {
    return m_ShopBG->GetVisibility();
}