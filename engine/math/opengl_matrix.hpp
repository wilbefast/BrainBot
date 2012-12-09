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

#ifndef OPENGL_MATRIX_HPP_INCLUDED
#define OPENGL_MATRIX_HPP_INCLUDED

#include "../opengl.h"
#include "V3.hpp"
#include "M44.hpp"

void printGLMatrix(GLenum which_matrix);
void applyTransform(M44<GLfloat> const& transform);

void addTranslation(M44<GLfloat>& transform, fV3 trans);
void addRotation(M44<GLfloat>& transform, float angle);
void addScale(M44<GLfloat>& transform, fV3 scale);

#endif // OPENGL_MATRIX_HPP_INCLUDED
