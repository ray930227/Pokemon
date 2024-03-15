#include "UsefulFunctions.hpp"

std::vector<std::string> useful::split(std::string &str, char interval) {
    std::vector<std::string> result;
    str.pop_back();
    str+=interval;
    size_t cur=0;
    while (cur<str.size()){
        result.push_back(str.substr(str.find(interval,cur)));
        cur=str.find(interval,cur)+1;
    }
    return result;
}

int useful::Getability(int ID, int option) {
    std::ifstream file(RESOURCE_DIR"/Pokemon/PokemonAbility.txt");
    int Value[151][5];
    for (int r = 0; r < 151; r++)
    {
        for (int c = 0; c < 5; c++)
        {
            file >> Value[r][c];
        }
    }
    file.close();
    return Value[ID-1][option];
}

std::string useful::Getname(int ID) {
    std::ifstream file(RESOURCE_DIR"/Pokemon/Name.txt");
    std::vector<std::string> Name;
    std::string text;
    while(file>>text){
        Name.push_back(text);
    }
    file.close();
    return Name[ID-1];
}