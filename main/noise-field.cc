// -*- mode: c++; c-basic-offset: 2; indent-tabs-mode: nil; -*-
// Small example how to use the library.
// For more examples, look at demo-main.cc
//
// This code is public domain
// (but note, that the led-matrix library this depends on is GPL v2)

#include "led-matrix.h"
#include "OpenSimplexNoise.h"
#include "ArtFunctions.h"

#include <stdio.h>
#include <signal.h>

using rgb_matrix::RGBMatrix;
using rgb_matrix::Canvas;


volatile bool interrupt_received = false;
static void InterruptHandler(int signo) {
  interrupt_received = true;

}


static void DrawOnCanvas(Canvas *canvas, OpenSimplexNoise::Noise& noise, int z) {
  for (int x = 0; x < canvas->width(); x++) {
    for (int y = 0; y < canvas->height(); y++) {
      double value = noise.eval((static_cast<double>(x) * .01), 
                                (static_cast<double>(y) * .01),
				(static_cast<double>(z) * .015));
      int hue = static_cast<int>(mapFloat(value, -1, 1, 0, 360));
      int r,g,b;
      HSBtoRGB(hue, 100, 100, r, g, b);
      canvas->SetPixel(x, y, r, g, b);
    }
  }
}


int main(int argc, char *argv[]) {
  RGBMatrix::Options defaults;
  
  defaults.hardware_mapping = "adafruit-hat";
  defaults.rows = 64;
  defaults.cols = 64;
  defaults.chain_length = 1;
  defaults.parallel = 1;
  defaults.show_refresh_rate = true;
  
  Canvas *canvas = RGBMatrix::CreateFromFlags(&argc, &argv, &defaults);
  OpenSimplexNoise::Noise noise;
  
  int z = 0;  // noise z coord
  
  if (canvas == NULL)
    return 1;

  signal(SIGTERM, InterruptHandler);
  signal(SIGINT, InterruptHandler);
  
  while (true) {
    DrawOnCanvas(canvas, noise, z);    
    usleep(1 * 15000);
    z++;
    if (interrupt_received){
      break;
    }
  }

  
  canvas->Clear();
  delete canvas;

  return 0;
}
