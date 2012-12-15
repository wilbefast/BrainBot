#ifndef BRAINBOTKING_HPP_INCLUDED
#define BRAINBOTKING_HPP_INCLUDED

#include "BrainBot.hpp"

class BrainBotKing : public BrainBot
{
public:
  static void load_texture();


  /* ATTRIBUTES */
  std::list<BrainBot*> minions;

  /* METHODS */
  // constructors
  BrainBotKing(fV2 position_ ) : BrainBot(position_), minions() { }

  // override
  void move(fV2 amount, NavGrid* grid);
  Texture* get_texture();
};

#endif // BRAINBOTKING_HPP_INCLUDED
