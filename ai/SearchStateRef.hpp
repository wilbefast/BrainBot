#ifndef SEARCHSTATEREF_HPP_INCLUDED
#define SEARCHSTATEREF_HPP_INCLUDED

#include "SearchState.hpp"

class SearchStateRef
{
public:
  SearchState *state;

public:
  // constructors, destructors
  SearchStateRef(SearchState* state_);

  // operators -- for priority queue
  bool operator<(SearchStateRef const& other) const;
  bool operator>(SearchStateRef const& other) const;
  bool operator<=(SearchStateRef const& other) const;
  bool operator>=(SearchStateRef const& other) const;
  bool operator==(SearchStateRef const& other) const;

};

#endif // SEARCHSTATEREF_HPP_INCLUDED
