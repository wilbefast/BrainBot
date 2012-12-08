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

#pragma once

#include <vector>
#include "../engine/math/V3.hpp"
#include "../engine/math/Rect.hpp"

#include "GameObject.h"
#include "NavCell.hpp"

namespace Troopy {
namespace Navigation {

class NavGrid {
	public:
		NavGrid(fV3 origin_, unsigned int numberOfCols_, unsigned int numberOfRows_,
            float cellHeight_, float cellSize_);
		virtual ~NavGrid();

		void generateGrid(std::vector<GameObject>& objects);
		fV3 getAbsoluteCellPosition(uV2 position) const;
		NavCell getCell(uV2 position);
		uV2 whatCell(fV2 position) const;
		uRect getApproximateFootprint(GameObject& o);
		uV2 getSize() const;
		fV3 getOrigin() const;
		unsigned int getCellSize() const;

	private:
    fV3 origin;
    unsigned int numberOfRows;
		unsigned int numberOfCols;
    float cellHeight;
		float cellSize;
		NavCell **grid;
		float yMargin;
};

}
}

