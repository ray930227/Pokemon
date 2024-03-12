#include "Map.hpp"

Map::Map(const std::string& Path) {
    m_BackGround=std::make_shared<Image>(Path+"/map.png");
    m_BackGround->SetZIndex(0);

    std::ifstream fileBlock(Path+"/blocks.txt", std::ios::in);
    std::ifstream fileEvent(Path+"/event.txt", std::ios::in);
    std::string tempStr1,tempStr2;
    while (std::getline(fileBlock, tempStr1) && std::getline(fileEvent, tempStr2)) {
        std::vector<std::shared_ptr<Block>> tempBlocks;
        for(size_t i=0;i<tempStr1.size();i+=2){
            std::shared_ptr<Block> tempBlock=std::make_shared<Block>((tempStr1[i]-'0')%2==0,
                                                                     (tempStr1[i]-'0')/2%2==1,
                                                                     tempStr2[i]-'0');
            tempBlocks.push_back(tempBlock);
        }
        m_Blocks.push_back(tempBlocks);
    }
    fileBlock.close();
}

std::vector<std::shared_ptr<Util::GameObject>> Map::GetChildren() const {
//    std::vector<std::shared_ptr<Util::GameObject>> result;
//    result.push_back(m_BackGround);
//    for(auto& i:m_Blocks){
//        for(auto& j:i){
//            j->SetVisible(false);
//            result.push_back(j);
//        }
//    }
//    return result;
    return {m_BackGround};
}

const glm::vec2 &Map::GetPosition() const {
    return m_BackGround->GetPosition();
}

glm::vec2 Map::GetPlayerPosition() {
    glm::vec2 MapSize={m_Blocks.size(),m_Blocks[0].size()};
    return {MapSize.y/2+(GetPosition().y/72),MapSize.x/2-(GetPosition().x/72)};
}

std::vector<std::vector<std::shared_ptr<Block>>> &Map::GetBlocks() {
    return m_Blocks;
}

void Map::SetImage(const std::string &ImagePath) {
    m_BackGround->SetImage(ImagePath);
}

void Map::SetPosition(const glm::vec2 &Position) {
    m_BackGround->SetPosition(Position);
}

void Map::SetVisible(const bool visible) {
    m_BackGround->SetVisible(visible);
}

void Map::Move(const glm::vec2 &Displacement) {
    m_BackGround->Move(Displacement);
}