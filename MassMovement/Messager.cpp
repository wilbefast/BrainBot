#include "Messager.h"

namespace Troopy {
namespace MultiAgentSystem {

Messager::Messager(std::string name) : Nameable(name) {
}


Messager::~Messager() {
	while(!messageQueue.empty()) {
		messageQueue.pop();
	}
}

bool Messager::sendMessage(Communication message) {
	Blackboard::pushMessage(message);
}

void Messager::addMessage(Communication message) {
	messageQueue.push(message);
}

void Messager::checkMessages() {
	while(!messageQueue.empty()) {
		process(messageQueue.front());
		messageQueue.pop();
	}
}

}
}
