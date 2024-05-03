#ifndef POKEMON_TEXTBOX_HPP
#define POKEMON_TEXTBOX_HPP

#include "Image.hpp"
#include "Text.hpp"

class TextBox {
private:
    std::shared_ptr<Text> m_Text;
    std::shared_ptr<Image> m_BG;
    std::vector<std::string> m_AllText;
    size_t m_LineIndex;
public:
    TextBox();

    size_t GetLineIndex();

    std::string GetCurrentLine();

    std::string GetText();

    [[nodiscard]] bool GetVisibility() const;

    [[nodiscard]] std::vector<std::shared_ptr<Util::GameObject>> GetChildren() const;

    void SetText(const std::string &str);

    void SetVisible(bool visible);

    void SetScale(const glm::vec2 &scale);

    void SetPosition(const glm::vec2 &Position);

    void ReadLines(const std::string &LinesPath);

    void ReadLines(std::vector<std::string> &Lines);

    void Next();

    void InputString();
};

#endif //POKEMON_TEXTBOX_HPP
