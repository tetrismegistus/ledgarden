// ArtFunctions.cpp
#include "ArtFunctions.h"
#include <math.h>

void HSBtoRGB(float hue, float saturation, float brightness, int &r, int &g, int &b) {
    hue = std::fmod(hue, 360);
    saturation /= 100;
    brightness /= 100;

    float C = brightness * saturation;
    float X = C * (1 - std::fabs(fmod(hue / 60.0, 2) - 1));
    float m = brightness - C;
    float rPrime, gPrime, bPrime;

    if (hue >= 0 && hue < 60) {
        rPrime = C, gPrime = X, bPrime = 0;
    } else if (hue >= 60 && hue < 120) {
        rPrime = X, gPrime = C, bPrime = 0;
    } else if (hue >= 120 && hue < 180) {
        rPrime = 0, gPrime = C, bPrime = X;
    } else if (hue >= 180 && hue < 240) {
        rPrime = 0, gPrime = X, bPrime = C;
    } else if (hue >= 240 && hue < 300) {
        rPrime = X, gPrime = 0, bPrime = C;
    } else {
        rPrime = C, gPrime = 0, bPrime = X;
    }

    r = static_cast<int>((rPrime + m) * 255);
    g = static_cast<int>((gPrime + m) * 255);
    b = static_cast<int>((bPrime + m) * 255);
}


float mapFloat(float x, float in_start, float in_end, float out_start, float out_end) {
  return (x - in_start) * (out_end - out_start) / (in_end - in_start) + out_start;
}