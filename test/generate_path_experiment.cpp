#include <iostream>
#include <vector>
#include <memory>
#include <nodes/node2d.h>
#include <plot/pbPlots.hpp>
#include "gnuplot-iostream.h"
#include <queue>
#include <unordered_map>

using namespace std;

void plotGrid(int width, int height, const vector<vector<int>>& grid, const string& outputFileName) {
  Gnuplot gp;
  gp << "set xrange [-0.5:" << width - 0.5 << "]\n";
  gp << "set yrange [-0.5:" << height - 0.5 << "]\n";
  gp << "set size ratio -1\n";
  gp << "set palette gray\n";
  gp << "unset key\n";
  gp << "set output '" << outputFileName << "'\n"; // output file name
  gp << "plot '-' matrix with image\n";

  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      gp << grid[i][j] << " ";
    }
    gp << "\n";
  }

  gp << "e\n";
  gp.flush();
}

int main() {
  int width = 10;
  int height = 10;
  vector<vector<int>> grid(height, vector<int>(width, 0));
  // Set some obstacles
  grid[3][5] = 1;
  grid[6][2] = 1;
  plotGrid(width, height, grid, "grid.png"); // output file name
  return 0;
}
