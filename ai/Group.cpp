#include "Group.hpp"

#include "../engine/opengl.h"

Group::Group(fV3 position_, NavGrid* grid_) :
GameObject(position_),
grid(grid_),
direction(1,0,0) // face right
{
}

Group::~Group()
{
  //! Delete formation? Shared?

  //! draw each member of the group
  for(std::vector<GameObject*>::iterator i = members.begin();
  i != members.end(); i++)
    delete (*i);
}

// ---- Formation managment ----------------------------------------------------

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


void Group::setDirection(fV3 direction_)
{
  direction = direction_;
  direction.normalise();
}

// ---- Overriden --------------------------------------------------------------

void Group::push(fV3 push_direction)
{
  GameObject::push(push_direction * 10.0f);
}

int Group::update(float t_delta)
{

  //! update each member of the group
  for(std::vector<GameObject*>::iterator i = members.begin();
  i != members.end(); i++)
  {
    // push the members towards the centre of the group
    fV3 direction = (position - (*i)->getPosition());
    direction.normalise();

    (*i)->push(direction);

    // call the members' update functions
    (*i)->update(t_delta);
  }

  //! group is still alive (return 0)
  return 0;
}

void Group::draw()
{
  //! draw each member of the group
  for(std::vector<GameObject*>::iterator i = members.begin();
  i != members.end(); i++)
  {
    (*i)->draw();
  }

  //! debug draw position and direction

  fV3 front_position = position + (direction*32.0f);
  glDisable(GL_LIGHTING);
    glBegin(GL_LINE_LOOP);
      glVertex3fv(position.front());
      glVertex3fv(front_position.front());
    glEnd();
  glEnable(GL_LIGHTING);
}
