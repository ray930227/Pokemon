#include "App.hpp"

#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

void App::Init() {

    if(tempBox->GetVisibility() && PlayerName.size()<8){
        if(Util::Input::IsKeyDown(Util::Keycode::A)){
            if(PlayerName==" ") PlayerName="A";
            else PlayerName.push_back('a');
        }
        if(Util::Input::IsKeyDown(Util::Keycode::B)){
            if(PlayerName==" ") PlayerName="B";
            else PlayerName.push_back('b');
        }
        if(Util::Input::IsKeyDown(Util::Keycode::C)){
            if(PlayerName==" ") PlayerName="C";
            else PlayerName.push_back('c');
        }
        if(Util::Input::IsKeyDown(Util::Keycode::D)){
            if(PlayerName==" ") PlayerName="D";
            else PlayerName.push_back('d');
        }
        if(Util::Input::IsKeyDown(Util::Keycode::E)){
            if(PlayerName==" ") PlayerName="E";
            else PlayerName.push_back('e');
        }
        if(Util::Input::IsKeyDown(Util::Keycode::F)){
            if(PlayerName==" ") PlayerName="F";
            else PlayerName.push_back('f');
        }
        if(Util::Input::IsKeyDown(Util::Keycode::G)){
            if(PlayerName==" ") PlayerName="G";
            else PlayerName.push_back('g');
        }
        if(Util::Input::IsKeyDown(Util::Keycode::H)){
            if(PlayerName==" ") PlayerName="H";
            else PlayerName.push_back('h');
        }
        if(Util::Input::IsKeyDown(Util::Keycode::I)){
            if(PlayerName==" ") PlayerName="I";
            else PlayerName.push_back('i');
        }
        if(Util::Input::IsKeyDown(Util::Keycode::J)){
            if(PlayerName==" ") PlayerName="J";
            else PlayerName.push_back('j');
        }
        if(Util::Input::IsKeyDown(Util::Keycode::K)){
            if(PlayerName==" ") PlayerName="K";
            else PlayerName.push_back('k');
        }
        if(Util::Input::IsKeyDown(Util::Keycode::L)){
            if(PlayerName==" ") PlayerName="L";
            else PlayerName.push_back('l');
        }
        if(Util::Input::IsKeyDown(Util::Keycode::M)){
            if(PlayerName==" ") PlayerName="M";
            else PlayerName.push_back('m');
        }
        if(Util::Input::IsKeyDown(Util::Keycode::N)){
            if(PlayerName==" ") PlayerName="N";
            else PlayerName.push_back('n');
        }
        if(Util::Input::IsKeyDown(Util::Keycode::O)){
            if(PlayerName==" ") PlayerName="O";
            else PlayerName.push_back('o');
        }
        if(Util::Input::IsKeyDown(Util::Keycode::P)){
            if(PlayerName==" ") PlayerName="P";
            else PlayerName.push_back('p');
        }
        if(Util::Input::IsKeyDown(Util::Keycode::Q)){
            if(PlayerName==" ") PlayerName="Q";
            else PlayerName.push_back('q');
        }
        if(Util::Input::IsKeyDown(Util::Keycode::R)){
            if(PlayerName==" ") PlayerName="R";
            else PlayerName.push_back('r');
        }
        if(Util::Input::IsKeyDown(Util::Keycode::S)){
            if(PlayerName==" ") PlayerName="S";
            else PlayerName.push_back('s');
        }
        if(Util::Input::IsKeyDown(Util::Keycode::T)){
            if(PlayerName==" ") PlayerName="T";
            else PlayerName.push_back('t');
        }
        if(Util::Input::IsKeyDown(Util::Keycode::U)){
            if(PlayerName==" ") PlayerName="U";
            else PlayerName.push_back('u');
        }
        if(Util::Input::IsKeyDown(Util::Keycode::V)){
            if(PlayerName==" ") PlayerName="V";
            else PlayerName.push_back('v');
        }
        if(Util::Input::IsKeyDown(Util::Keycode::W)){
            if(PlayerName==" ") PlayerName="W";
            else PlayerName.push_back('w');
        }
        if(Util::Input::IsKeyDown(Util::Keycode::X)){
            if(PlayerName==" ") PlayerName="X";
            else PlayerName.push_back('x');
        }
        if(Util::Input::IsKeyDown(Util::Keycode::Y)){
            if(PlayerName==" ") PlayerName="Y";
            else PlayerName.push_back('y');
        }
        if(Util::Input::IsKeyDown(Util::Keycode::Z)){
            if(PlayerName==" ") PlayerName="Z";
            else PlayerName.push_back('z');
        }
        if(Util::Input::IsKeyDown(Util::Keycode::BACKSPACE)){
            if(PlayerName.size()<=1) PlayerName=" ";
            else PlayerName.pop_back();
        }
        if (Util::Input::IsKeyPressed(Util::Keycode::KP_ENTER) || Util::Input::IsKeyPressed(Util::Keycode::RETURN)){
            tempBox->SetVisible(false);
            m_TB->Next();
            std::string temp="嗯……你叫做"+PlayerName+"啊！";
            m_TB->SetText(temp);
        }
        if(PlayerName.size()==8) PlayerName.pop_back();
        tempBox->SetText(PlayerName);
    }
    else if (Util::Input::IsKeyDown(Util::Keycode::Z)){
        m_TB->Next();
        if(m_TB->GetLineIndex()==10){
            tempBox->SetVisible(true);
            PlayerName=" ";
        }
    }

    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
    m_Root.Update();
}