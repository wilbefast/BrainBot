#include "MassMovement.hpp"

#include "engine/debug/assert.h"
#include "engine/debug/log.h"

#include "engine/global.hpp"
#include "engine/io/MeshManager.hpp"
#include "engine/graphics/draw.hpp"

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
  MeshManager::getInstance()->mesh.load_obj("assets/knight.obj");

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

  if(up) camera_move.z -= 5;
  if(down) camera_move.z += 5;
  if(forward) camera_move.y -= 1;
  if(backward) camera_move.y += 1;
  if(left) camera_move.x += 1;
  if(right) camera_move.x -= 1;

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
    MeshManager::getInstance()->mesh.draw();
  glPopMatrix();

  // Draw dynamic game objects
  GameState::draw();
}
