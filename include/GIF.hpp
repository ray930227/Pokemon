#ifndef POKEMON_GIF_HPP
#define POKEMON_GIF_HPP

#include "Util/GameObject.hpp"
#include "Util/Animation.hpp"

class GIF:public Util::GameObject{
private:

public:
    GIF(const std::vector<std::string>& ImagePaths);
    [[nodiscard]] bool IsLooping() const;
    [[nodiscard]] bool IsPlaying() const;
    [[nodiscard]] bool IsAnimationEnds() const;
    std::size_t GetFrameCount() const;
    void SetPosition(const glm::vec2& Position);
    void SetInterval(int interval);
    void SetLooping(bool looping);
    void Play();
};

#endif //POKEMON_GIF_HPP
