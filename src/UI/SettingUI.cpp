#include "UI/SettingUI.hpp"

SettingUI::SettingUI(const std::shared_ptr<Character> &Player, const std::shared_ptr<ComputerUI>& ComputerUI) {
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

    m_TFBox= std::make_shared<TFBox>();
    m_TFBox->SetZIndex(53);
    m_TFBox->SetVisible(false);

    m_Player = Player;
}

void SettingUI::Start() {
    m_SettingBG->SetVisible(true);
    m_Arrow->SetVisible(true);
    m_Arrow->SetPosition({80, 250});
}

void SettingUI::Run() {
    if(m_TFBox->GetVisible()){
        if(m_TFBox->Choose()){
            if(m_TFBox->GetTF()){
                m_isSave = true;
            }
            m_TB->SetVisible(false);
            m_TFBox->SetVisible(false);
            m_TB->SetText("存檔成功!");
        }
    } else if (m_TB->GetVisibility()) {
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
                m_TFBox->SetVisible(true);
                m_TB->SetText("是否要覆蓋存檔?");
                m_TB->SetVisible(true);
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

    for(auto &i: m_TFBox->GetChildren()) {
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

void SettingUI::Save(const std::shared_ptr<Character> &player, const std::shared_ptr<Character> &Bromance,
                     const std::shared_ptr<ComputerUI> &ComputerUI, const std::shared_ptr<MapSystem> &mapSystem) {
    SavePokemons(RESOURCE_DIR"/Save/PokeBag.txt", player->GetPokemonBag()->GetPokemons());
    SavePokemons(RESOURCE_DIR"/Save/Computer.txt",ComputerUI->GetKeepPokemons());
    SavePokemons(RESOURCE_DIR"/Save/BromancePokeBag.txt", Bromance->GetPokemonBag()->GetPokemons());

    std::ofstream file(RESOURCE_DIR"/Save/Items.txt", std::ios::trunc);
    for(int i=0;i<256;i++){
        file<<(std::to_string(player->GetItemBag()->GetItemQuantity(i))+"\n");
    }
    file.close();

    file.open(RESOURCE_DIR"/Save/CharacterData.txt", std::ios::trunc);
    auto CurrentMap=mapSystem->GetCurrnetMap();
    auto CurrentPosition=mapSystem->GetPosition();
    mapSystem->SetMap("MainMap");
    auto MainPosition=mapSystem->GetPosition();
    mapSystem->SetMap(CurrentMap);
    file<<CurrentMap+"\n";
    file<<(std::to_string(CurrentPosition.x)+" ");
    file<<(std::to_string(CurrentPosition.y)+"\n");
    file<<(std::to_string(MainPosition.x)+" ");
    file<<(std::to_string(MainPosition.y)+"\n");
    file<<player->GetName()+"\n";
    file<<Bromance->GetName();
    file.close();
}

void SettingUI::Read(const std::shared_ptr<Character> &player, const std::shared_ptr<Character> &Bromance,
                     const std::shared_ptr<ComputerUI> &ComputerUI, const std::shared_ptr<MapSystem> &mapSystem) {
    player->GetPokemonBag()->SetPokemons(ReadPokemons(RESOURCE_DIR"/Save/PokeBag.txt"));
    ComputerUI->SetKeepPokemons(ReadPokemons(RESOURCE_DIR"/Save/Computer.txt"));
    Bromance->GetPokemonBag()->SetPokemons(ReadPokemons(RESOURCE_DIR"/Save/BromancePokeBag.txt"));

    std::ifstream file(RESOURCE_DIR"/Save/Items.txt", std::ios::in);
    std::string tempStr;
    for(int i=0;i<256;i++){
        std::getline(file,tempStr);
        player->GetItemBag()->AddItemQuantity(i,std::stoi(tempStr));
    }
    file.close();

    file.open(RESOURCE_DIR"/Save/CharacterData.txt", std::ios::in);


    std::getline(file,tempStr);
    mapSystem->SetMap(tempStr);
    auto CurrentMap=tempStr;

    std::getline(file,tempStr);
    mapSystem->SetPosition({std::stoi(tempStr.substr(0,tempStr.find(' '))),
                            std::stoi(tempStr.substr(tempStr.find(' '),tempStr.length()))});

    std::getline(file,tempStr);
    mapSystem->SetMap("MainMap");
    mapSystem->SetPosition({std::stoi(tempStr.substr(0,tempStr.find(' '))),
                            std::stoi(tempStr.substr(tempStr.find(' '),tempStr.length()))});
    mapSystem->SetMap(CurrentMap);

    std::getline(file,tempStr);
    player->SetName(tempStr);

    std::getline(file,tempStr);
    Bromance->SetName(tempStr);

    file.close();
}

bool SettingUI::IsSave() {
    return m_isSave;
}

void SettingUI::SavePokemons(const std::string &path, const std::vector<std::shared_ptr<Pokemon>> &pokemons) {
    std::ofstream file(path, std::ios::trunc);

    for(auto &i:pokemons){
        auto Ability=i->GetAbility();
        file<<(std::to_string(Ability["ID"])+"\n");
        file<<(std::to_string(Ability["IV"])+"\n");
        file<<(std::to_string(Ability["LV"])+"\n");
        file<<(std::to_string(Ability["AttackBP"])+"\n");
        file<<(std::to_string(Ability["DefenseBP"])+"\n");
        file<<(std::to_string(Ability["SpeedBP"])+"\n");
        file<<(std::to_string(Ability["SpecialBP"])+"\n");
        file<<(std::to_string(Ability["HPBP"])+"\n");
        file<<(std::to_string(Ability["CurrentHP"])+"\n");
        file<<(std::to_string(Ability["CurrentEXP"])+"\n");
        auto skills=i->GetSkill();
        auto PPs=i->GetCurrentSkillPP();
        for(int i=0;i<4;i++){
            if(i<skills.size()){
                file<<skills[i]+" "+PPs[i]+"\n";
            } else {
                file<<"\n";
            }
        }
    }
    file.close();
}

std::vector<std::shared_ptr<Pokemon>> SettingUI::ReadPokemons(const std::string &path) {
    std::ifstream file(path, std::ios::in);
    std::string tempStr;
    std::vector<std::string> data={"IV","LV","AttackBP","DefenseBP","SpeedBP","SpecialBP","HPBP","CurrentHP","CurrentEXP"};

    std::vector<std::shared_ptr<Pokemon>> pokemons;
    while(std::getline(file,tempStr)){
        std::map<std::string, int>  Abilit;
        Abilit.insert({"ID", std::stoi(tempStr)});
        for(auto &i:data){
            std::getline(file,tempStr);
            Abilit.insert({i, std::stoi(tempStr)});
        }
        std::vector<std::string> skills;
        std::vector<std::string> PPs;
        for(int i=0;i<4;i++){
            std::getline(file,tempStr);
            if(tempStr!=""){
                skills.push_back(tempStr.substr(0,tempStr.find(' ')));
                PPs.push_back(tempStr.substr(tempStr.find(' ')+1,tempStr.length()));
            }
        }


        int CurrentHP=Abilit["CurrentHP"];
        Abilit.insert({"HP", 0});
        Abilit.insert({"Attack", 0});
        Abilit.insert({"Defence", 0});
        Abilit.insert({"Special", 0});
        Abilit.insert({"Speed", 0});
        Abilit.insert({"EXP", 0});

        std::stringstream ToString;
        ToString << std::setw(3) << std::setfill('0') <<Abilit["ID"];
        std::string StringID = ToString.str();
        std::shared_ptr<Pokemon> pokemon=std::make_shared<Pokemon>(StringID);
        pokemon->SetAbility(Abilit);
        pokemon->SetCurrentHP(CurrentHP);
        pokemon->SetSkillByName(skills);
        for(int i=0;i<PPs.size();i++){
            int pp=std::stoi(PPs[i]);
            for(int j=pp;j<std::stoi(pokemon->GetSkillPP()[i]);j++){
                pokemon->ReducePP(i);
            }
        }
        pokemons.push_back(pokemon);
    }
    file.close();

    return pokemons;
}