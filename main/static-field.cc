#include "led-matrix.h"
#include "RandomFunctions.h"
#include "ArtFunctions.h"

#include <stdio.h>
#include <signal.h>

using rgb_matrix::RGBMatrix;
using rgb_matrix::Canvas;


volatile bool interrupt_received = false;


static void InterruptHandler(int signo) {
  interrupt_received = true;
}

static void DrawOnCanvas(Canvas *canvas, State &stateObj) {
  int sz = 8;
  for (int x = 0; x < canvas->width(); x+=sz) {
    for (int y = 0; y < canvas->height(); y+=sz) {
      float rndVal = GenerateRandom(stateObj);
      float hue = mapFloat(rndVal, 0, 1, 190, 210);
      rndVal = GenerateRandom(stateObj);     
      float bri = mapFloat(rndVal, 0, 1, 0, 100);
      rndVal = GenerateRandom(stateObj);     
      float sat = mapFloat(rndVal, 0, 1, 0, 100);
      int r, g, b;
      HSBtoRGB(hue, bri, sat, r, g, b);
      for (int sx = x; sx < x + sz; sx++) {
        for (int sy = y; sy < y + sz; sy++) {
          canvas->SetPixel(sx, sy, r, g, b);
	      }
      }
    }
  }
}


int main(int argc, char *argv[]) {
  RGBMatrix::Options defaults;
  State state;

  InitRNGState(654654, state);

  defaults.hardware_mapping = "adafruit-hat";
  defaults.rows = 64;
  defaults.cols = 64;
  defaults.chain_length = 1;
  defaults.parallel = 1;
  defaults.show_refresh_rate = true;

  Canvas *canvas = RGBMatrix::CreateFromFlags(&argc, &argv, &defaults);
  
  if (canvas == NULL)
    return 1;

  signal(SIGTERM, InterruptHandler);
  signal(SIGINT, InterruptHandler);
  
  while (true) {
    DrawOnCanvas(canvas, state);     
    if (interrupt_received){
      break;
    }   
    usleep(1 * 100000);
  }
  
  delete canvas;

  return 0;
}
