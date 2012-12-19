#include "BrainBot.hpp"

#include "../engine/math/wjd_math.h"
#include "../engine/math/opengl_matrix.hpp"

#include "../view/Mesh3DView.hpp"

//! ----------------------------------------------------------------------------
//! CONSTRUCTOR
//! ----------------------------------------------------------------------------
BrainBot::BrainBot(fV3 position_) :
GameObject(position_, new Mesh3DView(position_, 3.0f, "spider"), NULL)
{

}
