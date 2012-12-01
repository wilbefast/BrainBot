#include "NavProperty.h"

namespace Troopy {
namespace Navigation {

NavProperty::NavProperty() {
	p = objectNavProperty::WALKABLE;
}

NavProperty::NavProperty(objectNavProperty p_) : p(p_) {
}

NavProperty::~NavProperty() {
}

objectNavProperty NavProperty::getProperty() {
	return p;
}

void NavProperty::setProperty(objectNavProperty p_) {
	p = p_;
}

}
}