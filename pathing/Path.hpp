#ifndef PATH_HPP_INCLUDED
#define PATH_HPP_INCLUDED

#include <deque>

#include "NavCell.hpp"

typedef std::deque<NavCell*> path_t;
typedef path_t::iterator path_it;

#endif // PATH_HPP_INCLUDED
