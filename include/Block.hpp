#ifndef POKEMON_BLOCK_HPP
#define POKEMON_BLOCK_HPP

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"

class Block:public Util::GameObject{
private:
    bool m_Traversable;
    bool m_Event;
    int m_eventID;
public:
    Block(bool traversable,bool event,int eventID);
    [[nodiscard]] bool GetVisibility() const;
    [[nodiscard]] const glm::vec2& GetPosition() const;
    [[nodiscard]] bool GetTraversable() const;
    [[nodiscard]] bool GetEvent() const;
    [[nodiscard]] int GetEventID() const;
    void SetImage(const std::string& ImagePath);
    void SetPosition(const glm::vec2& Position);
    void SetTraversable(bool traversable);
    void SetEvent(bool event);
};
#endif