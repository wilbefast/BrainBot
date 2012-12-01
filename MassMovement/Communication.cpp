#include "Communication.h"

namespace Troopy {
namespace MultiAgentSystem {

Communication::Communication(Messager emitter_, Messager recipient_, ComPriority priority_) : emitter(emitter_), priority(priority_), recipient(recipient_) {
}


Communication::~Communication() {
}

Messager Communication::getEmitter() {
	return emitter;
}

Messager Communication::getRecipient() {
	return recipient;
}

ComPriority Communication::getPriority() {
	return priority;
}

}
}
