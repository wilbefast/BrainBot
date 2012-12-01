#pragma once

#include <string>
#include "Nameable.h"

namespace Troopy {
namespace MultiAgentSystem {

class Behaviour : public Nameable {
	public:
		Behaviour(std::string name);
		virtual ~Behaviour();

		virtual bool run(void * data);
};

}
}
