/* ************************************************************************** *
 *   Map.cpp
 *                                                       :::      ::::::::    *
 *                                                     :+: :+:    :+:    :+:  *
 *                                                    +:+   +:+   +:+    +:+  *
 *   By: THEIS Paul                                  +#++:++#++:  +#++:++#+   *
 *                                                   +#+     +#+  +#+         *
 *   Created: 04/04/17                               #+#     #+#  #+#         *
 *   Updated: 04/04/17                               #+#     #+#  #+#         *
 *   Project: cpp_arcade
 * ************************************************************************** */

#include "Map.hpp"

arcade::Map::Map(Vector2u const &dim) : _dim(dim) {
  _map = new CaseMap*[dim.y];
  for (unsigned int i = 0; i < dim.y;++i) {
    _map[i] = new CaseMap[dim.x];
  }
  create();
}

arcade::Map::~Map() {
  for (unsigned int i = 0; i < _dim.y; ++i) {
    delete _map[i];
  }
  delete _map;
}

arcade::Map::Map(arcade::Map const &other) {
  _dim = other.getMapSize();

  _map = new CaseMap*[_dim.y];
  for (unsigned int i = 0; i < _dim.y;++i) {
    _map[i] = new CaseMap[_dim.x];
  }
}

arcade::Map &arcade::Map::operator=(arcade::Map const &other) {
  (void)other;
  return (*this);
}

void arcade::Map::create() {
  Vector2u tmp;

  for (tmp.y = 0; tmp.y < _dim.y; ++tmp.y){
    for (tmp.x = 0; tmp.x < _dim.x; ++tmp.x) {
      if (tmp.x == 0 || tmp.y == 0 || tmp.y == _dim.y-1 || tmp.x == _dim.x-1)
        _map[tmp.y][tmp.x] = Block;
      else
        _map[tmp.y][tmp.x] = Empty;
    }
  }
}

arcade::Map::CaseMap arcade::Map::getPosBlock(Vector2u const& pos) const {
  return _map[pos.y][pos.x]; //TODO: ERROR CHECK
}

void arcade::Map::setPosBlock(Vector2u const& pos, arcade::Map::CaseMap casemap) {
  _map[pos.y][pos.x] = casemap;
}

arcade::Vector2u arcade::Map::getMapSize() const {
  return _dim;
}

void arcade::Map::createObject() {

}