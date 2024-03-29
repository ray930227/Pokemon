#ifndef POKEMON_GIF_HPP
#define POKEMON_GIF_HPP

#include "Util/GameObject.hpp"
#include "Util/Animation.hpp"

class GIF : public Util::GameObject {
private:
    int m_Interval;
    bool m_Loop;
public:
    GIF(const std::vector<std::string> &ImagePaths);

    [[nodiscard]] bool IsLooping() const;

    [[nodiscard]] bool IsPlaying() const;

    [[nodiscard]] bool IsAnimationEnds() const;

    [[nodiscard]] std::size_t GetFrameCount() const;

    [[nodiscard]] std::size_t GetCurrentFrameIndex() const;

    const glm::vec2 &GetPosition() const;

    void SetPosition(const glm::vec2 &Position);

    void SetInterval(int interval);

    void SetLooping(bool looping);

    void SetImagePaths(const std::vector<std::string> &ImagePaths);

    void SetCurrentFrame(std::size_t index);

    void SetScale(const glm::vec2 &scale);

    void Play();

    void Pause();

    void Reset();

    void Move(const glm::vec2 &Displacement);
};

#endif //POKEMON_GIF_HPP
