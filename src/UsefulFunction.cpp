#include "UsefulFunctions.hpp"

std::vector<std::string> useful::Split(std::string &str, char interval) {
    std::vector<std::string> result;
    str.pop_back();
    str += interval;
    size_t cur = 0;
    while (cur < str.size()) {
        result.push_back(str.substr(str.find(interval, cur)));
        cur = str.find(interval, cur) + 1;
    }
    return result;
}

int PokeFunction::FindIndex(std::string MyType) {
    std::vector<std::string> Type = {"一般", "格鬥", "飛行", "毒", "地面", "岩石", "蟲", "幽靈","鋼","火", "水", "草", "電",
                                     "超能力", "冰", "龍", "惡", "妖精"};
    for (size_t i = 0; i < Type.size(); i++) {
        if (Type[i] == MyType) {
            return i;
        }
    }
    return -1;
}

float PokeFunction::TypeDamage(std::string MyType, std::vector<std::string> EnemyType) {
    float FinalBouns = 1.0;
    float DamageBonus[18][18] = {{1, 1,   1,   1,   1,   0.5, 1,   0,   0.5, 1,   1,   1,   1,   1,   1,   1,   1,   1},
                                 {2, 1,   0.5, 0.5, 1,   2,   0.5, 0,   2,   1,   1,   1,   1,   0.5, 2,   1,   2,   0.5},
                                 {1, 2,   1,   1,   1,   0.5, 2,   1,   0.5, 1,   1,   2,   0.5, 1,   1,   1,   1,   1},
                                 {1, 1,   1,   0.5, 0.5, 0.5, 2,   0.5, 0,   1,   1,   2,   1,   1,   1,   1,   1,   2},
                                 {1, 1,   0,   2,   1,   2,   0.5, 1,   2,   2,   1,   0.5, 2,   1,   1,   1,   1,   1},
                                 {1, 0.5, 2,   1,   0.5, 1,   2,   1,   0.5, 2,   1,   1,   1,   1,   2,   1,   1,   1},
                                 {1, 0.5, 0.5, 2,   1,   1,   1,   0.5, 0.5, 0.5, 1,   2,   1,   2,   1,   1,   2,   0.5},
                                 {0, 1,   1,   1,   1,   1,   1,   2,   1,   1,   1,   1,   1,   0,   1,   1,   0.5, 1},
                                 {1, 1,   1,   1,   1,   2,   1,   1,   0.5, 0.5, 0.5, 1,   0.5, 1,   2,   1,   1,   2},
                                 {1, 1,   1,   1,   1,   0.5, 2,   1,   2,   0.5, 0.5, 2,   1,   1,   2,   0.5, 1,   1},
                                 {1, 1,   1,   1,   2,   2,   1,   1,   1,   2,   0.5, 0.5, 1,   1,   1,   0.5, 1,   1},
                                 {1, 1,   0.5, 0.5, 2,   2,   0.5, 1,   0.5, 0.5, 2,   0.5, 1,   1,   1,   0.5, 1,   1},
                                 {1, 1,   2,   1,   0,   1,   1,   1,   1,   1,   2,   0.5, 0.5, 1,   1,   0.5, 1,   1},
                                 {1, 2,   1,   2,   1,   1,   1,   1,   0.5, 1,   1,   1,   1,   0.5, 1,   1,   0,   1},
                                 {1, 1,   2,   1,   2,   1,   1,   1,   0.5, 1,   0.5, 2,   1,   1,   0.5, 2,   1,   1},
                                 {1, 1,   1,   1,   1,   1,   1,   1,   0.5, 1,   1,   1,   1,   1,   1,   2,   1,   0},
                                 {1, 0.5, 1,   1,   1,   1,   1,   2,   1,   1,   1,   1,   1,   2,   1,   1,   0.5, 0.5},
                                 {1, 2,   1,   0.5, 1,   1,   1,   1,   0.5, 0.5, 1,   1,   1,   1,   1,   2,   2,   1}};
    for (auto type: EnemyType) {
        FinalBouns *= DamageBonus[FindIndex(MyType)][FindIndex(type)];
    }

    return FinalBouns;
}