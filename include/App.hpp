#ifndef APP_HPP
#define APP_HPP

#include "pch.hpp" // IWYU pragma: export

#include "Util/Root.hpp"
#include "TextBox.hpp"
#include "Image.hpp"
#include "GIF.hpp"
#include "Character.hpp"

class App {
public:
    enum class State {
        START,
        HOME,
        INIT,
        UPDATE,
        FIGHT,
        END,
    };

    State GetCurrentState() const { return m_CurrentState; }
    void Start();
    void Home();
    void Init();
    void Update();
    void Fight();
    void End();

private:
    void ValidTask();

private:
    State m_CurrentState = State::START;

    Util::Root m_Root;
    std::shared_ptr<GIF> m_AnimatedText;
    std::shared_ptr<Image> m_BG;
    std::shared_ptr<TextBox> m_TB;
    std::shared_ptr<Character> Player;
    std::shared_ptr<Character> NPC_Bromance;
    std::shared_ptr<TextBox> tempBox;
    glm::vec2 Displacement = {0, 0};
    int DisplacementCount;
};

#endif
