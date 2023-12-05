#pragma once
#include "../pch.h"
#include "vec2.hpp"

struct vec3 : sf::Vector3f {
  inline static float dot(
    const vec3& v1,
    const vec3& v2
  ) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
  }

  inline static void normalize(vec3& v) {
    v /= v.magnitude();
  }

  inline static vec3 floor(const vec3& v) {
    return vec3(std::floor(v.x), std::floor(v.y), std::floor(v.z));
  }

  inline static vec3 mix(vec3 x, vec3 y, vec3 a) {
    vec3 mixed = x * (vec3(1.f) - a) + y * a;
    mixed.x = std::clamp(mixed.x, 0.f, 1.f);
    mixed.y = std::clamp(mixed.y, 0.f, 1.f);
    mixed.z = std::clamp(mixed.z, 0.f, 1.f);

    return mixed;
  }

  static vec3 randomUnit() {
    vec3 v = vec3(
      Random::GetFloat(-1.f, 1.f),
      Random::GetFloat(-1.f, 1.f),
      Random::GetFloat(-1.f, 1.f)
    );
    normalize(v);

    return v;
  }

  static vec3 random(float min, float max) {
    return vec3(
      Random::GetFloat(min, max),
      Random::GetFloat(min, max),
      Random::GetFloat(min, max)
    );
  }

  vec3() : sf::Vector3f() {}

  vec3(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
  }

  vec3(const sf::Vector3f& v) {
    x = v.x;
    y = v.y;
    z = v.z;
  }

  vec3(float val) {
    x = val;
    y = val;
    z = val;
  }

  vec3(const vec2& v, float c) {
    x = v.x;
    y = v.y;
    z = c;
  }

  vec3 operator*(const vec3& rhs) const {
    return vec3(x * rhs.x, y * rhs.y, z * rhs.z);
  }

  float magnitude() {
    return std::sqrt(x * x + y * y);
  }
};

