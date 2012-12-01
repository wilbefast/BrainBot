#include "Blackboard.h"

namespace Troopy {
namespace MultiAgentSystem {

Blackboard::Blackboard() {
	pthread_attr_t attr;
	struct sched_param parm;
	pthread_attr_getschedparam(&attr, &parm);
	parm.sched_priority = sched_get_priority_max(SCHED_FIFO);;
	pthread_attr_setschedpolicy(&attr, SCHED_FIFO);
	pthread_attr_setschedparam(&attr, &parm);

	pthread_create(&messageThread, NULL, blackboardRun, NULL);

	pthread_attr_getschedparam(&attr, &parm);
	parm.sched_priority = sched_get_priority_min(SCHED_FIFO);
	pthread_attr_setschedpolicy(&attr, SCHED_FIFO);
	pthread_attr_setschedparam(&attr, &parm);

	pthread_join(messageThread, NULL);
}


Blackboard::~Blackboard() {
	destroy();
}

Blackboard * Blackboard::getInstance() {
	if(instance == NULL) {
		instance = new Blackboard();
	}

	return instance;
}

void Blackboard::init() {
	if(instance == NULL) {
		instance = new Blackboard();
	}
}

void Blackboard::destroy() {
	delete instance;
}

void * Blackboard::blackboardRun(void * data) {
	while(!highPriorityQueue.empty()) {
		processMessage(highPriorityQueue.front());
		highPriorityQueue.pop();
	}
	while(!midPriorityQueue.empty()) {
		processMessage(midPriorityQueue.front());
		midPriorityQueue.pop();
	}
	while(!lowPriorityQueue.empty()) {
		processMessage(lowPriorityQueue.front());
		lowPriorityQueue.pop();
	}
}

void Blackboard::processMessage(Communication message) {
	message.getRecipient().addMessage(message);
}

void Blackboard::pushMessage(Communication message) {
	switch(message.getPriority()) {
		case 2:		// HIGH
			highPriorityQueue.push(message);
			break;
		case 1:		// MID
			midPriorityQueue.push(message);
			break;
		case 0:		// LOW
			lowPriorityQueue.push(message);
			break;
	}
}

}
}
