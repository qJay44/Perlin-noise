#include "preferences.h"
#include "PerlinNoise.hpp"

int main() {
  // Setup SFML //

  sf::RenderWindow window;
  sf::Font mainFont;

  window.create(sf::VideoMode(WIDTH, HEIGHT), "Field flow", sf::Style::Close);
  window.setFramerateLimit(75);

  mainFont.loadFromFile("../../src/fonts/Minecraft rus.ttf");

  ////////////////

  PerlinNoise pn;
  sf::VertexArray vertices{sf::Points, WIDTH * HEIGHT};

  auto generateNoise = [&]() {
    for (int x = 0; x < WIDTH; x++) {
      for (int y = 0; y < HEIGHT; y++) {
        vec2 pos = vec2(x, y);
        float n =
          pn.noise2D(pos / 64.f) * 1.f +
          pn.noise2D(pos / 32.f) * 0.5f +
          pn.noise2D(pos / 16.f) * 0.25f +
          pn.noise2D(pos / 8.f ) * 0.125f;

        sf::Uint8 alpha = (n * 0.5f + 0.5f) * 255; // from [-1, 1] to [0, 1] to [0, 255]
        sf::Color color = sf::Color(255, 255, 255, alpha);

        vertices[x + y * WIDTH] = sf::Vertex(pos, color);
      }
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

    window.clear(sf::Color(30, 30, 30));
    window.draw(vertices);
    window.display();
  }

	return 0;
}

