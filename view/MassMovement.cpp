#include "MassMovement.hpp"

#include "../engine/debug/assert.h"
#include "../engine/debug/log.h"

#include "../engine/global.hpp"
#include "../engine/io/MeshManager.hpp"
#include "../engine/graphics/draw.hpp"

#define TURN_SPEED 1

#define GRID_N_ROWS 64
#define GRID_N_COLS 64
#define GRID_H 32.0f
#define GRID_ORIGIN fV3(0, 0, 0)
#define GRID_CELL_SIZE 2.0f

using namespace std;

/// CREATION, DESTRUCTION

MassMovement::MassMovement() :
GameState(),
camera(),
grid(GRID_ORIGIN, GRID_N_COLS, GRID_N_ROWS, GRID_H, GRID_CELL_SIZE),
gridView(&grid),
left(false),
right(false),
up(false),
down(false),
alt(false),
space(false),
ctrl(false)
{
}

int MassMovement::startup()
{
  // basic startup
  ASSERT(GameState::startup() == EXIT_SUCCESS,
        "MassMovement starting GameState");

  // load the 3D scene
  draw::use3D();
  //MeshManager::getInstance()->mesh.load_obj("assets/rubik.obj");

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

  if(space) camera_move.z -= 1;
  if(ctrl) camera_move.z += 1;
  if(up) camera_move.y -= 1;
  if(down) camera_move.y += 1;
  if(left) camera_move.x += 1;
  if(right) camera_move.x -= 1;

  // Apply the camera movement
  camera.pan(camera_move);

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
		case SDLK_SPACE: space = pressed; break;
		case SDLK_LCTRL: ctrl = pressed; break;
		case SDLK_LALT: alt = pressed; break;
		case SDLK_UP: up = pressed; break;
		case SDLK_DOWN: down = pressed; break;
		case SDLK_LEFT: left = pressed; break;
		case SDLK_RIGHT: right = pressed; break;
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
  glPopMatrix();

  // Draw dynamic game objects
  GameState::draw();
}
