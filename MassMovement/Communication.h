#pragma once

#include "Messager.h"

namespace Troopy {
namespace MultiAgentSystem {

typedef enum ComPriority {
	HIGH = 2,
	MID  = 1,
	LOW  = 0
} ComPriority;

class Communication{
	public:
		Communication(Messager emitter_, Messager recipient_, ComPriority priority_ = ComPriority::MID);
		virtual ~Communication();

		ComPriority getPriority();
		Messager getEmitter();
		Messager getRecipient();

	protected:
		Messager emitter, recipient;
		ComPriority priority;
};

}
}

