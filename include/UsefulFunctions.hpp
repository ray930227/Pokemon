#ifndef POKEMON_USEFULFUNCTIONS_HPP
#define POKEMON_USEFULFUNCTIONS_HPP

#include <vector>
#include <string>
#include <fstream>

namespace useful {
    std::vector<std::string> split(std::string& str,char interval);
    int Getability(int ID,int option);//option 0:HP 1:Attack 2:defense 3:special 4:speed
    std::string Getname(int ID);
}
#endif //POKEMON_USEFULFUNCTIONS_HPP
