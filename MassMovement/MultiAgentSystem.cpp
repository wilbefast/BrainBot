#include "MultiAgentSystem.h"

namespace Troopy {
namespace MultiAgentSystem {

MultiAgentSystem::MultiAgentSystem(int numberOfThreads_) {
}


MultiAgentSystem::~MultiAgentSystem() {
	threads.clear();
	agents.clear();
}

int MultiAgentSystem::mainLoop() {
	bool goOn = true;

	while(goOn) {
		for(int i = 0; i < agents.size(); i = i + threads.size()) {
			for(int t = 0; t < threads.size(); t++) {
				//pthread_create(&threads[t], NULL, &(agents[i].run), NULL);
			}
		}
	}

	return 0;
}

void MultiAgentSystem::addAgents(Agent agent, int numberOfCopies) {
	for(int i = 0; i < numberOfCopies; i++) {
		agents.push_back(agent.clone());
	}
}

}
}