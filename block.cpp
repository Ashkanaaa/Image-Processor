#include "block.h"
#include <cmath>
#include <iostream>

int Block::height() const {
  /* your code here */
  return data[0].size();
}

int Block::width() const {
  /* your code here */
  return data.size();
}

void Block::render(PNG &im, int x) const {
  /* your code here */
  for(int i =0;i<width();i++){
    for(int j = 0;j<height();j++){
      *im.getPixel(i+x,j) = data[i][j];
    }
  }
}

void Block::build(PNG &im, int x, int width) {
  /* your code here */
  vector<HSLAPixel> v(im.height());
  data.assign(width, v);

  for(int i = 0;i<width;i++){
    for(int j=0;j<im.height();j++){
      data[i][j] = *im.getPixel(i+x, j);
    }
  }
}

// Return "distance" between rightmost column of this (leftBlock)
// and leftmost column of rightBlock
double Block::distanceTo(Block const & rightBlock) const {
  int h = height();
  int w = width();
  double d = 0.0;
  for( int y=0; y<h; ++y ) {
    if( data[w-1][y] != rightBlock.data[0][y] ) d = d+1;
  }
  d = d/h;
  return d;
}

