#ifndef POKEMON_TEXTBOX_HPP
#define POKEMON_TEXTBOX_HPP

#include "Object.hpp"

#include "Util/GameObject.hpp"
#include "Util/Text.hpp"
#include "Util/Color.hpp"

class TextBox{
private:
    std::shared_ptr<Object> m_Text;
    std::shared_ptr<Object> m_BG;
    std::vector<std::string> m_AllText;
    size_t m_LineIndex;
public:
    TextBox();
    size_t GetLineIndex();
    std::string GetCurrentLine();
    [[nodiscard]] bool GetVisibility() const;
    void SetText(const std::string &str);
    void SetVisible(bool visible);
    void SetScale(const glm::vec2& scale);
    void SetPosition(const glm::vec2& Position);
    void ReadLines(const std::string &LinesPath);
    void Next();
    [[nodiscard]] std::vector<std::shared_ptr<Util::GameObject>> GetChildren() const;
};

#endif //POKEMON_TEXTBOX_HPP
