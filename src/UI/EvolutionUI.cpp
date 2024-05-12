#include "UI/EvolutionUI.hpp"

EvolutionUI::EvolutionUI() {
    std::vector<std::string> temp;
    temp.emplace_back(RESOURCE_DIR"/Pokemon/Pokedex/transparent.png");
    m_PokemonGIF = std::make_shared<GIF>(temp);
    m_PokemonGIF->SetPosition({0, 100});
    m_PokemonGIF->SetZIndex(55);
    m_PokemonGIF->SetInterval(401);
    m_PokemonGIF->SetLooping(true);
    m_PokemonGIF->SetVisible(false);
    m_Interval = 401;
    m_BG = std::make_shared<Image>(RESOURCE_DIR"/Background/WhiteBG.png");
    m_BG->SetZIndex(54);
    m_BG->SetVisible(false);
    m_TextBox = std::make_shared<TextBox>();
    m_TextBox->SetVisible(false);
}

std::vector<std::shared_ptr<Util::GameObject>> EvolutionUI::GetChildren() const {
    return {m_PokemonGIF, m_BG, m_TextBox->GetChildren()[0], m_TextBox->GetChildren()[1]};
}

void EvolutionUI::Setting(int PokemonID) {
    m_Name.clear();
    std::stringstream ToString1;
    std::stringstream ToString2;
    ToString1 << std::setw(3) << std::setfill('0') << PokemonID;
    ToString2 << std::setw(3) << std::setfill('0') << PokemonID + 1;
    std::string StringID1 = ToString1.str();
    std::string StringID2 = ToString2.str();
    m_PokemonGIF->SetImagePaths({RESOURCE_DIR"/Pokemon/PokeImage/Pokemonfront" + StringID1 + ".png",
                                 RESOURCE_DIR"/Pokemon/PokeImage/Pokemonfront" + StringID2 + ".png"});
    std::ifstream file(RESOURCE_DIR"/Pokemon/Name.txt");
    std::vector<std::string> Name;
    std::string text;
    while (file >> text) {
        Name.push_back(text);
    }
    file.close();
    m_Name.push_back(Name[PokemonID - 1]);
    m_Name.push_back(Name[PokemonID]);
    m_TextBox->Reload();
    m_TextBox->AddText("什麼! " + m_Name[0] + "正在進化!");
    m_TextBox->AddText(m_Name[0] + "進化成了" + m_Name[1]);
}

void EvolutionUI::SetVisible(bool visible) {
    m_PokemonGIF->SetVisible(visible);
    m_TextBox->SetVisible(visible);
    m_BG->SetVisible(visible);

}

void EvolutionUI::SetPokeVisible(bool visible) {
    m_PokemonGIF->SetVisible(visible);
}

void EvolutionUI::SetInterval(int interval) {
    m_Interval = interval;
    m_PokemonGIF->SetInterval(interval);
}

int EvolutionUI::GetTextIndex() {
    return m_TextBox->GetLineIndex();
}

void EvolutionUI::Play() {
    m_PokemonGIF->Play();
}

void EvolutionUI::Pause() {
    m_PokemonGIF->Pause();
}

void EvolutionUI::Next() {
    m_TextBox->Next();
}

void EvolutionUI::StopEvolution() {
    m_TextBox->SetText(m_Name[0] + "中斷了進化!");

}

bool EvolutionUI::GetVisibility() const {
    m_TextBox->GetVisibility();
}

int EvolutionUI::GetInterval() {
    return m_Interval;
}

void EvolutionUI::SetCurrentFrame(size_t index) {
    m_PokemonGIF->SetCurrentFrame(index);
}

