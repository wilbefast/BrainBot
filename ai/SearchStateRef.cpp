#include "SearchStateRef.hpp"

//! ----------------------------------------------------------------------------
//! CONSTRUCTORS, DESTRUCTORS
//! ----------------------------------------------------------------------------

SearchStateRef::SearchStateRef(SearchState* state_) :
state(state_)
{
}

//! ----------------------------------------------------------------------------
//! OPERATORS
//! ----------------------------------------------------------------------------

bool SearchStateRef::operator<(SearchStateRef const& other) const
{
  return (*state < *(other.state) );
}

bool SearchStateRef::operator>(SearchStateRef const& other) const
{
  return (*state > *(other.state) );
}

bool SearchStateRef::operator<=(SearchStateRef const& other) const
{
  return (*state <= *(other.state) );
}

bool SearchStateRef::operator>=(SearchStateRef const& other) const
{
  return (*state >= *(other.state) );
}

bool SearchStateRef::operator==(SearchStateRef const& other) const
{
  return (*state == *(other.state) );
}
