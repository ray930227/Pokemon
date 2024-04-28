#include "EventManager.hpp"


EventManager::EventManager() {
    std::ifstream fileArea(RESOURCE_DIR"/Map/area", std::ios::in);
    std::string tempStr;
    while (std::getline(fileArea, tempStr)) {
        std::vector<int> tempVector;
        for (size_t i = 0; i < tempStr.size(); i += 2) {
            tempVector.push_back(tempStr[i] - '0');
        }
        m_Area.push_back(tempVector);
    }

    fileArea.close();
}