#pragma once

#include <vector>
#include "../engine/math/V3.hpp"
#include "../engine/math/Rect.hpp"

#include "GameObject.h"
#include "NavProperty.h"

namespace Troopy {
namespace Navigation {

class NavGrid {
	public:
		NavGrid(fV3 origin_, unsigned int numberOfCols_, unsigned int numberOfRows_,
            float cellHeight_, float cellSize_);
		virtual ~NavGrid();

		void generateGrid(std::vector<GameObject>& objects);
		fV3 getAbsoluteCellPosition(uV2 position) const;
		NavProperty getCell(uV2 position);
		uV2 whatCell(fV2 position) const;
		uRect getApproximateFootprint(GameObject& o);
		uV2 getSize() const;
		fV3 getOrigin() const;
		unsigned int getCellSize() const;

	private:
    fV3 origin;
    unsigned int numberOfRows;
		unsigned int numberOfCols;
		float cellSize;
		float cellHeight;
		NavProperty **grid;
		float yMargin;
};

}
}

