#include "preferences.h"
#include "utils/vector.hpp"
#include <cmath>
#include <vector>

class PerlinNoise {
  std::vector<vec3> permutation;

  void generate() {
    for (int x = 0; x < WIDTH; x++)
      for (int y = 0; y < HEIGHT; y++)
        permutation[x + y * WIDTH] = vec3::randomUnit();
  }

  int gradient(int i) const {
    return permutation[i].x > 0.5f ? 1 : -1;
  }

  vec2 gradient(const vec2& p) const {
    int x = static_cast<int>(p.x);
    int y = static_cast<int>(p.y);
    vec3 rgb = permutation[x + y * WIDTH];

    return vec2(rgb.x, rgb.y);
  }

  vec3 gradient(const vec3& p) const {
    int x = static_cast<int>(p.x);
    int y = static_cast<int>(p.y);

    return permutation[x + y * WIDTH];
  }

  float fade(float t) const {
    return t * t * t * (t * (t * 6.f - 15.f) + 10.f);
  }

  public:
    PerlinNoise() {
      permutation.reserve(WIDTH * HEIGHT);
      generate();
    }

    void regenerate() {
      generate();
    }

    // Return value in [-1, 1]
    float noise1D(float p) const {
      int p0 = floor(p);
      int p1 = p0 + 1;
      int g0 = gradient(p0);
      int g1 = gradient(p1);
      float f = fade(p - p0);

      return (1.f - f) * g0 * (p - p0) + f * g1 * (p - p1);
    }

    // Return value in [-1, 1]
    float noise2D(const vec2& p) const {
      vec2 p0 = vec2::floor(p);               // Top-left
      vec2 p1 = p0 + vec2(1.f, 0.f);          // Top-right
      vec2 p2 = p0 + vec2(0.f, 1.f);          // Bottom-left
      vec2 p3 = p0 + vec2(1.f, 1.f);          // Bottom-right

      vec2 g0 = gradient(p0);
      vec2 g1 = gradient(p1);
      vec2 g2 = gradient(p2);
      vec2 g3 = gradient(p3);

      // Interpolate in horizontal direction
      float t0 = p.x - p0.x;
      float fade_t0 = fade(t0);

      // Interpolate in vertical direction
      float t1 = p.y - p0.y;
      float fade_t1 = fade(t1);

      // Dot products
      float p0p1 = (1.f - fade_t0) * vec2::dot(g0, (p - p0)) + fade_t0 * vec2::dot(g1, (p - p1)); // Upper two
      float p2p3 = (1.f - fade_t0) * vec2::dot(g2, (p - p2)) + fade_t0 * vec2::dot(g3, (p - p3)); // Lower two

      return (1.f - fade_t1) * p0p1 + fade_t1 * p2p3;
    }

    float noise3D(vec3 p) {
      /* Calculate lattice points. */
      vec3 p0 = vec3::floor(p);
      vec3 p1 = p0 + vec3(1.0, 0.0, 0.0);
      vec3 p2 = p0 + vec3(0.0, 1.0, 0.0);
      vec3 p3 = p0 + vec3(1.0, 1.0, 0.0);
      vec3 p4 = p0 + vec3(0.0, 0.0, 1.0);
      vec3 p5 = p4 + vec3(1.0, 0.0, 0.0);
      vec3 p6 = p4 + vec3(0.0, 1.0, 0.0);
      vec3 p7 = p4 + vec3(1.0, 1.0, 0.0);

      /* Look up gradients at lattice points. */
      vec3 g0 = gradient(p0);
      vec3 g1 = gradient(p1);
      vec3 g2 = gradient(p2);
      vec3 g3 = gradient(p3);
      vec3 g4 = gradient(p4);
      vec3 g5 = gradient(p5);
      vec3 g6 = gradient(p6);
      vec3 g7 = gradient(p7);

      float t0 = p.x - p0.x;
      float fade_t0 = fade(t0); /* Used for interpolation in horizontal direction */

      float t1 = p.y - p0.y;
      float fade_t1 = fade(t1); /* Used for interpolation in vertical direction. */

      float t2 = p.z - p0.z;
      float fade_t2 = fade(t2);

      /* Calculate dot products and interpolate.*/
      float p0p1 = (1.0 - fade_t0) * vec3::dot(g0, (p - p0)) + fade_t0 * vec3::dot(g1, (p - p1)); /* between upper two lattice points */
      float p2p3 = (1.0 - fade_t0) * vec3::dot(g2, (p - p2)) + fade_t0 * vec3::dot(g3, (p - p3)); /* between lower two lattice points */

      float p4p5 = (1.0 - fade_t0) * vec3::dot(g4, (p - p4)) + fade_t0 * vec3::dot(g5, (p - p5)); /* between upper two lattice points */
      float p6p7 = (1.0 - fade_t0) * vec3::dot(g6, (p - p6)) + fade_t0 * vec3::dot(g7, (p - p7)); /* between lower two lattice points */

      float y1 = (1.0 - fade_t1) * p0p1 + fade_t1 * p2p3;
      float y2 = (1.0 - fade_t1) * p4p5 + fade_t1 * p6p7;

      /* Calculate final result */
      return (1.0 - fade_t2) * y1 + fade_t2 * y2;
    }
};

