/**
 * @file PNG.cpp
 * Implementation of a simple PNG class using RGBAPixels and the lodepng PNG library.
 *
 * @author CS 221: Data Structures
 */

#include <iostream>
#include <string>
#include <algorithm>
#include "lodepng/lodepng.h"
#include "RGBA_PNG.h"

namespace cs221util {
  void RGBA_PNG::_copy(RGBA_PNG const & other) {
    // Clear self
    delete[] imageData_;

    // Copy `other` to self
    width_ = other.width_;
    height_ = other.height_;
    imageData_ = new RGBAPixel[width_ * height_];
    for (unsigned i = 0; i < width_ * height_; i++) {
      imageData_[i] = other.imageData_[i];
    }
  }

  RGBA_PNG::RGBA_PNG() {
    width_ = 0;
    height_ = 0;
    imageData_ = NULL;
  }

  RGBA_PNG::RGBA_PNG(unsigned int width, unsigned int height) {
    width_ = width;
    height_ = height;
    imageData_ = new RGBAPixel[width * height];
  }

  RGBA_PNG::RGBA_PNG(RGBA_PNG const & other) {
    imageData_ = NULL;
    _copy(other);
  }

  RGBA_PNG::~RGBA_PNG() {
    delete[] imageData_;
  }

  RGBA_PNG const & RGBA_PNG::operator=(RGBA_PNG const & other) {
    if (this != &other) { _copy(other); }
    return *this;
  }

  bool RGBA_PNG::operator== (RGBA_PNG const & other) const {
    return (imageData_ == other.imageData_);
  }

  bool RGBA_PNG::operator!= (RGBA_PNG const & other) const {
    return !(*this == other);
  }

  RGBAPixel * RGBA_PNG::getPixel(unsigned int x, unsigned int y) {
    if (width_ == 0 || height_ == 0) {
      cerr << "ERROR: Call to cs221util::PNG::getPixel() made on an image with no pixels." << endl;
      cerr << "     : Returning NULL." << endl;
      return NULL;
    }

    if (x >= width_) {
      cerr << "WARNING: Call to cs221util::PNG::getPixel(" << x << "," << y << ") tries to access x=" << x
          << ", which is outside of the image (image width: " << width_ << ")." << endl;
      cerr << "       : Truncating x to " << (width_ - 1) << endl;
      x = width_ - 1;
    }

    if (y >= height_) {
      cerr << "WARNING: Call to cs221util::PNG::getPixel(" << x << "," << y << ") tries to access y=" << y
          << ", which is outside of the image (image height: " << height_ << ")." << endl;
      cerr << "       : Truncating y to " << (height_ - 1) << endl;
      y = height_ - 1;
    }

    unsigned index = x + (y * width_);
    return imageData_ + index;
  }

  bool RGBA_PNG::readFromFile(string const & fileName) {
    vector<unsigned char> byteData;
    unsigned error = lodepng::decode(byteData, width_, height_, fileName);

    if (error) {
      cerr << "PNG decoder error " << error << ": " << lodepng_error_text(error) << endl;
      return false;
    }

    delete[] imageData_;
    imageData_ = new RGBAPixel[width_ * height_];

    for (unsigned i = 0; i < byteData.size(); i += 4) {
      RGBAPixel & pixel = imageData_[i/4];
      pixel.r = byteData[i];
      pixel.g = byteData[i + 1];
      pixel.b = byteData[i + 2];
      pixel.a = byteData[i + 3]/255.;

    }

    return true;
  }

  bool RGBA_PNG::writeToFile(string const & fileName) {
    unsigned char *byteData = new unsigned char[width_ * height_ * 4];

    for (unsigned i = 0; i < width_ * height_; i++) {
      byteData[(i * 4)]     = imageData_[i].r;
      byteData[(i * 4) + 1] = imageData_[i].g;
      byteData[(i * 4) + 2] = imageData_[i].b;
      byteData[(i * 4) + 3] = imageData_[i].a * 255;
    }

    unsigned error = lodepng::encode(fileName, byteData, width_, height_);
    if (error) {
      cerr << "PNG encoding error " << error << ": " << lodepng_error_text(error) << endl;
    }

    delete[] byteData;
    return (error == 0);
  }

  unsigned int RGBA_PNG::width() const {
    return width_;
  }

  unsigned int RGBA_PNG::height() const {
    return height_;
  }

  void RGBA_PNG::resize(unsigned int newWidth, unsigned int newHeight) {
    // Create a new vector to store the image data for the new (resized) image
    RGBAPixel * newImageData = new RGBAPixel[newWidth * newHeight];

    // Copy the current data to the new image data, using the existing pixel
    // for coordinates within the bounds of the old image size
    for (unsigned x = 0; x < newWidth; x++) {
      for (unsigned y = 0; y < newHeight; y++) {
        if (x < width_ && y < height_) {
          RGBAPixel *oldPixel = this->getPixel(x, y);
          RGBAPixel & newPixel = newImageData[ (x + (y * newWidth)) ];
          newPixel = *oldPixel;
        }
      }
    }

    // Clear the existing image
    delete[] imageData_;

    // Update the image to reflect the new image size and data
    width_ = newWidth;
    height_ = newHeight;
    imageData_ = newImageData;
  }
}
