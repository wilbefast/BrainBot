#ifndef BRAINBOT_HPP_INCLUDED
#define BRAINBOT_HPP_INCLUDED

#include "../engine/math/V2.hpp"

#include "../engine/utils/IntrusiveLinked.hpp"

#include "NavGrid.hpp"

class BrainBot : public IntrusiveLinked
{
public:
  static void load_texture();


  fV2 position, speed;

  BrainBot(fV2 position_);

  fV2 getPosition() const { return position; }

  virtual void move(fV2 amount, NavGrid* grid);
  void render();

  virtual Texture* get_texture();

};

#endif // BRAINBOT_HPP_INCLUDED
