#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

#include "../engine/math/V2.hpp"

#include "NavGrid.hpp"

class Player
{
public:
  static void load_texture();



private:
  fV2 position, speed;

public:
  Player(fV2 position_);

  fV2 getPosition() const { return position; }

  void move(fV2 amount, NavGrid* grid);
  void render();

};

#endif // PLAYER_HPP_INCLUDED
