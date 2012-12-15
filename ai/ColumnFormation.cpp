
#include "../ai/ColumnFormation.hpp"

ColumnFormation::ColumnFormation(uV2 size_) : Formation(size_) {
}

ColumnFormation::~ColumnFormation() {
}

// ---- Overriden ---------------------------------------------------------------------
// ---- Formation managment -----------------------------------------------------------
uV2 ColumnFormation::assignPosition(BrainBot* member) {
    uV2 newRelativePosition;

    if(lastPositionAssigned.x == 0 && lastPositionAssigned.y == 0) {
        newRelativePosition = lastPositionAssigned;
    } else {
        if(lastPositionAssigned.x == size.x) {
            newRelativePosition = uV2(0, lastPositionAssigned.y + 1);
        } else {
            newRelativePosition = uV2(lastPositionAssigned.x + 1, lastPositionAssigned.y);
        }
    }

    assignments[member] = newRelativePosition;
    lastPositionAssigned = newRelativePosition;

    return lastPositionAssigned;
}

uV2 ColumnFormation::assignLeaderPosition(BrainBot* leader) {
    return uV2(0, 0);
}
