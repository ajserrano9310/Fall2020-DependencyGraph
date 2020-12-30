 /* 
 * Author: Alejandro Serrano
 * Prof.: Peter Jensen
 * Assignment 03: Droplist
 * October 12, 2020
 * 
 * The node class that will hold the data and
* a reference node next for the next pointer. Also
* contains a vector of nodes. Each index will similarly
* hold a reference to a next node, though not linearly.
 */

#include "node.h"
#include <iostream>

namespace cs3505 {

  node::node(const std::string & s)
    :data(s), next(NULL)
    {
    }

  node::~node()
  {
   // The string_set classe handles the destruction of the
   // node objects. 
  }

  void node::set_max_width(int max_width)
  {
    this->max_width = max_width;
    // we set the vector nodes to the width calculated
    // in the string_set class. 
    (*this).vector_nodes.resize(max_width);
  }
  int node::get_max_width()
  {
    return max_width;
  }

}

