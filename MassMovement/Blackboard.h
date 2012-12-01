#pragma once

#include <queue>
#include <pthread.h>
#include "Communication.h"

namespace Troopy {
namespace MultiAgentSystem {

class Blackboard {
	public:
		virtual ~Blackboard();

		static void pushMessage(Communication message);

		static Blackboard * getInstance();
		static void destroy();
		static void init();

	protected:
		static std::queue<Communication> highPriorityQueue,
										 midPriorityQueue,
										 lowPriorityQueue;
		static Blackboard * instance;
		pthread_t messageThread;

		Blackboard();
		static void * blackboardRun(void * data);
		static void processMessage(Communication message);
};

}
}

