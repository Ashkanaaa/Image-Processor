/**
 * @file RGBAPixel.h
 */

#ifndef _RGBAPIXEL_H_
#define _RGBAPIXEL_H_

namespace cs221util {
  class RGBAPixel {
    public: // member attributes
      unsigned char r; // 8-bit red channel, integer in the range of [0,255]
      unsigned char g; // 8-bit green channel, integer in the range of [0,255]
      unsigned char b; // 8-bit blue channel, integer in the range of [0,255]
      double a; // alpha channel, double in the range of [0,1]. 0: transparent, 1: opaque
    
    public: // member functions
      RGBAPixel(); // default constructor
      RGBAPixel(int red, int green, int blue); // alpha will be 1.0. parameters must be in range of [0,255]
      RGBAPixel(int red, int green, int blue, double alpha);
  };
}
#endif