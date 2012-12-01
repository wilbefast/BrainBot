#pragma once

#include "NavProperty.h"

namespace Troopy {

typedef enum Axis {
	X = 0,
	Y = 1,
	Z = 2
} Axis;

namespace Navigation {

class GameObject : public Navigation::NavProperty {
	public:
		GameObject(float x_, float y_, float z_);
		virtual ~GameObject();

		float getPosition(Axis axis) const;
		void setPosition(Axis axis, float amount);

		virtual float getSize(Axis axis) const;
		virtual bool collide(float posX, float posY) const;

	protected:
		float posX, posY, posZ;
};

}
}