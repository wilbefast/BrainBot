#ifndef BRAINBOT_HPP_INCLUDED
#define BRAINBOT_HPP_INCLUDED

#include "../engine/math/V2.hpp"

#include "../engine/utils/IntrusiveLinked.hpp"

#include "NavGrid.hpp"

class BrainBot : public IntrusiveLinked
{
public:
  static void load_texture();



private:
  fV2 position, speed;

public:
  BrainBot(fV2 position_);

  fV2 getPosition() const { return position; }

  void move(fV2 amount, NavGrid* grid);
  void render();

  virtual Texture* get_texture();

};

#endif // BRAINBOT_HPP_INCLUDED