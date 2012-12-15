#ifndef BRAINBOTKING_HPP_INCLUDED
#define BRAINBOTKING_HPP_INCLUDED

#include "BrainBot.hpp"

#include <list>

class BrainBotKing : public BrainBot
{
public:
  static void load_assets();


  /* ATTRIBUTES */
  std::list<BrainBot*> minions;

  /* METHODS */
  // constructors
  BrainBotKing(fV2 position_ ) : BrainBot(position_), minions() { }

  // override
  void move(fV2 amount, NavGrid* grid);
  Texture* get_texture();
  //void render();
};

#endif // BRAINBOTKING_HPP_INCLUDED
