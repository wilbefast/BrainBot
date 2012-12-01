#pragma once

#include <vector>
#include <pthread.h>
#include "Agent.h"

namespace Troopy {
namespace MultiAgentSystem {

class MultiAgentSystem {
	public:
		MultiAgentSystem(int numberOfThreads_);
		virtual ~MultiAgentSystem();

		void addAgents(Agent agent, int numberOfCopies);

	protected:
		std::vector<Agent> agents;
		std::vector<pthread_t> threads;

		int mainLoop();
};

}
}

