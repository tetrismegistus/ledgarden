// RandomFunctions.cpp
#include "RandomFunctions.h"

float randRange(float value, float min, float max) {
    return value * (max - min) + min;
}

void InitRNGState(uint64_t seed, State& state_out) {
    state_out.s[0] = seed & 0xFFFFFFFF;
    state_out.s[1] = (seed >> 32) & 0xFFFFFFFF;
    state_out.s[2] = 42;
    state_out.s[3] = seed * 12345 & 0xFFFFFFFF;
}

static inline uint32_t rotl(const uint32_t x, int k) {
    return (x << k) | (x >> (32 - k));
}

float GenerateRandom(State& state) {
    const uint32_t result = state.s[0] + state.s[3];

    const uint32_t t = state.s[1] << 9;

    state.s[2] ^= state.s[0];
    state.s[3] ^= state.s[1];
    state.s[1] ^= state.s[2];
    state.s[0] ^= state.s[3];

    state.s[2] ^= t;

    state.s[3] = rotl(state.s[3], 11);

    float x = (float)state.s[0] / 4294967296.0f;
    return x;
}
