#include <cmath>
#include "Image.h"

Image::Image() : PNG() {}

Image::Image(unsigned int width, unsigned int height) : PNG(width, height) {}


void Image::lighten() {
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      getPixel(x, y).l = std::min(getPixel(x, y).l + 0.1, 1.0);
    }
  }
}

void Image::lighten(double amount) {
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      getPixel(x, y).l = std::min(getPixel(x, y).l + amount, 1.0);
    }
  }
}

void Image::darken() {
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      getPixel(x, y).l = std::max(getPixel(x, y).l - 0.1, 0.0);
    }
  }
}

void Image::darken(double amount) {
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      getPixel(x, y).l = std::max(getPixel(x, y).l - amount, 0.0);
    }
  }
}

void Image::saturate() {
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      getPixel(x, y).s = std::min(getPixel(x, y).s + 0.1, 1.0);
    }
  }
}

void Image::saturate(double amount) {
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      getPixel(x, y).s = std::min(getPixel(x, y).s + amount, 1.0);
    }
  }
}

void Image::desaturate() {
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      getPixel(x, y).s = std::max(getPixel(x, y).s - 0.1, 0.0);
    }
  }
}

void Image::desaturate(double amount) {
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      getPixel(x, y).s = std::max(getPixel(x, y).s - amount, 0.0);
    }
  }
}

void Image::grayscale() {
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      getPixel(x, y).s = 0;
    }
  }
}

void Image::rotateColor(double degrees) {
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      double rawAdd = getPixel(x, y).h + degrees;
      double shift = std::fmod(rawAdd, 360);
      if (shift < 0) getPixel(x, y).h = 360 + shift;
      else getPixel(x, y).h = shift;
    }
  }
}

void Image::illinify() {
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      double hue = getPixel(x, y).h;
      if (hue > 113.5 && hue < 293.5) {
        getPixel(x, y).h = 216;
      }
      else {
        getPixel(x, y).h = 11;
      }
    }
  }
  
}

void Image::scale(double factor) {
  unsigned scaledWidth = width() * factor;
  unsigned scaledHeight = height() * factor;
  Image scaledImage(scaledWidth, scaledHeight);
  for (unsigned x = 0; x < scaledWidth; x++) {
    for (unsigned y = 0; y < scaledHeight; y++) {
      scaledImage.getPixel(x, y) = getPixel(x / factor, y / factor);
    }
  }
  *this = scaledImage;
}

void Image::scale(unsigned w, unsigned h) {
  Image scaledImage(w, h);
  double xFactor = w / width();
  double yFactor = h / height();
  for (unsigned x = 0; x < w; x++) {
    for (unsigned y = 0; y < h; y++) {
      scaledImage.getPixel(x, y) = getPixel(x / xFactor, y / yFactor);
    }
  }
  *this = scaledImage;
}