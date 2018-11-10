/*********************************************************************
** Class Name: node
** Author: Jacob Leno
** Date: 11/03/17
** Description: This is the header file for the Node class
*********************************************************************/

#ifndef NODE_HPP
#define NODE_HPP

class Node
{
protected:
	int val;
	Node *next, *prev;

public:
	Node() { val = 0, prev = nullptr, next = nullptr; }
	Node(int val, Node *prevNode = nullptr, Node *nextNode = nullptr);
	Node* getNext() { return next; }
	Node* getPrev() { return prev; }
	int getVal() { return val; }
	void setNext(Node* nextIn) { next = nextIn; }
	void setPrev(Node* prevIn) { prev = prevIn; }
	void setVal(int valIn) { val = valIn; }

};

#endif
