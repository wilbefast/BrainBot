#include "BrainBot.hpp"

#include "../engine/math/wjd_math.h"
#include "../engine/math/opengl_matrix.hpp"

#include "../view/Mesh3DView.hpp"
#include "../physics/GridCollider.hpp"

#define ACCELERATION 0.4f
#define MAX_SPEED 3.0f
#define FRICTION 0.9f

//! ----------------------------------------------------------------------------
//! FUNCTIONS
//! ----------------------------------------------------------------------------
CollisionMask* BrainBot::createMask(NavGrid const* grid_)
{
  return
    new GridCollider(10, grid_, PhysicalProperties(MAX_SPEED, FRICTION, ACCELERATION));
}

ObjectView* BrainBot::createView(fV3 position_)
{
  return
    new Mesh3DView(position_, 3.0f, "spider");
}

//! ----------------------------------------------------------------------------
//! CONSTRUCTOR
//! ----------------------------------------------------------------------------
BrainBot::BrainBot(fV3 position_, NavGrid const* grid_) :
GameObject(position_, createView(position_), createMask(grid_))
{

}
