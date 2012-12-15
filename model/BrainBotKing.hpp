#ifndef BRAINBOTKING_HPP_INCLUDED
#define BRAINBOTKING_HPP_INCLUDED

#include "BrainBot.hpp"

class BrainBotKing : public BrainBot
{
public:
  static void load_texture();

  // constructors
  BrainBotKing(fV2 position_ ) : BrainBot(position_) { }

  // override
  Texture* get_texture();
};

#endif // BRAINBOTKING_HPP_INCLUDED
