#ifndef POKEMON_MAPSYSTEM_HPP
#define POKEMON_MAPSYSTEM_HPP

#include "Image.hpp"
#include "Block.hpp"
#include <fstream>
#include <map>

class MapSystem {
private:
    typedef struct Map {
        std::shared_ptr<Image> m_BackGround;
        std::vector<std::vector<std::shared_ptr<Block>>> m_Blocks;
    } s_Map;

    std::map<std::string, s_Map> m_Maps;

    std::string m_CurrentMapName;

public:
    MapSystem(const std::string &MapName);

    [[nodiscard]] std::vector<std::shared_ptr<Util::GameObject>> GetChildren() const;

    [[nodiscard]] const glm::vec2 &GetPosition();

    glm::vec2 GetPlayerPosition();

    std::vector<std::vector<std::shared_ptr<Block>>> &GetBlocks();

    std::string &GetCurrnetMap();

    int GetCurrentArea();

    void SetImage(const std::string &ImagePath);

    void SetPosition(const glm::vec2 &Position);

    void SetVisible(const bool visible);

    void SetMap(const std::string &Path);

    void Move(const glm::vec2 &Displacement);
};

#endif //POKEMON_MAPSYSTEM_HPP
