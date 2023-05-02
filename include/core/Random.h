//
// Created by dirii on 01/05/2023.
//

#ifndef VISUALGO_CS162_RANDOM_H
#define VISUALGO_CS162_RANDOM_H

#include <random>

namespace Random{
    static std::mt19937 rng(std::random_device{}());
    static int randomInt(int min, int max){
        std::uniform_int_distribution<int> dist(min, max);
        return dist(rng);
    }
}

#endif //VISUALGO_CS162_RANDOM_H
