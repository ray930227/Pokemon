#include "UI/SettingUI.hpp"

SettingUI::SettingUI(const std::shared_ptr<Character>& Player) {
    m_SettingBG=std::make_shared<Image>(RESOURCE_DIR"/Background/SettingBG.png");
    m_SettingBG->SetZIndex(51);
    m_SettingBG->SetVisible(false);

    m_Arrow=std::make_shared<Image>(RESOURCE_DIR"/Background/BlockArrow.png");
    m_Arrow->SetZIndex(52);
    m_Arrow->SetVisible(false);

    m_PokeBagUI=std::make_shared<PokeBagUI>(Player);
    m_PokeBagUI->SetVisible(false);

    m_TB=std::make_shared<TextBox>();
    m_TB->SetZIndex(53);
    m_TB->SetVisible(false);

    m_Player=Player;
}

void SettingUI::Start() {
    m_SettingBG->SetVisible(true);
    m_Arrow->SetVisible(true);
    m_Arrow->SetPosition({80, 250});
}

void SettingUI::Run() {
    if(m_TB->GetVisibility()){
        if(Util::Input::IsKeyDown(Util::Keycode::Z)){
            m_TB->Next();
        }
    } else if(m_PokeBagUI->GetVisible()){
        m_PokeBagUI->Run(3);
    } else if(Util::Input::IsKeyDown(Util::Keycode::Z)){
        switch ((int)m_Arrow->GetPosition().y) {
            case 250:
                if(m_Player->GetItemBag()->GetItemQuantity("寶可夢圖鑑")==0){
                    m_TB->SetVisible(true);
                    m_TB->SetText("尚無神奇寶貝圖鑑!");
                }
                else{
                    //實作圖鑑UI
                }
                break;
            case 178:
                if(m_Player->GetPokemonBag()->GetPokemons().size()==0){
                    m_TB->SetVisible(true);
                    m_TB->SetText("尚無任何神奇寶貝!");
                }
                else{
                    m_PokeBagUI->SetVisible(true);
                }
                break;
            case 106:
                break;
            case 34:
                break;
            case -38:
                SetVisibile(false);
        }
    } else if(Util::Input::IsKeyDown(Util::Keycode::UP) && m_Arrow->GetPosition().y<250){
        m_Arrow->SetPosition({m_Arrow->GetPosition().x,m_Arrow->GetPosition().y+72});
    } else if(Util::Input::IsKeyDown(Util::Keycode::DOWN) && m_Arrow->GetPosition().y>-38){
        m_Arrow->SetPosition({m_Arrow->GetPosition().x,m_Arrow->GetPosition().y-72});
    }

}

std::vector<std::shared_ptr<Util::GameObject>> SettingUI::GetChildren() {
    std::vector<std::shared_ptr<Util::GameObject>> result;
    result.push_back(m_SettingBG);
    result.push_back(m_Arrow);

    for(auto &i:m_PokeBagUI->GetChildren()){
        result.push_back(i);
    }

    for (auto &i: m_TB->GetChildren()) {
        result.push_back(i);
    }

    return result;
}

bool SettingUI::GetVisibile() {
    return m_SettingBG->GetVisible();
}

void SettingUI::SetVisibile(bool Visibile) {
    m_SettingBG->SetVisible(Visibile);
    m_Arrow->SetVisible(Visibile);
}