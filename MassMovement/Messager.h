#pragma once

#include <queue>
#include "Communication.h"
#include "Nameable.h"
#include "Blackboard.h"

namespace Troopy {
namespace MultiAgentSystem {

class Messager : public Nameable {
	public:
		Messager(std::string name);
		virtual ~Messager();

		bool sendMessage(Communication message);
		void checkMessages();
		virtual void process(Communication message);
		void addMessage(Communication message);

	protected:
		std::queue<Communication> messageQueue;
		static Blackboard blackboard;
};

}
}

