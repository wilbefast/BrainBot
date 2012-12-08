#include "StrategyCamera.hpp"

#include "../engine/opengl.h"

#define PITCH 30
#define MAX_Z -30


#include <stdio.h>

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

void StrategyCamera::pan(fV3 amount)
{
  position += amount;
  if(position.z > MAX_Z)
    position.z = MAX_Z;
}


//! OPENGL

void StrategyCamera::lookThrough() const
{
glRotatef(-PITCH, 1.0f, 0.0f, 0.0f);
  glTranslatef(position.x, position.y, position.z);

}
