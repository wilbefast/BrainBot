#include "NavGrid.h"
#include "NavProperty.h"

namespace Troopy {
namespace Navigation {

uV2 NavGrid::getSize() const {
  return uV2(numberOfCols, numberOfRows);
}

unsigned int NavGrid::getCellSize() const {
  return cellSize;
}

NavGrid::NavGrid(fV3 origin_, unsigned int numberOfCols_,
                 unsigned int numberOfRows_, float cellHeight_, float cellSize_)
	: origin(origin_), numberOfRows(numberOfRows_), numberOfCols(numberOfCols_),
    cellHeight(cellHeight_), cellSize(cellSize_) {

    grid = new ObjectNavProperty*[numberOfRows];

    for(unsigned int r = 0; r < numberOfRows; r++)
      grid[r] = new ObjectNavProperty[numberOfCols];
}

fV3 NavGrid::getOrigin() const {
  return origin;
}

void NavGrid::generateGrid(std::vector<GameObject>& objects) {

  for(size_t row = 0; row < numberOfRows; row++)
  for(size_t col = 0; col < numberOfCols; col++)
  {
      grid[row][col] = WALKABLE; //(rand()%2) ? OBSTACLE : WALKABLE;
  }


	/*for(unsigned int o = 0; 0 < objects.size(); o++) {

	  GameObject& obstacle = objects[o];
		uRect approximateFootprint = getApproximateFootprint(obstacle);


		for(unsigned int r = approximateFootprint.y;
        r < approximateFootprint.y + approximateFootprint.h; r++) {
      for(unsigned int c = approximateFootprint.x;
        c < approximateFootprint.x + approximateFootprint.w; c++)
        {
          GameObject cell(fV3(c*cellSize, r*cellSize, origin.z),
                          fV3(cellSize, cellSize, cellHeight));

          if(cell.isColliding(obstacle))
            grid[r][c]->setProperty(ObjectNavProperty.OBSTACLE);

        }
		}
  }*/
}

fV3 NavGrid::getAbsoluteCellPosition(uV2 position) const {
  return fV3(origin.x + position.x*cellSize,
             origin.y + position.y*cellSize, origin.z);
}

uRect NavGrid::getApproximateFootprint(GameObject& o) {

  fV3 position = o.getPosition(), size = o.getSize();

  unsigned int end_x = position.x + size.x + 1,
               end_y = position.y + size.x + 1,
               w = end_x - (unsigned int)position.x,
               h = end_y - (unsigned int)position.y;

  return uRect(position.x, position.y, w, h);
}

ObjectNavProperty NavGrid::getCell(uV2 position) {
	return grid[position.y][position.x];
}

uV2 NavGrid::whatCell(fV2 position) const {
	return uV2(position.x/cellSize, position.y/cellSize);
}

NavGrid::~NavGrid() {

  for(unsigned int r = 0; r < numberOfRows; r++)
    delete[] grid[r];
  delete[] grid;
}

} // namespace Navigation
} // namespace Troopy
