#ifndef NAVGRIDVIEW_HPP_INCLUDED
#define NAVGRIDVIEW_HPP_INCLUDED

#include "../model/NavGrid.hpp"

class NavGridView
{
  //! ATTRIBUTES
private:
  NavGrid * navGrid;

  //! METHODS
public:
  // constructors, destructors
  NavGridView(NavGrid * navGrid_);
  virtual ~NavGridView();
  // mutators
  void draw();
};

#endif // NAVGRIDVIEW_HPP_INCLUDED
