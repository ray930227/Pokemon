#ifndef POKEMON_COMPUTERUI_HPP
#define POKEMON_COMPUTERUI_HPP

#include <memory>
#include "Image.hpp"
#include "TextBox.hpp"
#include "TFBox.hpp"
#include "Character.hpp"
#include "Util/Input.hpp"

class ComputerUI {
private:
    std::shared_ptr<Image> m_ComputerBG;
    std::shared_ptr<Image> m_ComputerInsideBG;
    std::vector<std::shared_ptr<Image>> m_Arrows;
    std::shared_ptr<TextBox> m_TB;
    std::shared_ptr<Character> m_Player;
    std::vector<std::shared_ptr<Pokemon>> m_ComputerPokemons;
    std::vector<std::shared_ptr<Text>> m_Texts;
    std::shared_ptr<TFBox> m_TFBox;
    int m_RowTopIndex;
public:
    ComputerUI(const std::shared_ptr<Character> &Player);

    void Start();

    void Run();

    std::vector<std::shared_ptr<Util::GameObject>> GetChildren();

    bool GetVisibile();

    std::vector<std::shared_ptr<Pokemon>> GetKeepPokemons();

    void Keep(const std::shared_ptr<Pokemon> &Poke);

    void SetKeepPokemons(std::vector<std::shared_ptr<Pokemon>> Pokemons);
protected:
    void ChooseAction();

    void ChoosePokemon();

    void Updata();

    void Action();
};


#endif //POKEMON_COMPUTERUI_HPP
