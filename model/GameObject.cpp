#include "GameObject.h"

namespace Troopy {
namespace Navigation {

GameObject::GameObject(fV3 position_, fV3 size_, ObjectNavProperty navProperty_) :
                       position(position_), size(size_),
                       navProperty(navProperty_) {
}


GameObject::~GameObject() {
}

fV3 GameObject::getPosition() const {
	return position;
}

fV3 GameObject::getSize() const {
	return size;
}

void GameObject::setPosition(fV3 position_) {
	position = position_;
}


bool GameObject::isColliding(GameObject& other) const
{
  //! FIXME
  return false;

}

}
}
