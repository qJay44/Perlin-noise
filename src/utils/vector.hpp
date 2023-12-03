#pragma once

#include "../pch.h"

struct vec2 : sf::Vector2f {
  static vec2 randomUnit() {
    vec2 v = vec2(Random::GetFloat(-1.f, 1.f), Random::GetFloat(-1.f, 1.f));
    normalize(v);

    return v;
  }

  static vec2 random(float min, float max) {
    return vec2(Random::GetFloat(min, max), Random::GetFloat(min, max));
  }

  static float dot(const vec2& lhs, const vec2& rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
  }

  static void normalize(vec2& v) {
    v /= v.magnitude();
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

  float magnitude() {
    return std::sqrt(x * x + y * y);
  }
};

