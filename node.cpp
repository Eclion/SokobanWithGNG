#include "node.h"

#include <list>

Node::Node(){
	Node(0,0,0.0f);
}

Node::Node(Node* n){
	_x=n->_x;
	_y=n->_y;
	_error=n->_error;
}

Node::Node(int x, int y, float error){
	_x=x;
	_y=y;
	_error=error;
}

Node::~Node(){

}

float Node::maxErrorNeighbour(){
	
}

void Node::addNeigbour(Node* n){
	this->neighbours.push_back(n);
}

int Node::getX(){
	return this->_x;
}

int Node::getY(){
	return this->_y;
}

Node & Node::operator= (const Node & other){
        if (this != &other) // protect against invalid self-assignment
        {
            this->_x=other._x;
            this->_y=other._y;
            this->_error=other._error;
        }
        // by convention, always return *this
        return *this;
}

Node* between(Node* n1, Node* n2){
	return new Node((n1->getX()+n2->getX())/2,
			(n1->getY()+n2->getY())/2,
			0);
}

/*void findClosests(int x, int y, int z, List<Node> lNode, List<Node> & closestNodes){

}*/





