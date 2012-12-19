#include "Group.hpp"

Group::Group(fV3 position_, NavGrid* grid_) :
GameObject(position_),
grid(grid_)
{
}

Group::~Group()
{
  //! Delete formation? Shared?
}

// ---- Formation managment -----------------------------------------------------------

/*void Group::assembleFormation() {
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
}*/


// ---- Overriden ---------------------------------------------------------------------

void Group::push(fV3 direction)
{
  GameObject::push(direction);
}

int Group::update(float t_delta)
{

  //! update each member of the group
  for(std::vector<GameObject*>::iterator i = members.begin();
  i != members.end(); i++)
  {
    (*i)->update(t_delta);
  }
}

void Group::draw()
{
  //! draw each member of the group
  for(std::vector<GameObject*>::iterator i = members.begin();
  i != members.end(); i++)
  {
    (*i)->draw();
  }
}
