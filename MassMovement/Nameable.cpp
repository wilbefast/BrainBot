#include "Nameable.h"

namespace Troopy {

Nameable::Nameable(std::string name_) : name(name_) {
}


Nameable::~Nameable() {
	name.clear();
}

void Nameable::setName(std::string name_) {
	name = name_;
}
	
std::string Nameable::getName() const {
	return name;
}

}
