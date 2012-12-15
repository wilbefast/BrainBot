#ifndef FORMATION_HPP_INCLUDED
#define FORMATION_HPP_INCLUDED

#include <map>

#include "../engine/math/V2.hpp"
#include "../model/BrainBot.hpp"

class Formation {

    public:
        Formation(uV2 size_);
        virtual ~Formation();

// ---- Accessors ---------------------------------------------------------------------
        fV2 getSpotSize() { return spotSize; }
        void setSpotSize(fV2 spotSize_) { spotSize = spotSize_; }


// ---- Formation managment -----------------------------------------------------------
        virtual uV2 assignPosition(BrainBot* member) = 0;
        virtual uV2 assignLeaderPosition(BrainBot* leader) = 0;

    protected:
        uV2 size;
        uV2 lastPositionAssigned;
        std::map<BrainBot*, uV2> assignments;
        fV2 spotSize;

};

#endif // FORMATION_HPP_INCLUDED
