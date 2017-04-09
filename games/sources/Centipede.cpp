//
// Created by thauvi_a on 4/6/17.
//

#include <ctime>
#include "Centipede.h"

bool arcade::Centipede::isPlayerAlive() {
  return _alive;
}

bool arcade::Centipede::move_player(void) {
  return (true);
}

void arcade::Centipede::play() {

}

void arcade::Centipede::shoot() {
  if (_shoot && _shoot->getAlive())
    return;
  else
    _shoot = new arcade::Missile(_posPerso[0]);
}

void arcade::Centipede::goDown() {
  _tower->goDown();
}

void arcade::Centipede::goUp() {
  _tower->goUp();
}

void arcade::Centipede::goLeft() {
  _tower->goLeft();
}

void arcade::Centipede::goRight() {
  _tower->goRight();
}

size_t arcade::Centipede::getScore(void) const {
  return _score;
}

std::string arcade::Centipede::getGamesName(void) const {
  return _name;
}

void arcade::Centipede::restart(void) {
}

bool arcade::Centipede::isPlayerWin(void) const {
  return true;
}

arcade::Vector2u arcade::Centipede::getDimension(void) const {
  return _dim;
}

arcade::Map const *arcade::Centipede::getMap(void) const {
  return _map;
}

std::vector <arcade::Vector2u> const &arcade::Centipede::getPos() const {
  return _posPerso;
}

arcade::Centipede::Centipede(arcade::Vector2u const &dim) {
  std::srand(std::time(0));
  _posPerso.push_back(arcade::Vector2u(dim.x / 2, dim.y - 4));
  _map   = new arcade::Map(dim);
  _tower = new arcade::Personnage();
  _centi.push_back(new arcade::Personnage());
  setchampi();
  _map->setPosBlock(arcade::Vector2u(1, 1), arcade::Map::Centi);
  _map->setPosBlock(arcade::Vector2u(2, 1), arcade::Map::Centi);
  _map->setPosBlock(arcade::Vector2u(3, 1), arcade::Map::Centi);
  _map->setPosBlock(arcade::Vector2u(4, 1), arcade::Map::Centi);
  _map->setPosBlock(arcade::Vector2u(dim.x / 2, dim.y - 4),
                    arcade::Map::Player);
  _dim = dim;
}

bool arcade::Centipede::updateGame() {
  std::vector<Vector2u>::iterator it;
  arcade::Direction               dir;
  arcade::Vector2u                newPos;

  dir = _tower->getDir();
  it  = _posPerso.begin();
  switch (dir) {
    case D_UP :
      if (it->y > 15) {
        newPos.x = it->x;
        newPos.y = it->y - 1;
      }
      break;
    case D_DOWN :
      newPos.x = it->x;
      newPos.y = it->y + 1;
      break;
    case D_RIGHT :
      newPos.x = it->x + 1;
      newPos.y = it->y;
      break;
    case D_LEFT :
      newPos.x = it->x - 1;
      newPos.y = it->y;
      break;
    default:
      newPos = *it;
      break;
  }
  _tower->goNone();
  if (_map->getPosBlock(newPos) == arcade::Map::Enemy) {
    return false;
  }
  if (_map->getPosBlock(newPos) == arcade::Map::Empty) {
    _posPerso.pop_back();
    _posPerso.insert(it, newPos);
    _tower->setPos(_posPerso);
  }
  if (_shoot && _shoot->getAlive()) {
    _shoot->go();
    if (_map->getPosBlock(_shoot->getPos()) == arcade::Map::Empty) {
      _map->setPosBlock(Vector2u(_shoot->getPos().x, _shoot->getPos().y + 1),
                        Map::Empty);
      _map->setPosBlock(_shoot->getPos(), Map::Centi);
    } else {
      switch (_map->getPosBlock(_shoot->getPos())) {
        case Map::Object :
          _map->setPosBlock(_shoot->getPos(), Map::Empty);
          _map->setPosBlock(
                  Vector2u(_shoot->getPos().x, _shoot->getPos().y + 1),
                  Map::Empty);
          _shoot->setAlive(false);
          break;
        case Map::Block :
          _map->setPosBlock(
                  Vector2u(_shoot->getPos().x, _shoot->getPos().y + 1),
                  Map::Empty);
          _shoot->setAlive(false);
          break;
        default :
          break;
      }
    }
  }
  if (!move_centi())
    return false;
  _map->clear();
  for (it = _posPerso.begin(); it != _posPerso.end(); it++) {
    _map->setPosBlock(*it, arcade::Map::Player);
  }
  return true;
}

void arcade::Centipede::setchampi() {
  for (unsigned int y = 1; y < 19; ++y) {
    for (unsigned int x = 1; x < 19; ++x) {
      if ((std::rand() % 20) == 0)
        _map->setPosBlock(arcade::Vector2u(x, y), arcade::Map::Object);
    }
  }
}

bool arcade::Centipede::move_centi() {
  // if ((_map->getPosBlock(_posCenti[0]) == Map::Block) ||
  //     (_map->getPosBlock(_posCenti[0]) == Map::Object))
  //   {
  //     _posCenti[0].y -= 1;

  //   }

  return (true);
}

extern "C" {
arcade::IGame *createGame(arcade::Vector2u const &dim) {
  (void) dim;
  return (new arcade::Centipede(dim));
}
}
  
