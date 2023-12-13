// ArtFunctions.h
#ifndef ART_FUNCTIONS_H
#define ART_FUNCTIONS_H

#include <cstdint>

void HSBtoRGB(float hue, float saturation, float brightness, int &r, int &g, int &b);    
float mapFloat(float x, float in_start, float in_end, float out_start, float out_end);
  
#endif // ART_FUNCTIONS_H