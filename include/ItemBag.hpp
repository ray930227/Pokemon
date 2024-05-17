#ifndef POKEMON_ITEMBAG_HPP
#define POKEMON_ITEMBAG_HPP

#include <vector>
#include <string>
#include "UsefulFunctions.hpp"

class ItemBag {
private:
    std::vector<std::pair<std::string, int>> m_Items;
public:
    ItemBag();

    void AddItemQuantity(size_t ID, int quantity);

    void AddItemQuantity(const std::string &name, int quantity);

    void SetItemQuantity(size_t ID, int quantity);

    void SetItemQuantity(const std::string &name, int quantity);

    int GetItemQuantity(size_t ID);

    int GetItemQuantity(const std::string &name);
};

#endif //POKEMON_ITEMBAG_HPP
