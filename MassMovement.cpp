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

#include "engine/math/V2.hpp"

#define PAN_SPEED 20
#define ZOOM_SPEED 200

#define GRID_N_ROWS 64
#define GRID_N_COLS 64
#define GRID_ORIGIN fV3(0, 0, 0)

using namespace std;

/// CREATION, DESTRUCTION

MassMovement::MassMovement() :
GameState(),
// grid
grid(GRID_ORIGIN, uV2(GRID_N_COLS, GRID_N_ROWS)),
gridView(&grid),
// objects
player(fV2(20, 20)),
first_bot(NULL),
group(fV2(50, 50), &grid),
// camera controls
camera(),
left(false),
right(false),
up(false),
down(false),
forward(false),
backward(false)
{
}

int MassMovement::startup() {
    // basic startup
    ASSERT(GameState::startup() == EXIT_SUCCESS,
        "MassMovement starting GameState");

    BrainBot::load_texture();


    // load the 3D scene
    draw::use3D();
    MeshManager::getInstance()->startup();


    // create the objects

    column = new ColumnFormation(uV2(2, 8));
    column->setSpotSize(fV2(30.0f, 30.0f));
    group.setFormation(column);

    fV2 p(0, 0), d(32, 32);
    first_bot = current_bot = new BrainBot(p);
    group.setLeader(first_bot);


    for(int i = 1; i < 17; i++) {
        p += d;
        BrainBot* newbie = new BrainBot(p);
        group.addMember(newbie);
        first_bot->newNext(newbie);
    }

    group.assembleFormation();

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
  static fV2 player_move;
    player_move = fV2(0, 0);

  if(up) camera_move.z -= ZOOM_SPEED;
  if(down) camera_move.z += ZOOM_SPEED;

  /*if(forward) camera_move.y -= PAN_SPEED;
  if(backward) camera_move.y += PAN_SPEED;
  if(left) camera_move.x -= PAN_SPEED;
  if(right) camera_move.x += PAN_SPEED;*/

  if(forward) player_move.y -= 1;
  if(backward) player_move.y += 1;
  if(left) player_move.x -= 1;
  if(right) player_move.x += 1;

  // Apply the camera movement
  camera.push(camera_move);
  up = down = false;
  camera.update_position();

  // Move the player
  player.move(player_move, &grid);
  camera.centreOver(player.getPosition());

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
    gridView.draw();

    current_bot = first_bot;
    do
    {
      current_bot->render();
      current_bot = (BrainBot*)current_bot->getNext();
    }
    while(current_bot != first_bot);

    player.render();

  glPopMatrix();

  // Draw dynamic game objects
  GameState::draw();
}
