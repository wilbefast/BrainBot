#ifndef STRATEGYCAMERA_HPP
#define STRATEGYCAMERA_HPP


#include "../engine/math/V3.hpp"
#include "../engine/math/V2.hpp"

class StrategyCamera
{
  /* ATTRIBUTES */
private:
  fV3 position;

  /* METHODS */
public:
  // constructors
  StrategyCamera();
  virtual ~StrategyCamera();

  // mutators
  void pan(fV3 amount);
  void zoom(float amount);

  // opengl
  void lookThrough() const;
};

#endif // STRATEGYCAMERA_HPP
