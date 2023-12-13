// -*- mode: c++; c-basic-offset: 2; indent-tabs-mode: nil; -*-
// Small example how to use the library.
// For more examples, look at demo-main.cc
//
// This code is public domain
// (but note, that the led-matrix library this depends on is GPL v2)

#include "led-matrix.h"
#include "ArtFunctions.h"

#include <stdio.h>
#include <signal.h>

using rgb_matrix::RGBMatrix;
using rgb_matrix::Canvas;


volatile bool interrupt_received = false;
static void InterruptHandler(int signo) {
  interrupt_received = true;
}


static void DrawOnCanvas(Canvas *canvas, int modVal) {
  for (int x = 0; x < canvas->width(); x++) {
    for (int y = 0; y < canvas->height(); y++) {
      int notMod = (x ^ y) % modVal;

      float hue = static_cast<float>(200);
      float bri = static_cast<float>(notMod) * 2.5f;
	      
      int r, g, b;
      HSBtoRGB(hue, 0, bri, r, g, b);
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

  int modVal = 1;
  int modMod = 1;
  Canvas *canvas = RGBMatrix::CreateFromFlags(&argc, &argv, &defaults);
  
  if (canvas == NULL)
    return 1;

  signal(SIGTERM, InterruptHandler);
  signal(SIGINT, InterruptHandler);
  
  while (true) {
    DrawOnCanvas(canvas, modVal);     
    if (interrupt_received){
      break;
    }   
    if (modVal == 64) {
    	modMod = -1;
    } 
    if (modVal == 1) {
    	modMod = 1;
    }
    modVal = modVal + modMod;
    usleep(1 * 100000);
  }
  
  delete canvas;

  return 0;
}
