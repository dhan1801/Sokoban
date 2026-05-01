// Copyright 2025 Dhanvika Nakka
#include "Sokoban.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stack>
#include <SFML/Audio.hpp>

namespace SB {

Sokoban::Sokoban()
    : _width(0), _height(0), _playerPos(0, 0), _playerTileUnder('.'),
      _lastMoveDir(Direction::Down), _hasWon(false),
      _initialCrateCount(0), _storageAreaCount(0) {
  loadTextures();
}

void Sokoban::loadTextures() {
  std::vector<std::pair<char, std::string>> textureFiles = {
      {'#', "images/Blocks/block_06.png"},
      {'.', "images/Ground/ground_01.png"},
      {'A', "images/Crates/crate_03.png"},
      {'a', "images/Ground/ground_04.png"}
  };

  for (auto& [ch, path] : textureFiles) {
    if (!_textures[ch].loadFromFile(path)) {
      std::cerr << "Failed to load texture: " << path << std::endl;
    }
    _sprites[ch].setTexture(_textures[ch]);
  }

  std::map<Direction, std::string> playerDirs = {
      {Direction::Up, "images/Player/player_08.png"},
      {Direction::Down, "images/Player/player_05.png"},
      {Direction::Left, "images/Player/player_20.png"},
      {Direction::Right, "images/Player/player_17.png"},
  };

  for (const auto& [dir, path] : playerDirs) {
    if (!_playerTextures[dir].loadFromFile(path)) {
      std::cerr << "Failed to load player texture: " << path << std::endl;
    }
    _playerSprites[dir].setTexture(_playerTextures[dir]);
  }

  _victoryBuffer.loadFromFile("sounds/victory.wav");
  _victorySound.setBuffer(_victoryBuffer);
}

int Sokoban::width() const { return _width; }
int Sokoban::height() const { return _height; }
sf::Vector2i Sokoban::playerLoc() const { return _playerPos; }
std::vector<std::string> Sokoban::getGrid() const { return _grid; }

bool Sokoban::isValidMove(int x, int y) const {
  return (x >= 0 && x < _width && y >= 0 && y < _height && _grid[y][x] != '#');
}

bool Sokoban::canPushBox(int x, int y, Direction dir, int& newBoxX, int& newBoxY) const {
  switch (dir) {
    case Direction::Up:    newBoxX = x; newBoxY = y - 1; break;
    case Direction::Down:  newBoxX = x; newBoxY = y + 1; break;
    case Direction::Left:  newBoxX = x - 1; newBoxY = y; break;
    case Direction::Right: newBoxX = x + 1; newBoxY = y; break;
  }
  return (newBoxX >= 0 && newBoxX < _width && newBoxY >= 0 && newBoxY < _height) &&
         (_grid[newBoxY][newBoxX] != '#' && _grid[newBoxY][newBoxX] != 'A');
}

void Sokoban::movePlayer(Direction dir) {
  if (_hasWon) return;

  int dx = 0, dy = 0;
  switch (dir) {
    case Direction::Up:    dy = -1; break;
    case Direction::Down:  dy = 1;  break;
    case Direction::Left:  dx = -1; break;
    case Direction::Right: dx = 1;  break;
  }

  int newX = _playerPos.x + dx;
  int newY = _playerPos.y + dy;

  if (!isValidMove(newX, newY)) return;

  _undoStack.push({_grid, _playerPos, _playerTileUnder});
  while (!_redoStack.empty()) _redoStack.pop();
  _lastMoveDir = dir;

  if (_grid[newY][newX] == 'A') {
    int newBoxX, newBoxY;
    if (!canPushBox(newX, newY, dir, newBoxX, newBoxY)) return;
    _grid[newY][newX] = (_originalGrid[newY][newX] == 'a') ? 'a' : '.';
    _grid[newBoxY][newBoxX] = 'A';
  }

  _grid[_playerPos.y][_playerPos.x] = _playerTileUnder;
  _playerTileUnder = (_originalGrid[newY][newX] == 'a') ? 'a' : '.';
  _playerPos = {newX, newY};
  checkVictory();
}

void Sokoban::checkVictory() {
  for (int y = 0; y < _height; ++y) {
    for (int x = 0; x < _width; ++x) {
      if (_originalGrid[y][x] == 'a' && _grid[y][x] != 'A') {
        _hasWon = false;
        return;
      }
    }
  }
  _hasWon = true;
  _victorySound.play();
}

bool Sokoban::isWon() const { return _hasWon; }

bool Sokoban::loadLevel(const std::string& path) {
  std::ifstream in(path);
  if (!in) return false;

  std::vector<std::string> lines;
  std::string line;
  size_t maxWidth = 0;
  while (std::getline(in, line)) {
    maxWidth = std::max(maxWidth, line.size());
    lines.push_back(line);
  }

  for (auto& l : lines) {
    if (l.size() < maxWidth) {
      l.append(maxWidth - l.size(), '.');
    }
  }

  _grid = lines;
  _originalGrid = lines;
  _height = _grid.size();
  _width = static_cast<int>(maxWidth);
  _hasWon = false;
  _undoStack = {};
  _redoStack = {};

  for (int y = 0; y < _height; ++y) {
    for (int x = 0; x < _width; ++x) {
      if (_grid[y][x] == '@') {
        _playerPos = {x, y};
        _playerTileUnder = '.';
        _grid[y][x] = '.';
      }
    }
  }

  return true;
}


void Sokoban::undo() {
  if (_undoStack.empty()) return;
  _redoStack.push({_grid, _playerPos, _playerTileUnder});
  auto state = _undoStack.top(); _undoStack.pop();
  _grid = state.grid;
  _playerPos = state.pos;
  _playerTileUnder = state.tileUnder;
}

void Sokoban::redo() {
  if (_redoStack.empty()) return;
  _undoStack.push({_grid, _playerPos, _playerTileUnder});
  auto state = _redoStack.top(); _redoStack.pop();
  _grid = state.grid;
  _playerPos = state.pos;
  _playerTileUnder = state.tileUnder;
}

}  // namespace SB
