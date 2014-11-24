#include "node.h"

#include <vector>

Node::Node(){
	Node(-100,-100,0.0f);
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
	int maxErrorNeighbourIndex = 0;
	for(int i=0; i < neighbours.size(); i++){
		if(neighbours[maxErrorNeighbourIndex]->getError() < neighbours[i]->getError()){
			maxErrorNeighbourIndex = i;
		}
	}
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

float Node::getError(){
	return this->_error;
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

int Node::distanceWith(Node* n){
	int d = ((this->getX() - n->getX())² + (this->getY() - n->getY())²);
	return d;
}

vector<Node*> findClosests(Node* n, vector<Node*> nodes){
/*	Node* first = new Node();
	Node* second = new Node();
	Node* tmp = new Node();
	for(int i=0; i<nodes.size();i++){
		if(n->distanceWith(second) < n->distanceWith(nodes[i])){
			second=nodes[i];
			if(n->distanceWith(first) < n->distanceWith(second)){
				tmp = first;
				first = second;
				second = tmp;
			}
		}
	}*/
}
