#ifndef OBJECTVIEW_HPP_INCLUDED
#define OBJECTVIEW_HPP_INCLUDED

#include "../engine/math/V3.hpp"

//! ***ABSTRACT***
class ObjectView
{
//! INTERFACE
public:
  // destructors
  virtual ~ObjectView() {}
  // render
  virtual void draw() const = 0;
  // mutators
  virtual void setPosition(fV3 position) = 0;
};

#endif // OBJECTVIEW_HPP_INCLUDED
