#include "NavProperty.h"

namespace Troopy {
namespace Navigation {

NavProperty::NavProperty() {
	p = WALKABLE;
}

NavProperty::NavProperty(ObjectNavProperty p_) : p(p_) {
}

NavProperty::~NavProperty() {
}

ObjectNavProperty NavProperty::getProperty() {
	return p;
}

void NavProperty::setProperty(ObjectNavProperty p_) {
	p = p_;
}

}
}
