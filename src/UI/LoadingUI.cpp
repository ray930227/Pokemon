#include "UI/LoadingUI.hpp"


LoadingUI::LoadingUI() {
    m_TextBox = std::make_shared<TextBox>();
    m_TextBox->SetVisible(false);
    std::vector<std::shared_ptr<Image>> Loading_1;
    Loading_1.push_back(std::make_shared<Image>(RESOURCE_DIR"/Fight/LoadingImage/Loading1_1.png"));
    Loading_1.push_back(std::make_shared<Image>(RESOURCE_DIR"/Fight/LoadingImage/Loading1_2.png"));
    m_LoadingImages.push_back(Loading_1);
    m_LoadingImages[0][0]->SetPosition({-720, 0});
    m_LoadingImages[0][1]->SetPosition({720, 0});
    m_LoadingImages[0][0]->SetVisible(false);
    m_LoadingImages[0][1]->SetVisible(false);
    m_LoadingImages[0][0]->SetZIndex(100);
    m_LoadingImages[0][1]->SetZIndex(100);
}

void LoadingUI::RandomMode() {
    m_Mode = 0;
    m_LoadingImages[0][0]->SetVisible(true);
    m_LoadingImages[0][1]->SetVisible(true);
}

std::vector<std::vector<std::shared_ptr<Util::GameObject>>> LoadingUI::GetChildren() const {
    std::vector<std::vector<std::shared_ptr<Util::GameObject>>> Result;
    for (const auto &m_LoadingImage: m_LoadingImages) {
        std::vector<std::shared_ptr<Util::GameObject>> temp;
        temp.push_back(m_LoadingImage[0]);
        temp.push_back(m_LoadingImage[1]);
        Result.push_back(temp);
    }
    Result.push_back(m_TextBox->GetChildren());
    return Result;
}

void LoadingUI::StartLoading() {
    switch (m_Mode) {
        case 0:
            if (m_LoadingImages[0][0]->GetPosition().x != 720 && m_LoadingImages[0][0]->GetVisibility()) {
                m_LoadingImages[0][0]->Move({15, 0});
                m_LoadingImages[0][1]->Move({-15, 0});
            } else {
                m_LoadingImages[0][0]->SetPosition({-720, 0});
                m_LoadingImages[0][1]->SetPosition({720, 0});
                m_LoadingImages[0][0]->SetVisible(false);
                m_LoadingImages[0][1]->SetVisible(false);
            }
            break;
    }
}

bool LoadingUI::GetVisibility() {
    if (m_Mode == 0) {
        return m_LoadingImages[0][0]->GetVisibility();
    }
    return false;
}

void LoadingUI::LoadText(const std::string &MyPokeName, const std::string &EnemyPokeName) {
    m_TextBox->SetVisible(true);
    m_TextBox->Reload();
    m_TextBox->AddText(" ");
    m_TextBox->AddText("野生" + EnemyPokeName + "出現了!");
    m_TextBox->AddText("上吧! " + MyPokeName + "!");
}

void LoadingUI::Next() {
    m_TextBox->Next();
}

size_t LoadingUI::GetCurrentIndex() {
    return m_TextBox->GetLineIndex();
}

bool LoadingUI::GetTBVisibility() {
    return m_TextBox->GetVisibility();
}