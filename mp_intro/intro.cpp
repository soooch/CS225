#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "cs225/RGB_HSL.h"

#include <string>

using cs225::HSLAPixel;
using cs225::PNG;
using cs225::rgbaColor;

void rotate(std::string inputFile, std::string outputFile)
{
  PNG image;
  image.readFromFile(inputFile);

  for (unsigned x = 0, oppositeX = image.width() - 1; x < (image.width() / 2); x++, oppositeX--)
  {
    for (unsigned y = 0, oppositeY = image.height() - 1; y < (image.height()); y++, oppositeY--)
    {
      std::swap(image.getPixel(x, y), image.getPixel(oppositeX, oppositeY));
    }
  }

  // take care of the middle column if odd number of columns
  if (image.width() % 2 != 0)
  {
    unsigned x = (image.width() / 2);
    for (unsigned y = 0, oppositeY = image.height() - 1; y < (image.height() / 2); y++, oppositeY--)
    {
      std::swap(image.getPixel(x, y), image.getPixel(x, oppositeY));
    }
  }

  image.writeToFile(outputFile);
}

PNG myArt(unsigned int width, unsigned int height)
{
  PNG png(width, height);
  // TODO: Part 3
  class Vector3
  {
  public:
    double x, y, z;
    Vector3()
    {
      x = 0;
      y = 0;
      z = 0;
    }
    Vector3(double x, double y, double z)
    {
      this->x = x;
      this->y = y;
      this->z = z;
    }
    Vector3 operator*(double scalar)
    {
      return Vector3(x * scalar, y * scalar, z * scalar);
    }
    Vector3 operator+(const Vector3 &v)
    {
      return Vector3(
          this->x + v.x,
          this->y + v.y,
          this->z + v.z);
    }
    Vector3 operator-(const Vector3 &v)
    {
      return Vector3(
          this->x - v.x,
          this->y - v.y,
          this->z - v.z);
    }
    Vector3 cross(const Vector3 &v)
    {
      return Vector3(
          this->y * v.z - this->z * v.y,
          this->z * v.x - this->x * v.z,
          this->x * v.y - this->y * v.x);
    }
    double dot(const Vector3 &v)
    {
      return this->x * v.x + this->y * v.y + this->z + v.z;
    }
    double magnitude()
    {
      return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
    }
    Vector3 normalize()
    {
      return *this * (1.0 / this->magnitude());
    }
  };

  class Ray
  {
  public:
    Vector3 origin, direction;
    Ray()
    {
      origin = Vector3();
      direction = Vector3();
    }
    Ray(const Vector3 &origin, const Vector3 &direction)
    {
      this->origin = origin;
      this->direction = direction;
    }
  };

  class Sphere
  {
    double radius;
    Vector3 center;

  public:
    Sphere()
    {
      radius = 0.0;
      center = Vector3(0.0, 0.0, 0.0);
    }
    Sphere(double radius, const Vector3 &center)
    {
      this->radius = radius;
      this->center = center;
    }
    // Intersects ray r = p + td, |d| = 1, with sphere s and, if intersecting,
    // returns t value of intersection and intersection point q
    int IntersectRaySphere(Point p, Vector d, Sphere s, float &t, Point &q)
    {
      Vector m = p - s.c;
      float b = Dot(m, d);
      float c = Dot(m, m) - s.r * s.r;

      // Exit if r’s origin outside s (c > 0) and r pointing away from s (b > 0)
      if (c > 0.0f && b > 0.0f)
        return 0;
      float discr = b * b - c;

      // A negative discriminant corresponds to ray missing sphere
      if (discr < 0.0f)
        return 0;

      // Ray now found to intersect sphere, compute smallest t value of intersection
      t = -b - Sqrt(discr);

      // If t is negative, ray started inside sphere so clamp t to zero
      if (t < 0.0f)
        t = 0.0f;
      q = p + t * d;

      return 1;
    }
    bool intersect(Ray r, Sphere s, double & t, Vector3 & q)
    {
      Vector3 dist = r.origin - s.center;
      double b = m.d.dir;
    }
  };

  class Triangle
  {
    Vector3 a;
    Vector3 b;
    Vector3 c;

  public:
  };

  Vector3 v = Vector3(3, 2, -4);
  Vector3 b = Vector3(5, -1, 2);

  double n = v.dot(b);

  Vector3 c = b.normalize();

  std::cout << b.x << " " << b.y << " " << b.z << " " << n << std::endl;

  return png;
}
