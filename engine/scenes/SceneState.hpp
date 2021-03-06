/*
Arrogance Engine: a simple SDL/OpenGL game engine for Desktop and Android.
Copyright (C) 2012 William James Dyce

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SCENESTATE_HPP_INCLUDED
#define SCENESTATE_HPP_INCLUDED

#include "Input.hpp"
#include "Button.hpp"
#include "../math/V2.hpp"

class SceneState
{
  /// NESTING
public:
  enum UpdateResult
  {
      CONTINUE,
      EXIT
  };

  /// FRIENDS
  friend class Scene;

  /// ATTRIBUTES
protected:
  // Input management
  Input input;

  /// METHODS
public:
  // Constructors, destructors
  SceneState();
  virtual ~SceneState();
  // Explicit startup code, if needed
  virtual int startup();
  virtual int shutdown();
  // Update and draw dynamic objects, if needed
  virtual int update(float delta);
  virtual int trigger(int key, bool pressed);
  virtual void draw();
  // Input
  Input* getInput();
  // Input -- mouse or touch-pad
  void setCursor(uV2 new_cursor_position, bool new_clicking);
  str_id releasedOnButton();
  bool newClick() const;
  // Input -- keyboard
};

#endif // SCENESTATE_HPP_INCLUDED
