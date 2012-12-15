#ifndef NAVCELL_H_INCLUDED
#define NAVCELL_H_INCLUDED

#include "../engine/math/V2.hpp"
#include "../engine/math/V3.hpp"

class NavCell
{
  //! FRIENDS
friend class NavGrid;
friend class NavGridView;
friend class PathSearch;
friend class SearchState;

  //! CONSTANTS
public:
  static const fV3 size;

  //! ATTRIBUTES
private:
  uV2 grid_position;
  unsigned int cost;
  bool obstacle;

  //! METHODS
public:
  NavCell(uV2 grid_position_, bool obstacle_ = false, unsigned int cost_ = 0);
  virtual ~NavCell();
};

#endif // NAVCELL_H_INCLUDED
