// -*- mode: c++; c-basic-offset: 2; indent-tabs-mode: nil; -*-
// Small example how to use the library.
// For more examples, look at demo-main.cc
//
// This code is public domain
// (but note, that the led-matrix library this depends on is GPL v2)

#include "led-matrix.h"
#include "graphics.h"
#include "ArtFunctions.h"
#include "RandomFunctions.h"

#include <stdio.h>
#include <signal.h>
#include <iostream>
#include <vector>
#include <deque>

using rgb_matrix::RGBMatrix;
using rgb_matrix::Canvas;
using rgb_matrix::Color;

const int kGridSize = 64;
const int kBlockSize = 4; 

volatile bool interrupt_received = false;


static void InterruptHandler(int signo) {
  interrupt_received = true;
}

void InitializeGrid(std::deque<std::vector<float>>& grid, State &stateObj) {
    for (int i = 0; i < kGridSize; ++i) {
        std::vector<float> column;
        for (int j = 0; j < kGridSize; ++j) {
            column.push_back(GenerateRandom(stateObj));
        }
        grid.push_back(column);
    }
}

// Scroll and update the grid
void ScrollGrid(std::deque<std::vector<float>>& grid, State &stateObj) {
    grid.pop_front(); // Remove the top row

    std::vector<float> newRow;
    for (int i = 0; i < kGridSize; ++i) {
        newRow.push_back(GenerateRandom(stateObj));
    }
    grid.push_back(newRow); // Add a new row at the bottom
}

// Draw the grid on the canvas
void DrawOnCanvas(Canvas* canvas, const std::deque<std::vector<float>>& grid) {
    canvas->Fill(47, 62, 60);
    for (int y = 0; y < kGridSize; ++y) {
        for (int x = 0; x < kGridSize; ++x) {
            float value = grid[y][x];
            Color color = (value > 0.5) ? Color(132, 169, 140) : Color(202, 210, 197);
            if (value > .5) {
              DrawLine(canvas, x * kBlockSize, y * kBlockSize,
                      x * kBlockSize + kBlockSize, y * kBlockSize + kBlockSize, color);
            } else {
              DrawLine(canvas, x * kBlockSize, y * kBlockSize+ kBlockSize,
                      x * kBlockSize + kBlockSize, y * kBlockSize, color);

            }
        }
    }
}


int main(int argc, char *argv[]) {
  RGBMatrix::Options defaults;
  State state;
  std::deque<std::vector<float>> grid;
  
  InitRNGState(654654, state);
  InitializeGrid(grid, state);

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
    ScrollGrid(grid, state);
    DrawOnCanvas(canvas, grid);     
    if (interrupt_received){
      break;
    }   
    usleep(1 * 100000);
  }
  
  delete canvas;

  return 0;
}
