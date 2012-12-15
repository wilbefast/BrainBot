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

#ifndef MASSMOVEMENT_HPP_INCLUDED
#define MASSMOVEMENT_HPP_INCLUDED

#include "engine/math/V3.hpp"
#include "engine/scenes/GameState.hpp"

#include "model/NavGrid.hpp"
#include "model/BrainBotKing.hpp"
#include "model/BrainBot.hpp"

#include "view/NavGridView.hpp"
#include "view/StrategyCamera.hpp"

#include "ai/ColumnFormation.hpp"
#include "ai/Group.hpp"


class MassMovement : public GameState
{
  /// ATTRIBUTES
private:
  // grid
  NavGrid grid;
  NavGridView gridView;

  // objects
  BrainBotKing player;
  BrainBot *first_bot, *current_bot;

  //Group group;
  //ColumnFormation* column;

  // camera controls
  StrategyCamera camera;
  bool left, right, up, down, forward, backward;

  /// METHODS
public:
  // Creation, destruction
  MassMovement();
  int startup();
  int shutdown();
  // Overrides GameState
  int update(float delta);
  int trigger(int which, bool pressed);
  void draw();
};

#endif // MASSMOVEMENTSCENE_HPP_INCLUDED
