#ifndef NAVGRIDVIEW_HPP_INCLUDED
#define NAVGRIDVIEW_HPP_INCLUDED

#include "../pathing/NavGrid.hpp"

class NavGridView
{
  //! ATTRIBUTES
private:
  NavGrid *grid;

  //! METHODS
public:
  // constructors, destructors
  NavGridView(NavGrid *grid_);
  virtual ~NavGridView();
  // mutators
  void draw();
};

#endif // NAVGRIDVIEW_HPP_INCLUDED
