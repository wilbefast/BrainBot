#pragma once

#include "NavProperty.h"
#include "../engine/math/V3.hpp"

namespace Troopy {
namespace Navigation {

class GameObject : public Navigation::NavProperty {
	public:
		GameObject(fV3 position_, fV3 size_, ObjectNavProperty = OBSTACLE);
		virtual ~GameObject();

		fV3 getPosition() const;
		void setPosition(fV3);

		fV3 getSize() const;
    bool isColliding(GameObject& other) const;

	protected:
		fV3 position, size;
		ObjectNavProperty navProperty;
};

}
}
