#ifndef NAVGRIDVIEW_HPP_INCLUDED
#define NAVGRIDVIEW_HPP_INCLUDED

#include "../model/NavGrid.h"

namespace Troopy {
namespace Navigation {

class NavGridView {
  private:
    NavGrid * navGrid;

  public:
    NavGridView(NavGrid * navGrid_);
    virtual ~NavGridView();

    void render();
};

}
}

#endif // NAVGRIDVIEW_HPP_INCLUDED
