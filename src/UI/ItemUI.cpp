#include "UI/ItemUI.hpp"

ItemUI::ItemUI(const std::shared_ptr<Character>& Player) {
    m_ItemBG=std::make_shared<Image>(RESOURCE_DIR"/Background/ComputerInsideBG.png");
    m_ItemBG->SetVisible(false);
    m_ItemBG->SetZIndex(60);

    m_PokeBagUI=std::make_shared<PokeBagUI>(Player);
    m_PokeBagUI->SetVisible(false);

    m_Arrow=std::make_shared<Image>(RESOURCE_DIR"/Background/BlockArrow.png");
    m_Arrow->SetVisible(false);
    m_Arrow->SetZIndex(61);

    m_Texts.resize(4);
    for(int i=0;i<4;i++){
        m_Texts[i]=std::make_shared<Text>();
        m_Texts[i]->SetZIndex(61);
        m_Texts[i]->SetVisible(false);
        m_Texts[i]->SetPosition({50,290-i*96});
        m_Texts[i]->SetSize(48);
    }

    m_TB=std::make_shared<TextBox>();
    m_TB->SetVisible(false);
    m_TB->SetZIndex(61);

    m_Player=Player;
}

std::vector<std::shared_ptr<Util::GameObject>> ItemUI::GetChildren() {
    std::vector<std::shared_ptr<Util::GameObject>> result;

    result.push_back(m_ItemBG);
    result.push_back(m_Arrow);

    for(auto &i:m_PokeBagUI->GetChildren())
        result.push_back(i);

    for(auto &i:m_Texts)
        result.push_back(i);

    for(auto &i:m_TB->GetChildren())
        result.push_back(i);

    return result;
}

void ItemUI::Start() {
    m_ItemBG->SetVisible(true);
    m_Arrow->SetVisible(true);
    m_Arrow->SetPosition({-200, 290});
    m_RowTopIndex=0;
    for(auto &i:m_Texts)
        i->SetVisible(true);
    Updata();
}

void ItemUI::Run(unsigned mode) {
    if(m_TB->GetVisibility()){
        if(Util::Input::IsKeyDown(Util::Keycode::Z)){
            m_TB->Next();
            m_PokeBagUI->SetVisible(false);
        }
    } else if(m_PokeBagUI->GetVisible()){
        m_PokeBagUI->Run(0);
        if(!m_PokeBagUI->GetVisible()){
            Action(mode);
        }
    } else if(m_ItemBG->GetVisible()){
        ChooseItem();
    }
}

bool ItemUI::GetVisible() {
    return m_ItemBG->GetVisible() || m_PokeBagUI->GetVisible();
}

void ItemUI::SetVisible(bool Visibile) {
    m_ItemBG->SetVisible(Visibile);
    m_Arrow->SetVisible(Visibile);
    for(auto &i:m_Texts)
        i->SetVisible(Visibile);
}

void ItemUI::Updata() {
    auto ItemBag=m_Player->GetItemBag();

    for(auto &i:m_useItem){
        int Quantity=ItemBag->GetItemQuantity(i);
        if(Quantity>0){
            bool check=false;
            for(auto &j:m_Items){
                if(j.first==i){
                    j.second=Quantity;
                    check=true;
                }
            }
            if(!check) m_Items.push_back({i,Quantity});
        }

    }
    if(m_RowTopIndex<0) m_RowTopIndex=0;
    if(m_RowTopIndex!=0 && m_RowTopIndex+4>m_Items.size()) m_RowTopIndex--;

    for(size_t i=0;i<4;i++){
        if(i+m_RowTopIndex>=m_Items.size()){
            m_Texts[i]->SetText(" ");
        }
        else {
            m_Texts[i]->SetText(m_Items[i + m_RowTopIndex].first + " X" +
                                std::to_string(m_Items[i + m_RowTopIndex].second));
        }
    }

    if(4-(m_Arrow->GetPosition().y-2)/96>m_Items.size()){
        m_Arrow->SetPosition({-200,m_Arrow->GetPosition().y+96});
    }
}

void ItemUI::ChooseItem() {
    if(Util::Input::IsKeyDown(Util::Keycode::UP)){
        if(m_Arrow->GetPosition().y==290)
            m_RowTopIndex--;
        else
            m_Arrow->SetPosition({-200,m_Arrow->GetPosition().y+96});
    } else if(Util::Input::IsKeyDown(Util::Keycode::DOWN)){
        if(m_Arrow->GetPosition().y==2)
            m_RowTopIndex++;
        else
            m_Arrow->SetPosition({-200,m_Arrow->GetPosition().y-96});
    }

    Updata();

    if(Util::Input::IsKeyDown(Util::Keycode::Z)){
        SetVisible(false);
        m_PokeBagUI->SetVisible(true);
    }

    if(Util::Input::IsKeyDown(Util::Keycode::X)){
        SetVisible(false);
    }

}

void ItemUI::Action(unsigned mode) {
    size_t index=m_RowTopIndex+3-(m_Arrow->GetPosition().y-2)/96;
    int id=m_Player->GetItemBag()->GetItemID(m_Items[index].first);
    auto tempPokemon=m_Player->GetPokemonBag()->GetPokemons()[m_PokeBagUI->GetDecision()];
    if(id>=16 && id<=20){
        int CurrentHP=tempPokemon->GetCurrentHP();
        int HP=tempPokemon->GetHP();
        int heal=0;
        if(id==16)
            heal=HP;
        else if(id==17)
            heal=HP;
        else if(id==18)
            heal=200;
        else if(id==19)
            heal=50;
        else if(id==20)
            heal=20;

        if(CurrentHP+heal>HP) heal=HP-CurrentHP;

        if(heal==0)
            m_TB->SetText(tempPokemon->GetName()+"血量已滿!");
        else {
            m_TB->SetText(tempPokemon->GetName() + "恢复了" + std::to_string(heal) + "HP!");
            m_Player->GetItemBag()->AddItemQuantity(id,-1);
            tempPokemon->SetCurrentHP(CurrentHP+heal);
        }
        m_TB->SetVisible(true);
        m_PokeBagUI->SetVisible(true);
    }
}

int ItemUI::GetDecision() {
    size_t index=m_RowTopIndex+3-(m_Arrow->GetPosition().y-2)/96;
    return m_Player->GetItemBag()->GetItemID(m_Items[index].first);
}