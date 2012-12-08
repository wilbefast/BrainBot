#include "ModelViewState.hpp"

#include "../debug/assert.h"
#include "../global.hpp"
#include "../io/MeshManager.hpp"

#include "../graphics/draw.hpp"
#include "../debug/log.h"

#define TURN_SPEED 1

#define GRID_N_ROWS 64
#define GRID_N_COLS 64
#define GRID_H 32.0f
#define GRID_ORIGIN fV3(0, 0, 0)
#define GRID_CELL_SIZE 2.0f

using namespace std;

/// CREATION, DESTRUCTION

ModelViewState::ModelViewState() :
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

int ModelViewState::startup()
{
  // basic startup
  ASSERT(GameState::startup() == EXIT_SUCCESS,
        "ModelViewState starting GameState");

  // load the 3D scene
  draw::use3D();

  // all clear
  return EXIT_SUCCESS;
}

int ModelViewState::shutdown()
{
  // basic shutdown
  ASSERT(GameState::shutdown() == EXIT_SUCCESS,
        "ModelViewState stopping GameState");

  // all clear
  return EXIT_SUCCESS;
}

/// OVERRIDES GAMESTATE

int ModelViewState::update(float delta)
{
  // move camera
  static fV3 camera_move;
    camera_move = fV3(0, 0, 0);
  static float camera_angle;
    camera_angle = 0.0f;

  if(space) camera_move.y -= 0.5f;
  if(ctrl) camera_move.y += 0.5f;
  if(up) camera_move.z += 0.5f;
  if(down) camera_move.z -= 0.5f;

  if(left)
  {
    if(alt)
      camera_move.x += 0.5f;
    else
      camera_angle -= 1.0f;
  }
  if(right)
  {
    if(alt)
      camera_move.x -= 0.5f;
    else
      camera_angle += 1.0f;
  }

  // Apply the camera movement
  camera.turn(camera_angle);
  camera.pan(camera_move);

  // Update dynamic game objects
  int result = GameState::update(delta);
  if(result != CONTINUE)
    return result;

  // All clear
  return CONTINUE;
}

int ModelViewState::trigger(int which, bool pressed)
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


void ModelViewState::draw()
{
  // clear and reset
  glPushMatrix();
    camera.lookThrough();
    gridView.render();
  glPopMatrix();

  // Draw dynamic game objects
  GameState::draw();
}
