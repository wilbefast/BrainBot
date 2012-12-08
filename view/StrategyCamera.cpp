#include "StrategyCamera.hpp"

#include "../engine/opengl.h"

#define PITCH 30


//! CONSTRUCTORS, DESTRUCTORS

StrategyCamera::StrategyCamera() :
position(0, 0, -200)
{
  //ctor
}

StrategyCamera::~StrategyCamera()
{
  //dtor
}


//! MUTATORS


static int rot = 0;

void StrategyCamera::pan(fV3 amount)
{
  rot++;
  position += amount;
}


//! OPENGL

void StrategyCamera::lookThrough() const
{
glRotatef(-PITCH, 1.0f, 0.0f, 0.0f);
  glTranslatef(position.x, position.y, position.z);

}
