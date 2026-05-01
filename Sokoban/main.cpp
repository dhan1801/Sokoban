// Copyright 2025 Dhanvika Nakka
#include <SFML/Graphics.hpp>
#include "Sokoban.hpp"

int main(int argc, char* argv[]) {
  SB::Sokoban game;
  if (argc != 2 || !game.loadLevel(argv[1])) return 1;

  sf::RenderWindow window(
    sf::VideoMode(static_cast<unsigned int>(game.width() * 32),
                  static_cast<unsigned int>(game.height() * 32)),
    "Sokoban"
  );

  while (window.isOpen()) {
    sf::Event ev;
    while (window.pollEvent(ev)) {
      if (ev.type == sf::Event::Closed) window.close();
      if (ev.type == sf::Event::KeyPressed) {
        using D = SB::Direction;
        if (ev.key.code == sf::Keyboard::Up) game.movePlayer(D::Up);
        else if (ev.key.code == sf::Keyboard::Down) game.movePlayer(D::Down);
        else if (ev.key.code == sf::Keyboard::Left) game.movePlayer(D::Left);
        else if (ev.key.code == sf::Keyboard::Right) game.movePlayer(D::Right);
        else if (ev.key.code == sf::Keyboard::Z) game.undo();
        else if (ev.key.code == sf::Keyboard::Y) game.redo();
      }
    }

    window.clear();
    auto grid = game.getGrid();
    for (int y = 0; y < game.height(); ++y) {
      for (int x = 0; x < game.width(); ++x) {
        char c = grid[y][x];
        sf::Sprite& sprite = (c == '@')
                             ? game.getPlayerSprite()
                             : game.getSprite(c);
        sprite.setPosition(x * 32.f, y * 32.f);
        window.draw(sprite);
      }
    }
    window.display();

    if (game.isWon()) {
      sf::sleep(sf::seconds(2));
      window.close();
    }
  }

  return 0;
}
