#include "NavCell.hpp"

//! CONSTRUCTORS, DESTRUCTORS

NavCell::NavCell(bool obstacle_, unsigned int cost_) :
cost(cost_),
obstacle(obstacle_)
{
  //ctor
}

NavCell::~NavCell()
{
  //dtor
}
