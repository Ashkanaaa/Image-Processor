#include "chain.h"
#include <iostream>
#include "cs221util/PNG.h"
#include "lab_intro.h"
#include "cs221util/RGBA_PNG.h"
#include <random>
#include <cstdlib>
#include <ctime>
using namespace cs221util;
using namespace std;

void grayscaled(string filePath, string resultPath){
  RGBA_PNG png ,result; //creating the image objects
  png.readFromFile(filePath); //reading the source image
  result = grayscale(png); //performing the operation
  resultPath+= "/result.png"; //determining result path
  result.writeToFile(resultPath); //writting to the result path
}

void spotlighted(string filePath, string resultPath, int x, int y){
  RGBA_PNG png ,result; //creating the image objects
  png.readFromFile(filePath); //reading the source image
  result = createSpotlight(png, x, y); //performing the operation
  resultPath+= "/result.png"; //determining result path
  result.writeToFile(resultPath); //writting to the result path
}

void watermarked(string filePath1, string filePath2, string resultPath){
  RGBA_PNG png1, png2, result; //creating the image objects
  png1.readFromFile(filePath1); //reading the main source image
  png2.readFromFile(filePath2); //reading the main source image
  result = watermark(png1, png2); //performing the operation
  resultPath+= "/result.png"; //determining result path
  result.writeToFile(resultPath); //writting to the result path
}

void scrambled(string filePath, string resultPath){
  PNG im; //creating the image objects
  im.readFromFile(filePath); //reading the main source image
  Chain c(im,30); //creating the chain with 'segment' number of blocks
  c.scramble(); //performing the operation
  resultPath+= "/result.png"; //determining result path
  c.render().writeToFile(resultPath); //writting to the result path
}

void unscrambled(string filePath, string resultPath){
  PNG im; //creating the image objects
  im.readFromFile(filePath); //reading the main source image
  Chain c(im,30); //creating the chain with 100 segments of Blocks
  c.unscramble(); //performing the operation
  resultPath+= "/result.png"; //determining result path
  c.render().writeToFile(resultPath); //writting to the result path
}

int main(int argc, char *argv[]){
  if (atoi(argv[1]) == 1){
    grayscaled(argv[2], argv[3]);
  }else if(atoi(argv[1]) == 2){
    spotlighted(argv[2], argv[3], atoi(argv[4]), atoi(argv[5]));
  }else if(atoi(argv[1]) == 3){
    watermarked(argv[2], argv[3], argv[4]);
  }else if (atoi(argv[1]) == 4){
    scrambled(argv[2], argv[3]);
  }else if(atoi(argv[1]) == 5){
    unscrambled(argv[2], argv[3]);
  }
  return 0;
}
