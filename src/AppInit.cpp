#include "App.hpp"

#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

void App::Init() {
    if(tempBox->GetVisibility()){
        tempBox->InputString();
        if (Util::Input::IsKeyPressed(Util::Keycode::KP_ENTER) || Util::Input::IsKeyPressed(Util::Keycode::RETURN)){
            tempBox->SetVisible(false);
            m_TB->Next();
            if(m_TB->GetLineIndex()==11) {
                Player->SetName(tempBox->GetText());
            }
            else{
                NPC_Bromance->SetName(tempBox->GetText());
            }

        }
        if(tempBox->GetText().size()>=8) {
            std::string tempStr=tempBox->GetText();
            tempStr.pop_back();
            tempBox->SetText(tempStr);
        }
    }
    else if (Util::Input::IsKeyDown(Util::Keycode::Z)){
        m_TB->Next();
        if(m_TB->GetLineIndex()==10 || m_TB->GetLineIndex()==13){
            tempBox->SetPosition({0,0});
            tempBox->SetScale({0.5,0.5});
            tempBox->SetVisible(true);
            tempBox->SetText(" ");
        }
    }
    if(m_TB->GetText().find("<Player>")<m_TB->GetText().size()){
        std::string tempStr=m_TB->GetText();
        tempStr.replace(tempStr.begin()+tempStr.find("<Player>"),
                        tempStr.begin()+tempStr.find("<Player>")+8,
                        Player->GetName());
        m_TB->SetText(tempStr);
    }
    if(m_TB->GetText().find("<NPC_Bromance>")<m_TB->GetText().size()){
        std::string tempStr=m_TB->GetText();
        tempStr.replace(tempStr.begin()+tempStr.find("<NPC_Bromance>"),
                        tempStr.begin()+tempStr.find("<NPC_Bromance>")+14,
                        NPC_Bromance->GetName());
        m_TB->SetText(tempStr);
    }
    if(!m_TB->GetVisibility()){
        m_BG->SetImage(RESOURCE_DIR"/Background/Testmap.png");
        m_BG->SetPosition({-1224,2592});
        Player->SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR"/Charactor/playerfront.png"));
        Player->SetVisible(true);
        DisplacementCount=0;
        m_CurrentState = State::UPDATE;
    }
    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
    m_Root.Update();
}