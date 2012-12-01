#include "Agent.h"

namespace Troopy {
namespace MultiAgentSystem {

Agent Agent::clone() {
	return Agent(name);
}

Agent::Agent(std::string name) : Messager(name) {
}

Agent::~Agent() {
}

void * Agent::run(void * data) {
	checkMessages();

	behaviour->run(data);
}

void Agent::setBehaviour(Behaviour * behaviour_) {
}

Behaviour * Agent::getBehaviour() const {
}

}
}
