#include "preferences.h"
#include "utils/vector.hpp"
#include <cmath>
#include <vector>

class PerlinNoise {
  std::vector<vec2> permutation;

  // Generate a permutation table (random unit vectors)
  void generate() {
    for (int x = 0; x < WIDTH; x++)
      for (int y = 0; y < HEIGHT; y++)
        permutation[x + y * WIDTH] = vec2::randomUnit();
  }

  int gradient(int i) {
    return permutation[i].x > 0.5f ? 1 : -1;
  }

  vec2 gradient(const vec2& p) {
    int x = static_cast<int>(p.x);
    int y = static_cast<int>(p.y);

    return permutation[x + y * WIDTH];
  }

  float fade(float t) {
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

    // Return in [-1, 1]
    float noise1D(float p) {
      int p0 = floor(p);
      int p1 = p0 + 1;
      int g0 = gradient(p0);
      int g1 = gradient(p1);
      float f = fade(p - p0);

      return (1.f - f) * g0 * (p - p0) + f * g1 * (p - p1);
    }

    // Return in [-1, 1]
    float noise2D(const vec2& p) {
      vec2 p0 = vec2(floor(p.x), floor(p.y)); // Top-left
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
};

