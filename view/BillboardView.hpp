#ifndef BILLBOARDVIEW_HPP_INCLUDED
#define BILLBOARDVIEW_HPP_INCLUDED

#include "ObjectView.hpp"
#include "../engine/graphics/Texture.hpp"

class BillboardView : public ObjectView
{
//! ATTRIBUTES
private:
  Texture* texture;
  fV3 position;
  size_t size;

//! METHODS
public:
  // constructors, destructors
  BillboardView(fV3 position, size_t size_, const char* texture_name);
  virtual ~BillboardView();
  // render
  void draw() const;
  // mutators
  void setPosition(fV3 position_);
};


#endif // BILLBOARDVIEW_HPP_INCLUDED
