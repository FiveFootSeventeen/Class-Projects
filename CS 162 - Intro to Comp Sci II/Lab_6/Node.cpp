/*********************************************************************
** Class Name: node
** Author: Jacob Leno
** Date: 11/03/17
** Description: This is the function implementation file for the Node
** class
*********************************************************************/

#include "Node.hpp"

/*********************************************************************
** Node constructor: Creates a node object with the arguments initially
** both prevNode and nextNode default to nullptr if they are not set
** to anything.
*********************************************************************/

Node::Node(int valIn, Node *prevNode, Node *nextNode)
{
	val = valIn;
	next = nextNode;
	prev = prevNode;
}