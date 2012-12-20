#ifndef BRAINBOT_HPP_INCLUDED
#define BRAINBOT_HPP_INCLUDED

#include "GameObject.hpp"
#include "../pathing/NavGrid.hpp"

class BrainBot : public GameObject
{
  //! FUNCTIONS
public:
  static CollisionMask* createMask(NavGrid const* grid_);
  static ObjectView* createView(fV3 position_);

  //! ATTRIBUTES
private:

  //! METHODS
public:
  // constructors
  BrainBot(fV3 position_, NavGrid const* grid_);
};

#endif // BRAINBOT_HPP_INCLUDED
