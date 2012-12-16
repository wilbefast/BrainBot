/*
Copyright (C) 2012 William James Dyce and Guillaume Surroca

This program is free software: you can redistribute it and/or modify
it under he terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "StrategyCamera.hpp"

#include "../engine/opengl.h"
#include "../engine/math/opengl_matrix.hpp"



#define PITCH 30
#define MIN_Z 30
#define MAX_Z 1000

#define MAX_SPEED 10.0f
#define MIN_SPEED 0.01f

#include <stdio.h>
using namespace std;

//! ----------------------------------------------------------------------------
//! CONSTRUCTORS, DESTRUCTORS
//! ----------------------------------------------------------------------------

StrategyCamera::StrategyCamera()
{
  transform.toIdentity();
  addTranslation(transform, fV3(0, 0, 600));
  addRotationX(transform, -2*PI);
  //addRotationX(transform, 2*PI);
  //addRotationZ(transform, PI/2);
}

StrategyCamera::~StrategyCamera()
{
  //dtor
}

//! ----------------------------------------------------------------------------
//! MUTATORS
//! ----------------------------------------------------------------------------

void StrategyCamera::push(fV3 amount)
{
  // accelerate
  speed -= amount*0.3f * transform[3].z / (float)(MAX_Z-MIN_Z);

  // cap speed
  for(int i = 0; i < 3; i++)
  {
    if(speed[i] < -MAX_SPEED) speed[i] = -MAX_SPEED;
    else if(speed[i] > MAX_SPEED) speed[i] = MAX_SPEED;
  }
}

void StrategyCamera::centreOver(fV2 position)
{
  transform[3].x = -position.x;
  transform[3].y = -position.y;
}

void StrategyCamera::update_position()
{
  // move
  addTranslation(transform, speed);

  // slow down and stop
  speed *= 0.9f;
  for(int i = 0; i < 3; i++)
  {
    if(speed[i] < 0 && speed[i] > -MIN_SPEED) speed[i] = 0;
    else if(speed[i] > 0 && speed[i] < MIN_SPEED) speed[i] = 0;
  }

  // don't got through the ground
  if(transform[3].z < MIN_Z)
    transform[3].z = MIN_Z;
  else if(transform[3].z > MAX_Z)
    transform[3].z = MAX_Z;
}

//! ----------------------------------------------------------------------------
//! OPENGL
//! ----------------------------------------------------------------------------

void StrategyCamera::lookThrough() //const
{
  //applyTransform(transform);

  glRotatef(180, 0.0f, 1.0f, 0.0f);
  glRotatef(180, 0.0f, 0.0f, 1.0f);
  glTranslatef(transform[3].x, 0, transform[3].z);
    glRotatef(-30, 1, 0, 0);
      glTranslatef(0, transform[3].y, 0);


  //glRotatef(PITCH, 1.0f, 0.0f, 0.0f);
}
