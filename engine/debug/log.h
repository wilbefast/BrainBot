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

#ifndef LOG_HPP_INCLUDED
#define LOG_HPP_INCLUDED

#ifdef __ANDROID__
	#define LOG_INFO ANDROID_LOG_INFO
	#define LOG_WARN ANDROID_LOG_WARN
	#define LOG_ERROR ANDROID_LOG_ERROR
#else // LINUX, MAC, WINDOWS
  #define LOG_INFO 0
	#define LOG_WARN 1
	#define LOG_ERROR 2
#endif // #ifdef __ANDROID__

void log(unsigned int level, const char* format, ...);

#endif // LOG_HPP_INCLUDED
