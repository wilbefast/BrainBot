#include "GameObject.h"

namespace Troopy {
namespace Navigation {

GameObject::GameObject(float x_, float y_, float z_) : posX(x_), posY(y_), posZ(z_), NavProperty() {
}


GameObject::~GameObject() {
	posX = 0.0f;
	posY = 0.0f;
	posZ = 0.0f;
}

float GameObject::getPosition(Troopy::Axis axis) const {
	switch(axis) {
		case 0:
			return posX;
		case 1:
			return posY;
		case 2:
			return posZ;
		default:
			return -666.0f;
	}
}

void GameObject::setPosition(Troopy::Axis axis, float amount) {
	switch(axis) {
		case 0:
			posX = amount;
			break;
		case 1:
			posY = amount;
			break;
		case 2:
			posZ = amount;
			break;
	}
}

}
}