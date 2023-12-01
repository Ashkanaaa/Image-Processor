#ifndef LAB_INTRO_H
#define LAB_INTRO_H

#include "cs221util/RGBA_PNG.h"
using namespace cs221util;

RGBA_PNG grayscale(RGBA_PNG image);  
RGBA_PNG createSpotlight(RGBA_PNG image, int centerX, int centerY);
RGBA_PNG ubcify(RGBA_PNG image);
RGBA_PNG watermark(RGBA_PNG firstImage, RGBA_PNG secondImage);

double colordist(RGBAPixel px1, RGBAPixel px2);

#endif
