#pragma once
#include "../pch.h"

struct vec2 : sf::Vector2f {
  inline static float dot(const vec2& lhs, const vec2& rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
  }

  inline static void normalize(vec2& v) {
    v /= v.magnitude();
  }

  inline static vec2 floor(const vec2& v) {
    return vec2(std::floor(v.x), std::floor(v.y));
  }

  static vec2 randomUnit() {
    vec2 v = vec2(Random::GetFloat(-1.f, 1.f), Random::GetFloat(-1.f, 1.f));
    normalize(v);

    return v;
  }

  static vec2 random(float min, float max) {
    return vec2(Random::GetFloat(min, max), Random::GetFloat(min, max));
  }


  vec2() : sf::Vector2f() {}

  vec2(float x, float y) {
    this->x = x;
    this->y = y;
  }

  vec2(const sf::Vector2f& v) {
    x = v.x;
    y = v.y;
  }

  vec2(float val) {
    x = val;
    y = val;
  }

  vec2 operator+(float rhs) const {
    return vec2(x + rhs, y + rhs);
  }

  void operator*=(float rhs) {
    x = x * rhs;
    y = y * rhs;
  }

  float magnitude() {
    return std::sqrt(x * x + y * y);
  }
};

