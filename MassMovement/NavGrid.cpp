#include "NavGrid.h"

namespace Troopy {
namespace Navigation {

NavGrid::NavGrid(int numberOfCols_, int numberOfRows_)
	: numberOfRows(numberOfRows_), numberOfCols(numberOfCols_) {
		grid.reserve(numberOfCols * numberOfRows);
}

void NavGrid::generateGrid(std::vector<GameObject> objects) {
	std::vector<int> collidableCells;

	for(int o = 0; 0 < objects.size(); o++) {
		collidableCells = getWheelBase(objects[o]);
		for(int i = 0; i < collidableCells.size(); i++)
			grid[collidableCells[i]].setProperty(ObjectNavProperty::OBSTACLE);
	}
}

float NavGrid::getAbsoluteCellPosition(Axis axis, int i, int j) const {
	switch(axis) {
		case Axis::X:
			return base_x + i * cellSize;
		case Axis::Y:
			return base_y + i * cellSize;
		case Axis::Z:
			return 0.0f;
	}
}

std::vector<int> NavGrid::getAverageWheelBase(GameObject e) {
	std::vector<int> result;
	float localObjectX = e.getPosition(Axis::X) - base_x;
	float localObjectY = e.getPosition(Axis::Y) - base_y;

	int firstCellIndex = whatCell(localObjectX, localObjectY);

	int objectDiscreteSizeX = e.getSize(Axis::X) / cellSize;
	int objectDiscreteSizeY = e.getSize(Axis::Y) / cellSize;

	return result;
}

std::vector<int> NavGrid::getWheelBase(GameObject e) {
	std::vector<int> result = getAverageWheelBase(e);
	float row, col;

	for(int k = 0; k < result.size(); k++) {
		if(e.collide(getCell(result[k], Axis::X), getCell(result[k], Axis::Y))) {
			result.erase(result.begin() + k);
		}
	}

	return result;
}

NavProperty NavGrid::getCell(int i, int j) {
	return grid[i + j * numberOfCols];
}

float NavGrid::getCell(int i, Axis axis) {
	if(axis == Axis::X) {
		return (i / numberOfCols) * cellSize + base_x;
	} else if(axis == Axis::Y) {
		return (i % numberOfCols) * cellSize + base_y;
	}

	return 666.0f;
}

int NavGrid::whatCell(float x_, float y_) const {
	int i = x_ / cellSize;
	int j = y_ / cellSize;

	return i + j * numberOfCols;
}

NavGrid::~NavGrid() {
	numberOfRows = 0;
	numberOfCols = 0;
	grid.clear();
}

}
}