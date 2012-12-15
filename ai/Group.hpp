#ifndef GROUP_H
#define GROUP_H

#include <vector>

#include "../model/BrainBot.hpp"
#include "../ai/Formation.hpp"

class Group : public BrainBot {

    public:
        Group(fV2 position_, NavGrid* grid_);
        virtual ~Group();

// ---- Accessors ---------------------------------------------------------------------

        std::vector<BrainBot*> getMembers() { return members; }
        void setMembers(std::vector<BrainBot*> val) { members = val; }
        void addMember(BrainBot* member) { members.push_back(member); }

        BrainBot* getLeader() { return leader; }
        void setLeader(BrainBot* leader_) { leader = leader_; }

        Formation* getFormation() { return formation; }
        void setFormation(Formation* formation_) { formation = formation_; }


// ---- Formation managment -----------------------------------------------------------

        void assembleFormation();


// ---- Overriden ---------------------------------------------------------------------

        void move(fV2 amount, NavGrid* grid);


    private:
        std::vector<BrainBot*> members;
        BrainBot* leader;
        Formation* formation;
        NavGrid* grid;
};

#endif // GROUP_H
