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