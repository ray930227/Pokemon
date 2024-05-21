#ifndef POKEMON_SFXSYSTEM_HPP
#define POKEMON_SFXSYSTEM_HPP

#include "Util/SFX.hpp"
#include <map>
#include <string>
#include <filesystem>

class SFXSystem{
private:
    std::map<std::string,std::shared_ptr<Util::SFX>> m_SFXs;
public:
    SFXSystem();

    void Play(const std::string& SFXName);
};

#endif //POKEMON_SFXSYSTEM_HPP
