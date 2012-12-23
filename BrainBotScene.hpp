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

#ifndef BRAINBOTSCENE_HPP_INCLUDED
#define BRAINBOTSCENE_HPP_INCLUDED

#include "engine/math/V3.hpp"
#include "engine/scenes/GameState.hpp"

#include "pathing/NavGridMaze.hpp"

#include "game_objects/BrainBot.hpp"

#include "view/NavGridView.hpp"
#include "view/StrategyCamera.hpp"

#include "formations/Group.hpp"


class BrainBotScene : public GameState
{
  /// ATTRIBUTES
private:
  // grid
  NavGridMaze grid;
  NavGridView gridView;

  // objects
  Group* player;

  // camera controls
  StrategyCamera camera;
  bool left, right, up, down, forward, backward;

  /// METHODS
public:
  // Creation, destruction
  BrainBotScene();
  int startup();
  int shutdown();
  // Overrides GameState
  int update(float delta);
  int trigger(int which, bool pressed);
  void draw();
};

#endif // BRAINBOTSCENE_HPP_INCLUDED
