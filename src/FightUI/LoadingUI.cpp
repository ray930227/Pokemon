#include "FightUI/LoadingUI.hpp"


LoadingUI::LoadingUI() {
    std::vector<std::shared_ptr<Image>> Loading_1;
    Loading_1.push_back(std::make_shared<Image>(RESOURCE_DIR"/Fight/LoadingImage/Loading1_1.png"));
    Loading_1.push_back(std::make_shared<Image>(RESOURCE_DIR"/Fight/LoadingImage/Loading1_2.png"));
    m_LoadingImages.push_back(Loading_1);
}

std::vector<std::vector<std::shared_ptr<Util::GameObject>>> LoadingUI::GetChildren() const {
    std::vector<std::vector<std::shared_ptr<Util::GameObject>>> Result;
    for (const auto &m_LoadingImage: m_LoadingImages) {
        std::vector<std::shared_ptr<Util::GameObject>> temp;
        temp.push_back(m_LoadingImage[0]);
        temp.push_back(m_LoadingImage[1]);
        Result.push_back(temp);
    }
    return Result;
}

