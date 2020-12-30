/*   
 * Author: Alejandro Serrano
 * Prof.: Peter Jensen
 * Assignment 3: Droplist
 * October 12, 2020
 * 
 * Summary: A 'string set' is defined as a set of strings stored
 * in sorted order in a drop list. This list traverses in O(log n) 
 * for the add, remove, and contains methods. Each node contains a 
 * vector of nodes with a random amount of indices. Only the head node 
 * will always have the max width. 
 * 
 */

#ifndef STRING_SET_H
#define STRING_SET_H

#include "node.h"  

namespace cs3505
{
  class string_set
    {

      int max_width;  // The maximum width of of a drop list in each node

      node *head;     // The head of the list will sit in a sentinal node
                      // (without any data in it).  This sentinal node
                      // will have a maximum width next list.  The head
                      // sentinal node should be in heap memory.

      int size;       // The number of elements in the set
      void clean();   // Cleans the list 
      int calculate_node_width();  // Calculates the width for each vector inside of a node

    public:
      string_set(int max_next_width = 10);   // Constructor. Has a default parameter value for max width, 
                                             // but also allows input from user.

      string_set(const string_set & other);  // Copy constructor
      ~string_set();                         // Destructor

      void add      (const std::string & target);        // Adds a value to the list in alphabetical order
      void remove   (const std::string & target);        // Removes a value from the list
      bool contains (const std::string & target) const;  // Const - checks the list to see if the value already exists
                                                         // does not edit this.

      int  get_size () const;                            // Const - returns size of the list. Does not edit this.

      string_set & operator= (const string_set & rhs);   // Sets this equal to another set (rhs)

      std::vector<std::string> get_elements();           // Returns all the elements in this string_set,
                                                         // in ascending order.  
  };

}

#endif
