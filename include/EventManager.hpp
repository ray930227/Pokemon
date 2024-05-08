#ifndef POKEMON_EVENTMANAGER_HPP
#define POKEMON_EVENTMANAGER_HPP

#include <fstream>
#include <vector>
#include <memory>

class EventManager {
private:
    std::vector<std::vector<int>> m_Area;
    bool choosePokemon = false;
public:
    EventManager();
};

#endif //POKEMON_EVENTMANAGER_HPP
