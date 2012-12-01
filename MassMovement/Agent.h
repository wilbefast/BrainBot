#pragma once

#include <string>
#include <pthread.h>
#include "Messager.h"
#include "Behaviour.h"

namespace Troopy {
namespace MultiAgentSystem {

class Agent : public Messager {
	public:
		Agent clone();
		Agent(std::string name);
		virtual ~Agent();

		void * run(void * data);

		void setBehaviour(Behaviour * behaviour_);
		Behaviour * getBehaviour() const;

	protected:
		Behaviour * behaviour;
};

}
}

