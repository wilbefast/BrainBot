
#include "../ai/ColumnFormation.hpp"

ColumnFormation::ColumnFormation(uV2 size_) : Formation(size_) {
}

ColumnFormation::~ColumnFormation() {
}

// ---- Overriden ---------------------------------------------------------------------
// ---- Formation managment -----------------------------------------------------------
uV2 ColumnFormation::assignPosition(BrainBot* member) {
    uV2 newRelativePosition;

    if(lastPositionAssigned.x == 666 && lastPositionAssigned.y == 666) {
        newRelativePosition = uV2(0, 0);
    } else {
        if(lastPositionAssigned.x == size.x - 1) {
            lastPositionAssigned.x = 0;
            newRelativePosition = uV2(lastPositionAssigned.x, lastPositionAssigned.y + 1);
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
