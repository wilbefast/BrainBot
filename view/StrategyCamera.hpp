#ifndef STRATEGYCAMERA_HPP
#define STRATEGYCAMERA_HPP

#include "../engine/math/M44.hpp"
#include "../engine/math/V2.hpp"

class StrategyCamera
{
  /* ATTRIBUTES */
private:
  fM44 transform;
  fV3 speed;

  /* METHODS */
public:
  // constructors
  StrategyCamera();
  virtual ~StrategyCamera();

  // mutators
  void push(fV3 amount);
  void centreOver(fV2 position);
  void update_position();

  // opengl
  void lookThrough(); //const;
};

#endif // STRATEGYCAMERA_HPP
