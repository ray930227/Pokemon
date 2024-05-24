#include "SFXSystem.hpp"
#include "Util/Logger.hpp"

SFXSystem::SFXSystem() {
    auto paths = std::filesystem::directory_iterator(RESOURCE_DIR"/SoundEffect");
    for (const auto &path: paths) {
        std::string SFXName = path.path().string().replace(0, std::string(RESOURCE_DIR"/SoundEffect").size() + 1, "");
        SFXName.replace(SFXName.find(".mp3"), SFXName.find(".mp3") + 3, "");
        std::pair<std::string, std::shared_ptr<Util::SFX>> tempPair;
        tempPair.first = SFXName;
        tempPair.second = std::make_shared<Util::SFX>(RESOURCE_DIR"/SoundEffect/" + SFXName + ".mp3");
        m_SFXs.insert(tempPair);
    }
}

void SFXSystem::Play(const std::string &SFXName) {
    m_SFXs[SFXName]->SetVolume(50);
    m_SFXs[SFXName]->Play();
}