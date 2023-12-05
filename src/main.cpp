#include "preferences.h"
#include "PerlinNoise.hpp"

int main() {
  // Setup SFML //

  sf::RenderWindow window;
  sf::Font mainFont;

  window.create(sf::VideoMode(WIDTH, HEIGHT), "Perlin noise", sf::Style::Close);
  window.setFramerateLimit(90);

  mainFont.loadFromFile("../../src/fonts/Minecraft rus.ttf");

  ////////////////

  PerlinNoise pn;
  sf::VertexArray vertices{sf::Points, WIDTH * HEIGHT};
  sf::Clock clock;

  for (int x = 0; x < WIDTH; x++)
    for (int y = 0; y < HEIGHT; y++)
      vertices[x + y * WIDTH] = sf::Vertex(vec2(x, y));

  auto generateNoise = [&]() {
    float time = clock.getElapsedTime().asSeconds();
    for (int i = 0; i < vertices.getVertexCount(); i++) {
      const vec2& pos = vertices[i].position;

      float n =
        pn.noise3D(vec3(pos, time * 30.f) / 128.f) / 1.f +
        pn.noise3D(vec3(pos, time * 30.f) / 64.f ) / 2.f +
        pn.noise3D(vec3(pos, time * 64.f) / 32.f ) / 16.f;

      vec3 mix1 = vec3::mix(vec3(1.f, 1.f, 0.f), vec3(1.f, 0.2f, 0.f), n + 1.f);
      vec3 mix2 = vec3::mix(mix1, vec3(0.1f, 0.f, 0.f), n * 0.5f + 0.5f);

      vertices[i].color = sf::Color(mix2.x * 255, mix2.y * 255, mix2.z * 255);
    }
  };

  generateNoise();

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();

      if (event.type == sf::Event::KeyReleased)
        switch (event.key.code) {
          case sf::Keyboard::Q:
            window.close();
            break;
          case sf::Keyboard::R:
            pn.regenerate();
            generateNoise();
            break;
          default:
            break;
        }
    }

    window.clear();
    window.draw(vertices);
    window.display();
  }

	return 0;
}

