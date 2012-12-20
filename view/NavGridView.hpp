#ifndef NAVGRIDVIEW_HPP_INCLUDED
#define NAVGRIDVIEW_HPP_INCLUDED

#include "../model/NavGrid.hpp"

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

  //! SUBROUTINES
private:
  void draw_all_roads();
  void draw_all_buildings();
};

#endif // NAVGRIDVIEW_HPP_INCLUDED
