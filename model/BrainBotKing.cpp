#include "BrainBotKing.hpp"

#include "../engine/io/GraphicsManager.hpp"

//! ----------------------------------------------------------------------------
//! GLOBAL VARIABLES
//! ----------------------------------------------------------------------------
static Texture *t = NULL;
static Colour bot_emissive(1.0f, 1.0f, 1.0f);

//! ----------------------------------------------------------------------------
//! FUNCTIONS
//! ----------------------------------------------------------------------------

void BrainBotKing::load_texture()
{
  t= GraphicsManager::getInstance()->get_texture("alien_bot2");
}

//! ----------------------------------------------------------------------------
//! OVERRIDES
//! ----------------------------------------------------------------------------


#include <iostream>

void attract(BrainBotKing* king, BrainBot* minion)
{
  fV2 to_me = king->getPosition() - minion->getPosition();

  if(to_me.getNorm2() > 64*64)
    minion->speed += to_me*0.03f;
  else
    minion->speed -= to_me*0.07f;
}

void repulse(BrainBot* a, BrainBot* b)
{
  fV2 a_to_b = b->position - a->position;
  if(a_to_b.getNorm2() < 64*64)
  {
    a->speed -= a_to_b*0.01f;
    b->speed += a_to_b*0.01f;
  }

}

void BrainBotKing::move(fV2 amount, NavGrid* grid)
{
  BrainBot::move(amount, grid);

  // for each minion
  for(std::list<BrainBot*>::iterator i = minions.begin(); i != minions.end(); i++)
  {
    // for each minion -- attraction
    attract(this, (*i));

    // for each pair of minions -- repulsion
    std::list<BrainBot*>::iterator j = i;
    j++;
    for(; j != minions.end(); j++)
      repulse((*i),(*j));

    // move minions
    (*i)->move(fV2(), grid);
  }
}

Texture* BrainBotKing::get_texture()
{
  return t;
}
