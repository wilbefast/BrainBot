#ifndef GROUP_HPP_INCLUDED
#define GROUP_HPP_INCLUDED

#include <vector>

#include "../model/NavGrid.hpp"
#include "../model/GameObject.hpp"
#include "../ai/Formation.hpp"

class Group : public GameObject
{
public:
  Group(fV3 position_, NavGrid* grid_);
  virtual ~Group();

// ---- Accessors --------------------------------------------------------------

  std::vector<GameObject*> getMembers() { return members; }
  void setMembers(std::vector<GameObject*> val) { members = val; }
  void addMember(GameObject* member) { members.push_back(member); }

  GameObject* getLeader() { return leader; }
  void setLeader(GameObject* leader_) { leader = leader_; }

  Formation* getFormation() { return formation; }
  void setFormation(Formation* formation_) { formation = formation_; }


// ---- Formation managment ----------------------------------------------------

  void assembleFormation();

  void setDirection(fV3 direction_);


// ---- Overrides GameObject ---------------------------------------------------

  void push(fV3 direction);
  int update(float t_delta);
  void draw();


private:
  std::vector<GameObject*> members;
  GameObject* leader;
  Formation* formation;
  NavGrid* grid;
  fV3 direction;
};

#endif // GROUP_HPP_INCLUDED
