#ifndef APP_HPP
#define APP_HPP

#include "pch.hpp" // IWYU pragma: export

#include "Util/Root.hpp"
#include "Object.hpp"
#include "TextBox.hpp"

class App {
public:
    enum class State {
        START,
        HOME,
        INIT,
        UPDATE,
        END,
    };

    State GetCurrentState() const { return m_CurrentState; }

    void Start();

    void Home();

    void Init();

    void Update();

    void End(); // NOLINT(readability-convert-member-functions-to-static)

private:
    void ValidTask();

private:
    State m_CurrentState = State::START;

    Util::Root m_Root;
    std::shared_ptr<Object> m_AnimatedText;
    std::shared_ptr<Object> m_BG;
    std::shared_ptr<TextBox> m_TB;
};

#endif
