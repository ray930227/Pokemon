
#include "FightUI/EvolutionUI.hpp"

EvolutionUI::EvolutionUI() {
    std::vector<std::string> tempBallPath;
    m_PokemonGIF=std::make_shared<GIF>(tempBallPath);
    m_TextBox=std::make_shared<TextBox>();
}

std::vector<std::shared_ptr<Util::GameObject>> EvolutionUI::GetChildren() const {
    std::vector<std::shared_ptr<Util::GameObject>> temp;
    return {m_PokemonGIF,m_TextBox};
}

void EvolutionUI::Setting(int PokemonID) {
    std::stringstream ToString1;
    std::stringstream ToString2;
    ToString1 << std::setw(3) << std::setfill('0') << PokemonID-1;
    ToString1 << std::setw(3) << std::setfill('0') << PokemonID;
    std::string StringID1 = ToString1.str();
    std::string StringID2 = ToString2.str();
    m_PokemonGIF->SetImagePaths({RESOURCE_DIR"/Pokemon/PokeImage/Pokemonfront"+StringID1+ ".png",
                                 RESOURCE_DIR"/Pokemon/PokeImage/Pokemonfront"+StringID2+ ".png"});
    std::ifstream file(RESOURCE_DIR"/Pokemon/Name.txt");
    std::vector<std::string> Name;
    std::string text;
    while (file >> text) {
        Name.push_back(text);
    }
    file.close();
//    m_Name = Name[PokemonID - 1];
//    m_TextBox->Reload();
//    m_TextBox->AddText("什麼! ");
}
