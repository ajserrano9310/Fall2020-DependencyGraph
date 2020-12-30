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

// Guard against double inclusion

#ifndef NODE_H
#define NODE_H
#include <string>
#include <vector>

namespace cs3505
{

  class node
  {
    friend class string_set;   // Allows class string_set to access private members from the node class
			      
    private:
    node(const std::string & data); // constructor
    ~node();                        // destructor

    // class variables
     std::string data;              // holds the string data
     node *next;                    // holds the reference to next
     int max_width;                 // max width of the vector (random for all nodes except head)
     std::vector<node*> vector_nodes; // a vector which holds pointers to other nodes

     // Class functions
     void set_max_width(int max_width); // sets the max width of a particular node
     int get_max_width();               // returns the max width of a node
  };
}
		
#endif 
	
