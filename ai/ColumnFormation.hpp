#ifndef COLUMNFORMATION_HPP_INCLUDED
#define COLUMNFORMATION_HPP_INCLUDED

#include "../ai/Formation.hpp"

class ColumnFormation : public Formation {

    public:
        ColumnFormation(uV2 size_);
        virtual ~ColumnFormation();

// ---- Overriden ---------------------------------------------------------------------
// ---- Formation managment -----------------------------------------------------------
        uV2 assignPosition(BrainBot* member);
        uV2 assignLeaderPosition(BrainBot* leader);

};

#endif // COLUMNFORMATION_HPP_INCLUDED
