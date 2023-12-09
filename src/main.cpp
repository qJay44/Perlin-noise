#include "pch.h"
#include "PerlinNoise.hpp"

int main() {
  sf::RenderWindow window;
  window.create(sf::VideoMode(WIDTH, HEIGHT), "Perlin noise", sf::Style::Close);
  window.setFramerateLimit(90);

  srand(time(NULL));
  PerlinNoise* pn = new PerlinNoise(256);
  sf::VertexArray vertices{sf::Points, WIDTH * HEIGHT};
  sf::Clock clock;

  for (int x = 0; x < WIDTH; x++)
    for (int y = 0; y < HEIGHT; y++)
      vertices[x + y * WIDTH] = sf::Vertex(sf::Vector2f(x, y));

  const auto generateNoise2D = [&]() {
    for (int i = 0; i < vertices.getVertexCount(); i++) {
      const sf::Vector2f& pos = vertices[i].position;
      float n =
        pn->noise2D(pos.x / 64.f, pos.y / 64.f) * 1.f +
        pn->noise2D(pos.x / 32.f, pos.y / 32.f) * 0.5f +
        pn->noise2D(pos.x / 16.f, pos.y / 16.f) * 0.25f +
        pn->noise2D(pos.x / 8.f , pos.y / 8.f ) * 0.125f;

      sf::Uint8 alpha = (n * 0.5f + 0.5f) * 255;
      vertices[i].color = {255, 255, 255, alpha};
    }
  };

  generateNoise2D();

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
            pn->regenerate();
            generateNoise2D();
            break;
          default:
            break;
        }
    }

    window.clear();
    window.draw(vertices);
    window.display();
  }

  delete pn;

	return 0;
}

