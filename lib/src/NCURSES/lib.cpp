//
// lib.cpp for  in /home/cedric/workTek2/cpp_arcade/lib
// 
// Made by Cedric
// Login   <cedric.clemenceau@epitech.eu>
// 
// Started on  Mon Mar 27 23:28:07 2017 Cedric
// Last update Mon Apr  3 23:36:17 2017 Cedric
//

#include "libNCURSES.hpp"
#include <termios.h>
#include <unistd.h>

arcade::GfxNCURSES::GfxNCURSES(Vector2u const& dim) {
  _mainSize = dim;
  initscr();
  cbreak();
  keypad(stdscr, TRUE);
  _input[10] = InputT(InputT::KeyPressed, Input::ENTER, InputT::None);
  _input[27] = InputT(InputT::KeyPressed, Input::ESCAPE, InputT::None);
  _input[122] = InputT(InputT::KeyPressed, Input::UP, InputT::None);
  _input[115] = InputT(InputT::KeyPressed, Input::DOWN, InputT::None);
  _input[100] = InputT(InputT::KeyPressed, Input::RIGHT, InputT::None);
  _input[113] = InputT(InputT::KeyPressed, Input::LEFT, InputT::None);
  _input[65] = InputT(InputT::KeyPressed, Input::UP, InputT::None);
  _input[66] = InputT(InputT::KeyPressed, Input::DOWN, InputT::None);
  _input[67] = InputT(InputT::KeyPressed, Input::RIGHT, InputT::None);
  _input[68] = InputT(InputT::KeyPressed, Input::LEFT, InputT::None);
  _input[32] = InputT(InputT::KeyPressed, Input::SPACE, InputT::None);
  _input[105] = InputT(InputT::KeyPressed, Input::PREV_LIB, InputT::None);
  _input[112] = InputT(InputT::KeyPressed, Input::NEXT_LIB, InputT::None);
  _input[107] = InputT(InputT::KeyPressed, Input::PREV_GAME, InputT::None);
  _input[109] = InputT(InputT::KeyPressed, Input::NEXT_GAME, InputT::None);
  refresh();
  _mainWindow = newwin(dim.y, dim.x, 0, 0);
  _isOpen = true;
}

arcade::GfxNCURSES::~GfxNCURSES() {
  endwin();
  system("clear");
}

void	arcade::GfxNCURSES::setTitleWindow(std::string const &title) {
  (void)title;
}

bool	arcade::GfxNCURSES::isOpen() const {
  return (_isOpen);
}

void	arcade::GfxNCURSES::clear() {
//  wclear(_mainWindow);
}

void              arcade::GfxNCURSES::close() {
  endwin();
  system("clear");
}

void              arcade::GfxNCURSES::setWindowSize(Vector2u const& size) {
  wresize(_mainWindow, size.y, size.x);
}

void           arcade::GfxNCURSES::draw(DrawObject const& obj) {
  Vector2i    pos = obj.getPosition();
  Vector2u    size = obj.getSize();

  mvaddstr(pos.y, pos.x, obj.getText().c_str());
  
  // SDL_SetRenderDrawColor(_renderer, 40, 44, 52, 255 );
}

char getcha() {
  char buf = 0;
  struct termios old = {0};
  if (tcgetattr(0, &old) < 0)
    perror("tcsetattr()");
  old.c_lflag &= ~ICANON;
  old.c_lflag &= ~ECHO;
  old.c_cc[VMIN] = 1;
  old.c_cc[VTIME] = 0;
  if (tcsetattr(0, TCSANOW, &old) < 0)
    perror("tcsetattr ICANON");
  if (read(0, &buf, 1) < 0)
    perror ("read()");
  old.c_lflag |= ICANON;
  old.c_lflag |= ECHO;
  if (tcsetattr(0, TCSADRAIN, &old) < 0)
    perror ("tcsetattr ~ICANON");
  return (buf);
}

arcade::InputT	arcade::GfxNCURSES::getInput() {
  int input = getcha();
  if (_input.find(input) != _input.end())
    {
      InputT in = _input[input];
      in.type = InputT::TextEntered;
      in.unicode = input;
      return (_input[input]);
    }
  return (InputT(InputT::TextEntered, input, input));
}

void	arcade::GfxNCURSES::display() {
  refresh();
  wrefresh(_mainWindow);
}

extern "C" {
arcade::IGFX *createLib(arcade::Vector2u dim) {
  return (new arcade::GfxNCURSES(dim));
}
}
