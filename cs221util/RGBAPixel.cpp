/**
 * @file RGBAPixel.cpp
 * Implementation of the RGBAPixel class for use with the PNG library.
 */

#include "RGBAPixel.h"

namespace cs221util {
  RGBAPixel::RGBAPixel() {
    r = 255;
    g = 255;
    b = 255;
    a = 1.0;
  }

  // alpha will be 1.0. parameters must be in range of [0,255]
  RGBAPixel::RGBAPixel(int red, int green, int blue) {
    r = red;
    g = green;
    b = blue;
    a = 1.0;
  }

  RGBAPixel::RGBAPixel(int red, int green, int blue, double alpha) {
    r = red;
    g = green;
    b = blue;
    a = alpha;
  }
}