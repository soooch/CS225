/**
 * @file HSLAPixel.cpp
 * Implementation of the HSLAPixel class for use in with the PNG library.
 *
 * @author CS 225: Data Structures
 * @version 2018r1-lab1
 */

#include "HSLAPixel.h"
#include <cmath>
#include <iostream>
using namespace std;

namespace cs225 {
  HSLAPixel::HSLAPixel() {
    h = 0.0;
    s = 1.0;
    l = 1.0;
    a = 1.0;
  }

  HSLAPixel::HSLAPixel(double hue, double saturation, double luminance) {
    this->h = hue;
    this->s = saturation;
    this->l = luminance;
    this->a = 1.0;
  }

  HSLAPixel::HSLAPixel(double hue, double saturation, double luminance, double alpha) {
    this->h = hue;
    this->s = saturation;
    this->l = luminance;
    this->a = alpha;
  }

}
