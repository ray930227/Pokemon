#include "MapSystem.hpp"
#include <filesystem>

MapSystem::MapSystem(const std::string &MapName) {
    auto paths = std::filesystem::directory_iterator(RESOURCE_DIR"/Map");


    for (auto path: paths) {
        s_Map tempMap;
        std::string Path = path.path().string().replace(0, std::string(RESOURCE_DIR"/Map").size() + 1, "");
        LOG_DEBUG("LOAD {}'s map file", Path);
        tempMap.m_BackGround = std::make_shared<Image>(RESOURCE_DIR"/Map/" + Path + "/map.png");
        std::ifstream fileBlock(RESOURCE_DIR"/Map/" + Path + "/blocks.txt", std::ios::in);
        std::ifstream fileEvent(RESOURCE_DIR"/Map/" + Path + "/event.txt", std::ios::in);
        std::string tempStr1, tempStr2;
        int y = 0;
        while (std::getline(fileBlock, tempStr1) && std::getline(fileEvent, tempStr2)) {
            std::vector<std::shared_ptr<Block>> tempBlocks;
            std::vector<std::shared_ptr<Block>> tempShowBlocks;
            for (size_t i = 0; i < tempStr1.size(); i += 2) {
                std::shared_ptr<Block> tempBlock = std::make_shared<Block>((tempStr1[i] - '0') % 2 == 0,
                                                                           (tempStr1[i] - '0') / 2 % 2 == 1,
                                                                           tempStr2[i] - '0');

                tempBlock->SetVisible(false);
                tempBlock->SetZIndex(1);
                tempBlock->SetPosition({i / 2 * 72, y * 72});
                tempBlocks.push_back(tempBlock);
            }
            tempMap.m_Blocks.push_back(tempBlocks);
            y++;
        }
        fileBlock.close();
        fileEvent.close();

        auto &blocks = tempMap.m_Blocks;
        for (size_t i = 0; i < blocks.size(); i++) {
            for (size_t j = 0; j < blocks[i].size(); j++) {
                if (blocks[i][j]->isDisplayable()) {
                    blocks[i][j]->SetZIndex(1);
                    blocks[i][j]->SetVisible(false);
                    blocks[i][j]->SetPosition(
                            {(j - blocks[i].size() / 2) * 72 + 36, (blocks.size() / 2 - i) * 72 - 36});
                }
            }
        }

        tempMap.m_BackGround = std::make_shared<Image>(RESOURCE_DIR"/Map/" + Path + "/map.png");
        tempMap.m_BackGround->SetZIndex(0);
        tempMap.m_BackGround->SetVisible(false);
        m_Maps.insert(std::pair<std::string, s_Map>(Path, tempMap));
    }
    m_CurrentMapName = MapName;
    m_Maps[m_CurrentMapName].m_BackGround->SetVisible(true);
}

std::vector<std::shared_ptr<Util::GameObject>> MapSystem::GetChildren() const {
    std::vector<std::shared_ptr<Util::GameObject>> result;

    for (auto &i: m_Maps) {
        result.push_back(i.second.m_BackGround);
        for (auto &j: i.second.m_Blocks) {
            for (auto &block: j) {
                if (block->isDisplayable())
                    result.push_back(block);
            }
        }
    }
    return result;
}

const glm::vec2 &MapSystem::GetPosition() {
    return m_Maps[m_CurrentMapName].m_BackGround->GetPosition();
}

glm::vec2 MapSystem::GetPlayerPosition() {
    glm::vec2 MapSize = {m_Maps[m_CurrentMapName].m_Blocks.size(), m_Maps[m_CurrentMapName].m_Blocks[0].size()};
    return {MapSize.y / 2 + (GetPosition().y / 72), MapSize.x / 2 - (GetPosition().x / 72)};
}

std::vector<std::vector<std::shared_ptr<Block>>> &MapSystem::GetBlocks() {
    return m_Maps[m_CurrentMapName].m_Blocks;
}

std::string &MapSystem::GetCurrnetMap() {
    return m_CurrentMapName;
}

void MapSystem::SetImage(const std::string &ImagePath) {
    m_Maps[m_CurrentMapName].m_BackGround->SetImage(ImagePath);
}

void MapSystem::SetPosition(const glm::vec2 &Position) {
    glm::vec2 offset = Position - m_Maps[m_CurrentMapName].m_BackGround->GetPosition();
    m_Maps[m_CurrentMapName].m_BackGround->SetPosition(Position);
    auto &blocks = m_Maps[m_CurrentMapName].m_Blocks;
    for (size_t i = 0; i < blocks.size(); i++) {
        for (size_t j = 0; j < blocks[i].size(); j++) {
            if (blocks[i][j]->isDisplayable())
                blocks[i][j]->SetPosition(blocks[i][j]->GetPosition() + offset);
        }
    }
}

void MapSystem::SetVisible(const bool visible) {
    m_Maps[m_CurrentMapName].m_BackGround->SetVisible(visible);
    for (auto &i: m_Maps[m_CurrentMapName].m_Blocks) {
        for (auto &j: i) {
            if (j->isDisplayable())
                j->SetVisible(visible);
        }
    }
}

void MapSystem::SetMap(const std::string &MapName) {
    SetVisible(false);
    m_CurrentMapName = MapName;
    SetVisible(true);
}

void MapSystem::Move(const glm::vec2 &Displacement) {
    m_Maps[m_CurrentMapName].m_BackGround->Move(Displacement);
    auto &blocks = m_Maps[m_CurrentMapName].m_Blocks;
    for (size_t i = 0; i < blocks.size(); i++) {
        for (size_t j = 0; j < blocks[i].size(); j++) {
            if (blocks[i][j]->isDisplayable())
                blocks[i][j]->SetPosition(blocks[i][j]->GetPosition() + Displacement);
        }
    }
}