#include <cmath>
#include <string>

#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"

using cs225::HSLAPixel;
using cs225::PNG;

void rotate(std::string inputFile, std::string outputFile) {
  PNG image;
  image.readFromFile(inputFile);

  for (unsigned x = 0, oppositeX = image.width() - 1; x < (image.width() / 2);
       x++, oppositeX--) {
    for (unsigned y = 0, oppositeY = image.height() - 1; y < (image.height());
         y++, oppositeY--) {
      std::swap(image.getPixel(x, y), image.getPixel(oppositeX, oppositeY));
    }
  }

  // take care of the middle column if odd number of columns
  if (image.width() % 2 != 0) {
    unsigned x = (image.width() / 2);
    for (unsigned y = 0, oppositeY = image.height() - 1;
         y < (image.height() / 2); y++, oppositeY--) {
      std::swap(image.getPixel(x, y), image.getPixel(x, oppositeY));
    }
  }

  image.writeToFile(outputFile);
}

PNG myArt(unsigned int width, unsigned int height) {
  PNG png(width, height);
  class Vector3 {
   public:
    float x, y, z;
    Vector3() {
      x = 0;
      y = 0;
      z = 0;
    }
    Vector3(float x, float y, float z) {
      this->x = x;
      this->y = y;
      this->z = z;
    }
    Vector3 operator*(float scalar) {
      return Vector3(x * scalar, y * scalar, z * scalar);
    }
    Vector3 operator+(const Vector3 &v) {
      return Vector3(this->x + v.x, this->y + v.y, this->z + v.z);
    }
    Vector3 operator-(const Vector3 &v) {
      return Vector3(this->x - v.x, this->y - v.y, this->z - v.z);
    }
    Vector3 cross(const Vector3 &v) {
      return Vector3(this->y * v.z - this->z * v.y,
                     this->z * v.x - this->x * v.z,
                     this->x * v.y - this->y * v.x);
    }
    float dot(const Vector3 &v) {
      return this->x * v.x + this->y * v.y + this->z * v.z;
    }
    float magnitude() {
      return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
    }
    Vector3 normalize() {
      *this = *this * (1.0 / this->magnitude());
      return *this;
    }
    Vector3 normalized() { return *this * (1.0 / this->magnitude()); }
    void print() {
      std::cout << "(" << this->x << ", " << this->y << ", " << this->z << ")"
                << std::endl;
    }

    std::string str() {
      std::stringstream s;
      s << "(" << this->x << ", " << this->y << ", " << this->z << ")";
      return s.str();
    }
  };

  class Ray {
   public:
    Vector3 origin, direction;
    Ray() {
      origin = Vector3();
      direction = Vector3();
    }
    Ray(const Vector3 &origin, const Vector3 &direction) {
      this->origin = origin;
      this->direction = direction;
    }
    Ray normalized() { return Ray(origin, direction.normalized()); }
  };

  class Sphere {
   public:
    float radius;
    Vector3 center;

    Sphere() {
      radius = 0.0;
      center = Vector3(0.0, 0.0, 0.0);
    }
    Sphere(float radius, const Vector3 &center) {
      this->radius = radius;
      this->center = center;
    }
    // https://gamedev.stackexchange.com/questions/96459/fast-ray-sphere-collision-code
    // Intersects ray r = p + td, |d| = 1, with sphere s and, if intersecting,
    // returns t value of intersection and intersection point q
    bool intersect(Ray &r, float &t, Vector3 &q) {
      Vector3 dist = r.origin - this->center;
      float b = dist.dot(r.direction);
      float c = dist.dot(dist) - this->radius * this->radius;

      // Exit if r’s origin outside s (c > 0) and r pointing away from s (b > 0)
      if (c > 0.0f && b > 0.0f) return false;
      float discr = b * b - c;

      // A negative discriminant corresponds to ray missing sphere
      if (discr < 0.0f) return false;

      // Ray now found to intersect sphere, compute smallest t value of
      // intersection
      t = -b - sqrt(discr);

      // If t is negative, ray started inside sphere so clamp t to zero
      if (t < 0.0f) t = -t;
      q = r.origin + (r.direction * t);

      return true;
    }
  };

  class Triangle {
    Vector3 a;
    Vector3 b;
    Vector3 c;

   public:
  };

  class RGBPixel {
   public:
    float r, g, b;
    RGBPixel() { r = b = g = 0; }
    RGBPixel(float r, float g, float b) {
      this->r = r;
      this->g = g;
      this->b = b;
    }
    HSLAPixel toHSLA() {
      HSLAPixel hsl;
      double r, g, b, min, max, chroma;
      r = this->r;
      g = this->g;
      b = this->b;

      // HSV Calculations -- formulas sourced from
      // https://en.wikipedia.org/wiki/HSL_and_HSV Compute constants
      min = (r < g) ? r : g;
      min = (min < b) ? min : b;

      max = (r > g) ? r : g;
      max = (max > b) ? max : b;

      chroma = max - min;

      // Compute L
      hsl.l = 0.5 * (max + min);

      // Check for black, white, and shades of gray, where H is undefined,
      // S is always 0, and L controls the shade of gray.  Mathematically, this
      // is true when chroma == 0, but we'll use a near-zero value to account
      // for floating point errors.
      //
      // This check is required here, or division by zero will occur when
      // calculating S and H below.
      if (chroma < 0.0001 || max < 0.0001) {
        hsl.h = hsl.s = 0;
        return hsl;
      }

      // Compute S
      hsl.s = chroma / (1 - fabs((2 * hsl.l) - 1));

      // Compute H
      if (max == r) {
        hsl.h = fmod((g - b) / chroma, 6);
      } else if (max == g) {
        hsl.h = ((b - r) / chroma) + 2;
      } else {
        hsl.h = ((r - g) / chroma) + 4;
      }

      hsl.h *= 60;
      if (hsl.h < 0) {
        hsl.h += 360;
      }

      // Return result
      return hsl;
    }
  };

  static float piOverTwo = 1.5707963267948966192313216916397514420;

  Vector3 eyePos(0.0, 0.0, 0.0);
  float fov = piOverTwo;

  // ensure these are normalized
  Vector3 upInput(0.0, 1.0, 0.0);
  Vector3 center(0.0, 0.0, 1.0);

  Vector3 right = upInput.cross(center).normalized();
  Vector3 up = center.cross(right);

  float screenX = std::tan(fov / 2.0);
  float screenY =
      screenX *
      ((float)height /
       (float)width);  // height / width is probably only ever going to be 1

  Vector3 nextX = right * ((2.0 * screenX) / (float)(width - 1));
  Vector3 nextY = up * ((2.0 * screenY) / (float)(height - 1));
  Vector3 initDir = center - right * screenX + up * screenY;

  Sphere s1(1.0, Vector3(0.0, 0.0, 4.0));

  Ray r;
  r.origin = eyePos;

  for (unsigned x = 0; x < width; x++) {
    r.direction = initDir + nextX * (float)x;
    for (unsigned y = 0; y < height; y++) {
      auto pixel = RGBPixel(0, 0, 0);
      float t;
      Vector3 q;
      Ray normed = r.normalized();
      if (s1.intersect(normed, t, q)) {
        //q.print();
        Vector3 normal = (q - s1.center).normalize();
        //normal.print();
        pixel = RGBPixel(abs(normal.x), abs(normal.y), abs(normal.z));
      }
      png.getPixel(x, y) = pixel.toHSLA();
      r.direction = r.direction - nextY;
    }
  }

  return png;
}