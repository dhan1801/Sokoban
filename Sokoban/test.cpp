#include "Sokoban.hpp"
#include <cassert>
#include <iostream>

int main() {
  SB::Sokoban game;
  assert(game.loadLevel("levels/test1.txt"));

  sf::Vector2i originalPos = game.playerLoc();
  game.movePlayer(SB::Direction::Right);
  sf::Vector2i movedPos = game.playerLoc();
  assert(movedPos != originalPos);

  game.undo();
  assert(game.playerLoc() == originalPos);

  game.redo();
  assert(game.playerLoc() == movedPos);

  while (!game.isWon()) {
    game.movePlayer(SB::Direction::Right);
  }
  assert(game.isWon());

  std::cout << "All tests passed!\n";
  return 0;
}
