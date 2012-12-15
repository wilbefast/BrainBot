
#include "../ai/Formation.hpp"

Formation::Formation(uV2 size_) {
    size = size_;
    lastPositionAssigned = uV2(666, 666);
}

Formation::~Formation() {
}
