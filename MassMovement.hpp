#ifndef MASSMOVEMENT_HPP_INCLUDED
#define MASSMOVEMENT_HPP_INCLUDED

#include "engine/math/V3.hpp"
#include "engine/scenes/GameState.hpp"

#include "model/NavGrid.h"

#include "view/NavGridView.hpp"
#include "view/StrategyCamera.hpp"

class MassMovement : public GameState
{
  /// ATTRIBUTES
private:
  StrategyCamera camera;
  Troopy::Navigation::NavGrid grid;
  Troopy::Navigation::NavGridView gridView;
  bool left, right, up, down, forward, backward;

  /// METHODS
public:
  // Creation, destruction
  MassMovement();
  int startup();
  int shutdown();
  // Overrides GameState
  int update(float delta);
  int trigger(int which, bool pressed);
  void draw();
};

#endif // MASSMOVEMENTSCENE_HPP_INCLUDED
