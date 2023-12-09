// https://gpfault.net/posts/perlin-noise.txt.html
// https://en.wikipedia.org/wiki/Perlin_noise

#include <cmath>
#include <vector>

class PerlinNoise {
  struct vec2 {
    float x, y;

    inline static float dot(const vec2& lhs, const vec2& rhs) {
      return lhs.x * rhs.x + lhs.y * rhs.y;
    }

    // TODO: Kinda slow
    inline static void normalize(vec2& v) {
      float m = v.magnitude();
      v.x /= m;
      v.y /= m;
    }
    vec2() = default;
    vec2(float x, float y) : x(x), y(y) {}

    vec2 operator +(const vec2& rhs) const { return vec2(x + rhs.x, y + rhs.y); }
    vec2 operator -(const vec2& rhs) const { return vec2(x - rhs.x, y - rhs.y); }

    float magnitude() const {
      return sqrt(x * x + y * y);
    }
  };

  struct vec3 {
    float x, y, z;

    inline static float dot(const vec3& lhs, const vec3& rhs) {
      return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
    }

    // TODO: Kinda slow
    inline static void normalize(vec3& v) {
      float m = v.magnitude();
      v.x /= m;
      v.y /= m;
      v.z /= m;
    }

    vec3() = default;
    vec3(float x, float y, float z) : x(x), y(y), z(z) {}

    vec3 operator +(const vec3& rhs) const { return vec3(x + rhs.x, y + rhs.y, z + rhs.z); }
    vec3 operator -(const vec3& rhs) const { return vec3(x - rhs.x, y - rhs.y, z - rhs.z); }

    float magnitude() const {
      return sqrt(x * x + y * y + z * z);
    }
  };

  int size;
  std::vector<vec3> permutation;

  void generate() {
    for (vec3& v : permutation) {
      v = vec3(
        // Random in [0, 255] to [0, 1] to [-1, 1]
        ((rand() % 256) / 255.f) * 2.f - 1.f,
        ((rand() % 256) / 255.f) * 2.f - 1.f,
        ((rand() % 256) / 255.f) * 2.f - 1.f
      );
    }
  }

  int gradient(int i) const {
    return permutation[i % permutation.size()].x;
  }

  vec2 gradient(const vec2& p) const {
    int i = static_cast<int>(p.x) % size;
    int j = static_cast<int>(p.y) % size;
    const vec3& v = permutation[i + j * size];
    vec2 rg = vec2(v.x, v.y);
    vec2::normalize(rg);

    return rg;
  }

  vec3 gradient(const vec3& p) const {
    int i = static_cast<int>(p.x) % size;
    int j = static_cast<int>(p.y) % size;
    vec3 rgb = permutation[i + j * size];
    vec3::normalize(rgb);

    return rgb;
  }

  float fade(float t) const {
    return t * t * t * (t * (t * 6.f - 15.f) + 10.f);
  }

  public:
    // @param size: the square size of the permutation table
    PerlinNoise(int size) : size(size) {
      permutation.resize(size * size);
      permutation.reserve(size * size);
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
    float noise2D(float x, float y) const {
      vec2 p = vec2(x, y);
      vec2 p0 = vec2(floor(x), floor(y));     // Top-left
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

    float noise3D(float x, float y, float z) {
      /* Calculate lattice points. */
      vec3 p = vec3(x, y, z);
      vec3 p0 = vec3(floor(p.x), floor(p.y), floor(p.z));
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

