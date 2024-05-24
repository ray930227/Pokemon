#ifndef POKEMON_TFBOX_HPP
#define POKEMON_TFBOX_HPP

#include <memory>
#include "Image.hpp"
#include "Util/Input.hpp"

class TFBox : public Util::GameObject {
private:
    std::shared_ptr<Image> m_Box;
    std::shared_ptr<Image> m_Arrow;
public:
    TFBox();

    [[nodiscard]] bool GetVisibility() const;

    [[nodiscard]] const glm::vec2 &GetPosition() const;

    [[nodiscard]] std::vector<std::shared_ptr<Util::GameObject>> GetChildren() const;

    bool GetTF();

    void SetVisibility(const bool visible);

    void SetPosition(const glm::vec2 &Position);

    bool Choose();
};

#endif //POKEMON_TFBOX_HPP
