#include "pch.h"
#include "PerlinNoise.hpp"

int main() {
  sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Perlin noise", sf::Style::Close);
  window.setFramerateLimit(90);

  srand((unsigned)time(NULL));
  PerlinNoise* pn = new PerlinNoise(256);
  sf::VertexArray vertices{sf::Quads, COLUMNS * ROWS * 4};

  for (int x = 0; x < COLUMNS; x++)
    for (int y = 0; y < ROWS; y++) {
      int index = (x + y * COLUMNS) << 2;
      sf::Vector2f pos = sf::Vector2f(x * CELL_SCALE, y * CELL_SCALE);

      vertices[index + 0].position = pos;
      vertices[index + 1].position = {pos.x + CELL_SCALE, pos.y};
      vertices[index + 2].position = {pos.x + CELL_SCALE, pos.y + CELL_SCALE};
      vertices[index + 3].position = {pos.x, pos.y + CELL_SCALE};
    }

  const auto generateNoise2D = [&]() {
    for (int x = 0; x < COLUMNS; x++) {
      for (int y = 0; y < ROWS; y++) {
        int index = (x + y * COLUMNS) << 2;
        const sf::Vector2f& pos = vertices[index].position;

        float n =
          pn->noise2D(pos.x / 64.f, pos.y / 64.f) * 1.f +
          pn->noise2D(pos.x / 32.f, pos.y / 32.f) * 0.5f +
          pn->noise2D(pos.x / 16.f, pos.y / 16.f) * 0.25f +
          pn->noise2D(pos.x / 8.f , pos.y / 8.f ) * 0.125f;

        sf::Uint8 alpha = (n * 0.5f + 0.5f) * 255;
        sf::Color color = {255, 255, 255, alpha};

        vertices[index + 0].color = color;
        vertices[index + 1].color = color;
        vertices[index + 2].color = color;
        vertices[index + 3].color = color;
      }
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

