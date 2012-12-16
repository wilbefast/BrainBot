#include "BrainBotKing.hpp"

#include "../engine/io/GraphicsManager.hpp"
#include "../engine/io/MeshManager.hpp"

//! ----------------------------------------------------------------------------
//! GLOBAL VARIABLES
//! ----------------------------------------------------------------------------
static Mesh3D* m = NULL;
static Texture* t = NULL;


//! ----------------------------------------------------------------------------
//! FUNCTIONS
//! ----------------------------------------------------------------------------

void BrainBotKing::load_assets()
{
  t= GraphicsManager::getInstance()->get_texture("alien_bot2");
  m= MeshManager::getInstance()->get_mesh("spider");
}

//! ----------------------------------------------------------------------------
//! OVERRIDES
//! ----------------------------------------------------------------------------


void attract(BrainBotKing* king, BrainBot* minion)
{
  fV2 to_me = king->getPosition() - minion->getPosition();

  if(to_me.getNorm2() > 64*64)
    minion->speed += to_me*0.015f;
  else
    minion->speed -= to_me*0.035f;
}

void repulse(BrainBot* a, BrainBot* b)
{
  fV2 a_to_b = b->position - a->position;
  if(a_to_b.getNorm2() < 64*64)
  {
    a->speed -= a_to_b*0.008f;
    b->speed += a_to_b*0.008f;
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


void BrainBotKing::render()
{
  glPushMatrix();

    glTranslatef(position.x, position.y, -50);
    glScalef(5, 5, 5);

    m->draw();
  glPopMatrix();
}
