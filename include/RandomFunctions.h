// RandomFunctions.h
#ifndef RANDOM_FUNCTIONS_H
#define RANDOM_FUNCTIONS_H

#include <cstdint>

class State {
public:
    uint32_t s[4];
};

float randRange(float value, float min, float max);
void InitRNGState(uint64_t seed, State& state_out);
float GenerateRandom(State& state);

#endif // RANDOM_FUNCTIONS_H