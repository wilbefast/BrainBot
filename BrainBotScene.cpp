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

#include "BrainBotScene.hpp"

#include "engine/debug/assert.h"
#include "engine/debug/log.h"

#include "engine/global.hpp"
#include "engine/io/MeshManager.hpp"
#include "engine/graphics/draw.hpp"

#include "game_objects/GameObject.hpp"
#include "formations/BrainBotGroup.hpp"

#include "engine/math/V3.hpp"

#define PAN_SPEED 20
#define ZOOM_SPEED 200

#define GRID_N_ROWS 64
#define GRID_N_COLS 64
#define GRID_SIZE uV2(GRID_N_COLS, GRID_N_ROWS)
#define GRID_ORIGIN fV3(0, 0, 0)

#define MAZE_TUNNEL_SIZE 5
#define MAZE_PERCENT_BROKEN_WALLS 33

#define START_N_MINIONS 2

using namespace std;


//! GLOBAL VARIABLES

static std::deque<NavCell*>* testpath = NULL;

/// CREATION, DESTRUCTION

BrainBotScene::BrainBotScene() :
GameState(),
// grid
grid(GRID_ORIGIN, GRID_SIZE, MAZE_TUNNEL_SIZE, MAZE_PERCENT_BROKEN_WALLS),
gridView(&grid),
// objects
player(NULL),
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

int BrainBotScene::startup()
{
  // basic startup
  ASSERT(GameState::startup() == EXIT_SUCCESS,
        "BrainBotScene starting GameState");

  // load the 3D scene
  draw::use3D();
  MeshManager::getInstance()->startup();

  // create game objects
  fV3 map_centre((GRID_N_COLS+1)*NavCell::SIZE.x*0.5f,
                  (GRID_N_ROWS+1)*NavCell::SIZE.y*0.5f, 0);
  //player = new BrainBot(map_centre, &grid);
  player = new BrainBotGroup(map_centre, &grid);

  // set up the lighting
  glShadeModel(GL_SMOOTH);
  GLfloat light_pos[4] = { map_centre.x, map_centre.y, 1000.0f, 1.0f};
  GLfloat light_diffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
  GLfloat light_ambient[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
  glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

  // test path
  testpath = grid.getPath(uV2(3,3), uV2(GRID_N_COLS/2, GRID_N_ROWS/2));

  // all clear
  return EXIT_SUCCESS;
}

int BrainBotScene::shutdown()
{
  // basic shutdown
  ASSERT(GameState::shutdown() == EXIT_SUCCESS,
        "BrainBotScene stopping GameState");

  // free memory
  delete player;

  // all clear
  return EXIT_SUCCESS;
}

/// OVERRIDES GAMESTATE

int BrainBotScene::update(float t_delta)
{
  // move camera
  static fV3 camera_move, player_move;
    camera_move = fV3(0, 0, 0);
    player_move = fV3(0, 0, 0);

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

  // Push the player with the keyboard
  if(player_move.x || player_move.y)
  {
    player->push(player_move);
    player->setDirection(player_move);
  }

  // Update the player position and follow with the camera
  player->update(t_delta);
  camera.centreOver(player->getPosition());

  // Get the mouse
  static fV2 pointed;
  pointed = input.last_hover;
  pointed.x -= camera.transform[3].x;
  pointed.y -= camera.transform[3].y;

  // All clear
  return CONTINUE;
}

int BrainBotScene::trigger(int which, bool pressed)
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


void BrainBotScene::draw()
{
  // clear and reset
  glPushMatrix();
    camera.lookThrough();
    gridView.draw();

    /*current_bot = first_bot;
    do
    {
      current_bot->render();
      current_bot = (BrainBot*)current_bot->getNext();
    }
    while(current_bot != first_bot);*/

    player->draw();

    /*glLineWidth(2.0f);
    glColor3f(1,1,0);
    glBegin(GL_LINE_STRIP);
    for(std::deque<NavCell*>::iterator i = testpath->begin(); i != testpath->end(); i++)
    {
      fV2 node = (*i)->grid_position;

       node.x *= NavCell::SIZE.x; node.x += NavCell::SIZE.x*0.5f;
       node.y *= NavCell::SIZE.y; node.y += NavCell::SIZE.y*0.5f;
      glVertex3f(node.x, node.y, -15);
    }
    glEnd();
*/
  glPopMatrix();
}
