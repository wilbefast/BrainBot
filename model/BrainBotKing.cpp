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

Texture* BrainBotKing::get_texture()
{
  return t;
}
