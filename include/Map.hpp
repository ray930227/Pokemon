#ifndef POKEMON_MAP_HPP
#define POKEMON_MAP_HPP

#include "Image.hpp"
#include "Block.hpp"
#include <fstream>

class Map{
private:
    std::shared_ptr<Image> m_BackGround;
    std::vector<std::vector<std::shared_ptr<Block>>> m_Blocks;

public:
    Map(const std::string& MapImagePath,const std::string& MapTxtPath);
    [[nodiscard]] std::vector<std::shared_ptr<Util::GameObject>> GetChildren() const;
    [[nodiscard]] const glm::vec2& GetPosition() const;
    glm::vec2 GetPlayerPosition();
    std::vector<std::vector<std::shared_ptr<Block>>> GetBlocks();
    void SetImage(const std::string &ImagePath);
    void SetPosition(const glm::vec2 &Position);
    void SetVisible(const bool visible);
    void Move(const glm::vec2& Displacement);
};

#endif //POKEMON_MAP_HPP
