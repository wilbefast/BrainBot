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

#include "MassMovement.hpp"

#include "engine/debug/assert.h"
#include "engine/debug/log.h"

#include "engine/global.hpp"
#include "engine/io/MeshManager.hpp"
#include "engine/graphics/draw.hpp"

#include "model/GameObject.hpp"

#define PAN_SPEED 3
#define ZOOM_SPEED 7

#define GRID_N_ROWS 64
#define GRID_N_COLS 64
#define GRID_H 32.0f
#define GRID_ORIGIN fV3(0, 0, 0)
#define GRID_CELL_SIZE 2.0f

using namespace std;

/// CREATION, DESTRUCTION


//! FIXME ----------------------------------------------------------------------
Mesh3D* knight = NULL;
GameObject objects[3] =
{
  GameObject(fV4(100, 100, 0), "knight"),
  GameObject(fV4(200, 200, 0), "knight"),
  GameObject(fV4(200, 200, 0), "knight"),
};
//! ----------------------------------------------------------------------------

MassMovement::MassMovement() :
GameState(),
camera(),
grid(GRID_ORIGIN, GRID_N_COLS, GRID_N_ROWS, GRID_H, GRID_CELL_SIZE),
gridView(&grid),
left(false),
right(false),
up(false),
down(false),
forward(false),
backward(false)
{
}

int MassMovement::startup()
{
  // basic startup
  ASSERT(GameState::startup() == EXIT_SUCCESS,
        "MassMovement starting GameState");

  // load the 3D scene
  draw::use3D();
  MeshManager::getInstance()->startup();
  knight = MeshManager::getInstance()->get_mesh("knight");

  // all clear
  return EXIT_SUCCESS;
}

int MassMovement::shutdown()
{
  // basic shutdown
  ASSERT(GameState::shutdown() == EXIT_SUCCESS,
        "MassMovement stopping GameState");

  // all clear
  return EXIT_SUCCESS;
}

/// OVERRIDES GAMESTATE

int MassMovement::update(float delta)
{
  // move camera
  static fV3 camera_move;
    camera_move = fV3(0, 0, 0);

  if(up) camera_move.z -= ZOOM_SPEED;
  if(down) camera_move.z += ZOOM_SPEED;
  if(forward) camera_move.y -= PAN_SPEED;
  if(backward) camera_move.y += PAN_SPEED;
  if(left) camera_move.x += PAN_SPEED;
  if(right) camera_move.x -= PAN_SPEED;

  // Apply the camera movement
  camera.pan(camera_move);
  up = down = false;

  // Update dynamic game objects
  int result = GameState::update(delta);
  if(result != CONTINUE)
    return result;

  // All clear
  return CONTINUE;
}

int MassMovement::trigger(int which, bool pressed)
{
  switch(which)
  {
		case SDLK_UP: forward = pressed; break;
		case SDLK_DOWN: backward = pressed; break;
		case SDLK_LEFT: left = pressed; break;
		case SDLK_RIGHT: right = pressed; break;

		case SDL_BUTTON_WHEELDOWN: if(pressed) { up = true; down = false; } break;
    case SDL_BUTTON_WHEELUP: if(pressed) { down = true; up = false; } break;
  }

  // All clear
  return CONTINUE;
}


void MassMovement::draw()
{
  // clear and reset
  glPushMatrix();
    camera.lookThrough();
    gridView.render();

    glColor3f(0, 1, 0);
    glScalef(0.4f, 0.4f, 0.4f);
    glTranslatef(0.0f, 0.0f, 3.0f);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    knight->draw();
  glPopMatrix();

  // Draw dynamic game objects
  GameState::draw();
}
