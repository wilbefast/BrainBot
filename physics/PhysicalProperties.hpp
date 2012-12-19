#ifndef PHYSICALPROPERTIES_HPP_INCLUDED
#define PHYSICALPROPERTIES_HPP_INCLUDED

class PhysicalProperties
{
  //! ATTRIBUTES
public:
  float max_speed, friction, acceleration;

  //! METHODS
public:
  // constructors
  PhysicalProperties(float max_speed_, float friction_, float acceleration_) :
  max_speed(max_speed_), friction(friction_), acceleration(acceleration_)
  {
  }
};

#endif // PHYSICALPROPERTIES_HPP_INCLUDED
