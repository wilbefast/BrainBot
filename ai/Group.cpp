#include "Group.hpp"

Group::Group(fV2 position_, NavGrid* grid_) : BrainBot(position_), grid(grid_) {
}

Group::~Group() {
    delete leader;
    delete formation;
}

// ---- Formation managment -----------------------------------------------------------

void Group::assembleFormation() {
    uV2 tmpRelativePosition;

    if(formation != NULL) {
        for(unsigned int i = 0; i < members.size(); i++) {
            tmpRelativePosition = formation->assignPosition(members[i]);
            members[i]->setPosition(fV2(tmpRelativePosition.x * formation->getSpotSize().x + position.x,
                                 tmpRelativePosition.y * formation->getSpotSize().y + position.y));
        }

        tmpRelativePosition = formation->assignLeaderPosition(leader);
        leader->setPosition(fV2(tmpRelativePosition.x * formation->getSpotSize().x + position.x,
                         position.y - formation->getSpotSize().y));
    }
}


// ---- Overriden ---------------------------------------------------------------------

void Group::move(fV2 amount, NavGrid* grid) {
}
