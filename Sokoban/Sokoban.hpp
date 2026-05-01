// Copyright 2025 Dhanvika Nakka
#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stack>
#include <vector>
#include <string>
#include <map>

namespace SB {

enum class Direction { Up, Down, Left, Right };

class Sokoban {
 public:
  Sokoban();
  bool loadLevel(const std::string& path);
  void movePlayer(Direction dir);
  bool isWon() const;
  int width() const;
  int height() const;
  sf::Vector2i playerLoc() const;
  std::vector<std::string> getGrid() const;
  void undo();
  void redo();
  sf::Sprite& getSprite(char c) { return _sprites[c]; }
  sf::Sprite& getPlayerSprite() { return _playerSprites.at(_lastMoveDir); }

 private:
  void loadTextures();
  bool isValidMove(int x, int y) const;
  bool canPushBox(int x, int y, Direction dir, int& bx, int& by) const;
  void checkVictory();

  std::vector<std::string> _originalGrid;
  std::vector<std::string> _grid;
  int _width, _height;
  sf::Vector2i _playerPos;
  char _playerTileUnder;
  Direction _lastMoveDir;
  bool _hasWon;

  struct State {
    std::vector<std::string> grid;
    sf::Vector2i pos;
    char tileUnder;
  };
  std::stack<State> _undoStack, _redoStack;

  std::map<char, sf::Texture> _textures;
  std::map<char, sf::Sprite> _sprites;
  std::map<Direction, sf::Texture> _playerTextures;
  std::map<Direction, sf::Sprite> _playerSprites;

  sf::SoundBuffer _victoryBuffer;
  sf::Sound _victorySound;

  int _initialCrateCount, _storageAreaCount;
};

}  // namespace SB
