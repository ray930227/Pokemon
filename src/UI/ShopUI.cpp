#include "UI/ShopUI.hpp"

ShopUI::ShopUI() {
    for(int i=0;i<2;i++){
        m_Arrows.push_back(std::make_shared<Image>(RESOURCE_DIR"/Background/BlockArrow.png"));
        m_Arrows[i]->SetVisible(false);
        m_Arrows[i]->SetZIndex(91+i*2);
    }
    m_Arrows[0]->SetPosition({-300,300});

    m_ShopBG=std::make_shared<Image>(RESOURCE_DIR"/Background/ShopBG.png");
    m_ShopBG->SetZIndex(90);
    m_ShopBG->SetVisible(false);

    m_ShopInsideBG=std::make_shared<Image>(RESOURCE_DIR"/Background/ShopInsideBG.png");
    m_ShopInsideBG->SetZIndex(92);
    m_ShopInsideBG->SetVisible(false);

    m_TFBox=std::make_shared<TFBox>();

    m_TextBox=std::make_shared<TextBox>();
    m_TextBox->SetVisible(false);
}

void ShopUI::Start() {
    m_ShopBG->SetVisible(true);
    m_Arrows[0]->SetVisible(true);
}

void ShopUI::Run() {
    if(m_TFBox->GetVisibility()){
        if(m_TFBox->Choose()){
            m_TFBox->SetVisibility(false);
            m_TextBox->SetVisible(false);
            if (m_TFBox->GetTF()){

            }
            m_Arrows[1]->SetImage(RESOURCE_DIR"/Background/BlockArrow.png");
        }
    } else if(Util::Input::IsKeyDown(Util::Keycode::Z)){
        if(m_ShopInsideBG->GetVisibility()){
            m_TFBox->SetVisibility(true);
            m_TextBox->SetVisible(true);
            m_TextBox->SetText("這樣總共是XXX元，您要購買嗎?");
            m_Arrows[1]->SetImage(RESOURCE_DIR"/Background/WhiteArrow.png");
        }
        else{
            auto p=m_Arrows[0]->GetPosition();
            if(p.y==300){
                m_ShopInsideBG->SetVisible(true);
                m_Arrows[1]->SetVisible(true);
                m_Arrows[1]->SetImage(RESOURCE_DIR"/Background/BlockArrow.png");
                m_Arrows[0]->SetImage(RESOURCE_DIR"/Background/WhiteArrow.png");
            }else if(p.y==225){
                m_ShopInsideBG->SetVisible(true);
                m_Arrows[1]->SetVisible(true);
                m_Arrows[1]->SetImage(RESOURCE_DIR"/Background/BlockArrow.png");
                m_Arrows[0]->SetImage(RESOURCE_DIR"/Background/WhiteArrow.png");
            }else{
                m_ShopBG->SetVisible(false);
                m_Arrows[0]->SetVisible(false);
            }
        }
    } else if(Util::Input::IsKeyDown(Util::Keycode::X)){
        if(m_ShopInsideBG->GetVisibility()){
            m_ShopInsideBG->SetVisible(false);
            m_Arrows[1]->SetVisible(false);
            m_Arrows[0]->SetImage(RESOURCE_DIR"/Background/BlockArrow.png");
        }
        else{
            m_ShopBG->SetVisible(false);
            m_Arrows[0]->SetVisible(false);
        }
    } else if(Util::Input::IsKeyDown(Util::Keycode::UP)){
        if(m_ShopInsideBG->GetVisibility()){

        }
        else if(m_Arrows[0]->GetPosition().y!=300){
            auto p=m_Arrows[0]->GetPosition();
            m_Arrows[0]->SetPosition({p.x,p.y+75});
        }
    } else if(Util::Input::IsKeyDown(Util::Keycode::DOWN)){
        if(m_ShopInsideBG->GetVisibility()){

        }
        else if(m_Arrows[0]->GetPosition().y!=150){
            auto p=m_Arrows[0]->GetPosition();
            m_Arrows[0]->SetPosition({p.x,p.y-75});
        }
    }
}

std::vector<std::shared_ptr<Util::GameObject>> ShopUI::GetChildren() {
    std::vector<std::shared_ptr<Util::GameObject>> result;
    for(auto& i:m_Arrows)
        result.push_back(i);

    result.push_back(m_ShopBG);
    result.push_back(m_ShopInsideBG);

    for(auto& i:m_TFBox->GetChildren())
        result.push_back(i);

    for(auto& i:m_TextBox->GetChildren())
        result.push_back(i);

    return result;
}

bool ShopUI::GetVisibile() {
    return m_ShopBG->GetVisibility();
}