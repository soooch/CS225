#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "cs225/RGB_HSL.h"

#include <string>

using cs225::HSLAPixel;
using cs225::PNG;
using cs225::rgbaColor;


void rotate(std::string inputFile, std::string outputFile) {
  // TODO: Part 2
  PNG image;
  image.readFromFile(inputFile);

  unsigned oppositeX = image.width();
  for (unsigned x = 0; x < (image.width()/2); x++) {
    oppositeX--;
    unsigned oppositeY = image.height();
    for (unsigned y = 0; y < (image.height()); y++) {
      oppositeY--;
      HSLAPixel & pixel = image.getPixel(x, y);
      HSLAPixel & oppositePixel = image.getPixel(oppositeX, oppositeY);
      std::swap(pixel, oppositePixel);
    }
  }
  
  if (image.width() % 2 != 0) {
    unsigned x = (image.width() / 2);
    unsigned oppositeY = image.height();
    for (unsigned y = 0; y < (image.height()/2); y++) {
      oppositeY--;
      HSLAPixel & pixel = image.getPixel(x, y);
      HSLAPixel & oppositePixel = image.getPixel(x, oppositeY);
      std::swap(pixel, oppositePixel);
    }
  }

  image.writeToFile(outputFile);

}

PNG myArt(unsigned int width, unsigned int height) {
  PNG png(width, height);
  // TODO: Part 3
  typedef struct {
    double x, y, z;
  } Vector3;

  class Sphere {
    double radius;
    Vector3 coord;
    public:
    Sphere();
    Sphere(double radius, Vector3 coord);
    bool reflection()
  }



  return png;
}
