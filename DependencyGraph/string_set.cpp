/*
 * Author: Alejandro Serrano
 * Prof.: Peter Jensen
 * Assignment 3: Droplist
 * October 12, 2020
 *
 * Summary: A 'string set' is defined as a set of strings stored
 * in sorted order in a drop list. This list traverses in O(log n)
 * for the add, remove, and contains methods. Each node contains a
 * vector node with a random amount of indices. Only the head node
 * will always have the max width.
 *
 */

#include "string_set.h"
#include <iostream> 
#include <stdlib.h>
#include <time.h>
namespace cs3505
{
	string_set::string_set(int max_width)
	{	
		// Rand for max width
		srand(time(NULL));

		// Properties for string_set
		this->max_width = max_width;
		this->head = new node("");
		this->head->set_max_width(max_width);
		this->size = 0;
	}

	string_set::string_set(const string_set& other)
	{
		// We re initialize everything
		this->head = new node("");
		this->head->set_max_width(other.max_width);
		this->max_width = other.max_width;
		node* rhs_current = other.head->next;
		this->size = 0;
		while (rhs_current != NULL)
		{
			this->add(rhs_current->data);
			rhs_current = rhs_current->next;
		}
	}

	string_set::~string_set()
	{
		this->clean();
	}

	void string_set::add(const std::string& target)
	{

		if (contains(target))
			return;

		// initialize node with new string
		node* temp = new node(target);
		node* current = this->head;
		node* prior = this->head;

		// Calculate the width the node will have
		(*temp).set_max_width(calculate_node_width());

		// Places it immediately right next to head
		// if the list is empty
		if (this->size == 0)
		{
			(*current).next = temp;
			this->size++;
			if (temp->get_max_width() == 0)
				return;
			else
			{
				// sets vector nodes for the temp node according
				// to its width. 
				for (int i = 0; i < temp->get_max_width(); i++)
				{
					current->vector_nodes[i] = temp;
				}
				return;
			}
		}
		std::vector<node*> prior_vector;
		prior_vector.resize(max_width);
		int position = max_width - 1;
		node* pointer_vector = this->head;

		while (position >= 0)
		{
			// In case is NULL we save the prior and continue
			if (pointer_vector->vector_nodes[position] == NULL)
			{
				prior_vector[position] = pointer_vector;
				position--;
				continue;
			}
			

			// We check if it's bigger, smaller. 
			// If it's smaller, we continue until we either reach the value
			// we reach something bigger. Then we update prior_vector
			// with the prior node
			if (pointer_vector->vector_nodes[position]->data.compare(temp->data) < 0)
			{
				prior = pointer_vector->vector_nodes[position];
				pointer_vector = pointer_vector->vector_nodes[position];
				prior_vector[position] = pointer_vector;
				continue;
			}
			
			else if (pointer_vector->vector_nodes[position]->data.compare(temp->data) > 0)
			{
				prior = pointer_vector;
				prior_vector[position] = pointer_vector;
				if (position == 0)
				{
					break;
				}
				position--;
				continue;
			}
			else
			{
				prior = pointer_vector;
				prior_vector[position] = pointer_vector;
				position--;
				continue;
			}

			prior = pointer_vector;
			prior_vector[position] = pointer_vector;
			position--;
		}

		// Sets the variables ready for the 
		// linearly connected linked list
		node* prior_node = prior;
		node* current_node = prior_node->next;

		// We use the width from temp to set up the correct 
		// indices with the right references
		for (int i = temp->get_max_width() - 1; i >= 0; i--)
		{
			if (prior_vector[i] == NULL)
			{
				this->head->vector_nodes[i] = temp;
				continue;
			}
			node* temporal = prior_vector[i];
			// update previous current node. 
			// We proceed depending on whether temp is 
			// greater or less than.
			if (temporal->data.compare(temp->data) > 0)
			{

				temp->vector_nodes[i] = temporal;
				this->head->vector_nodes[i] = temp;
			}
			else
			{
				if (i > temporal->get_max_width() - 1)
					continue;

				temp->vector_nodes[i] = temporal->vector_nodes[i];
				temporal->vector_nodes[i] = temp;
			}
		}
		// Finally, we just set the temp
		// to the correct spot
		if (prior_node->next != NULL)
		{
			prior_node->next = temp;
			temp->next = current_node;
			this->size++;
		}
		else
		{
			prior_node->next = temp;
			this->size++;
		}

	}

	void string_set::remove(const std::string& target)
	{
		if (!contains(target))
			return;

		node* temp = new node(target);

		// will help for removal at the end 
		node* prior = this->head;

		std::vector<node*> prior_vector; // will save the prior of the node we are want to remove
		prior_vector.resize(max_width);
		int position = max_width - 1;
		node* pointer_vector = this->head;

		while (position >= 0)
		{
			// If the value is null at position, we just continue
			if (pointer_vector->vector_nodes[position] == NULL)
			{
				prior_vector[position] = pointer_vector;
				position--;
				continue;
			}
			// In case we find it, we save it's prior and continue for other possible
			// connections
			if (pointer_vector->vector_nodes[position]->data.compare(temp->data) == 0)
			{
				prior_vector[position] = pointer_vector;
				temp = pointer_vector->vector_nodes[position];
				position--;
				continue;
			}

			// We check if it's bigger, smaller, or equal. 
			// If it's smaller, we continue until we either reach the value
			// we are looking for, or something bigger. Then we update prior_vector
			// with the prior node
			if (pointer_vector->vector_nodes[position]->data.compare(temp->data) < 0)
			{
				prior = pointer_vector->vector_nodes[position];
				pointer_vector = pointer_vector->vector_nodes[position];
				prior_vector[position] = pointer_vector;
				continue;
			}

			else if (pointer_vector->vector_nodes[position]->data.compare(temp->data) > 0)
			{
				prior = pointer_vector;
				prior_vector[position] = prior;
				if (position == 0)
				{
					break;
				}
				position--;
				continue;
			}
			else
			{
				prior = pointer_vector;
				prior_vector[position] = pointer_vector;
				position--;
				continue;
			}

			prior = pointer_vector;
			prior_vector[position] = prior;
			position--;
		}

		// we set the variables to delete the prior and next
		node* prior_node = prior;
		node* current_node = prior_node->next;

		for (int i = temp->get_max_width() - 1; i >= 0; i--)
		{
			// In case we've saved a null
			if (prior_vector[i] == NULL)
			{
				continue;
			}
			// otherwise, we just set the node
			pointer_vector = prior_vector[i];
			if (pointer_vector->vector_nodes[i] == NULL)
			{
				continue;
			}
			pointer_vector->vector_nodes[i] = current_node->vector_nodes[i];
		}

		// We delete the references
		prior->next = temp->next;
		temp->next = NULL;
		delete temp;
		this->size--;
	}
	bool string_set::contains(const std::string& target) const
	{
		// These first few checks handle the cases in which the list
		// has a size of 0 or 1, so that we don't have to traverse 
		// everything. 
		if (this->get_size() == 0)
			return false;

		else if (this->get_size() == 1)
		{
			if (this->head->next->data.compare(target) == 0)
			{
				return true;
			}
			return false;
		}

		// Prepare variables for traversal
		node* temp = new node(target);
		node* prior = this->head;

		int position = max_width - 1;
		node* pointer_vector = this->head;

		while (position >= 0)
		{
			// If the value is null at position, we just continue
			if (pointer_vector->vector_nodes[position] == NULL)
			{
				position--;
				continue;
			}
			// In case we find it immediately. 
			if (pointer_vector->vector_nodes[position]->data.compare(temp->data) == 0)
			{
				position--;
				return true;
			}

			// We check if it's bigger, smaller, or equal. 
			// If it's smaller, we continue until we either reach the value
			// we are looking for, or something bigger. If it's the same then
			// we simply return true.
			if (pointer_vector->vector_nodes[position]->data.compare(temp->data) < 0)
			{
				prior = pointer_vector->vector_nodes[position];
				pointer_vector = pointer_vector->vector_nodes[position];
				continue;
			}

			else if (pointer_vector->vector_nodes[position]->data.compare(temp->data) > 0)
			{
				prior = pointer_vector;
				if (position == 0)
				{
					break;
				}
				position--;
				continue;
			}
			else
			{
				prior = pointer_vector;
				position--;
				return true;
			}

			prior = pointer_vector;
			position--;
		}

		return false;
	}
	int string_set::get_size() const
	{
		return this->size;
	}

	string_set& string_set::operator=(const string_set& rhs)
	{
		if (&rhs == this)
			return *this;

		this->clean();

		// for the nodes that need to be added in this
		node* rhs_current = rhs.head->next;

		// set the values from rhs into this
		this->head = new node("");
		this->head->set_max_width(rhs.max_width);
		this->max_width = rhs.max_width;
		this->size = 0;

		while (rhs_current != NULL)
		{
			this->add(rhs_current->data);
			rhs_current = rhs_current->next;
		}

		return *this;
	}

	std::vector<std::string> string_set::get_elements()
	{
		node* current = this->head;
		std::vector<std::string> vector_of_set_elements;
		while (current != NULL)
		{
			if (current->data.compare("") == 0)
			{
				current = current->next;
				continue;
			}
			vector_of_set_elements.push_back(current->data);
			current = current->next;
		}

		return vector_of_set_elements;
	}

	int string_set::calculate_node_width()
	{
		int width_for_node = 1;

		// The loop continues until the node's max witdh 
		// is equal to this max width or the number is 
		// no longer divisible by 2. 
		while (width_for_node != this->max_width)
		{
			int value;
			value = rand();

			if (value % 2 == 0)
				width_for_node++;
			else
				break;
		}
		return width_for_node;
	}

	void string_set::clean()
	{
		node* this_current = this->head;
		node* this_next = this->head;

		while (this_current != NULL)
		{
			this_next = this_current->vector_nodes[0];
			delete this_current;
			this_current = this_next;
		}

	}

}
