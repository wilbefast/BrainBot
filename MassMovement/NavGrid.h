#pragma once

#include <vector>
#include "GameObject.h"

namespace Troopy {
namespace Navigation {

class NavGrid {
	public:
		NavGrid(int numberOfCols_, int numberOfRows_);
		virtual ~NavGrid();

		void generateGrid(std::vector<GameObject> objects);
		float getAbsoluteCellPosition(Axis axis, int i, int j) const;
		NavProperty getCell(int i, int j);
		float getCell(int i, Axis axis);
		int whatCell(float x_, float y_) const;
		std::vector<int> getAverageWheelBase(GameObject e);
		std::vector<int> getWheelBase(GameObject e);

	private:
		int numberOfCols;
		int numberOfRows;
		float cellSize;
		std::vector<NavProperty> grid;
		float base_x;
		float base_y;
		float yMargin;
};

}
}

