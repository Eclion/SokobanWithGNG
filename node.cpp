#include "node.h"

#include <vector>
#include <iostream>

/*Node::Node(){
	Node(0,0,0.0f);
}*/

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

Node* Node::maxErrorNeighbour(){
	int maxErrorNeighbourIndex = 0;
	if(neighbours.empty()){
		cout<<"vide"<<endl;
		return (new Node());
	}
	for(int i=0; i < neighbours.size(); i++){
		if(neighbours[maxErrorNeighbourIndex]->getError() < neighbours[i]->getError()){
			maxErrorNeighbourIndex = i;
		}
	}
	return neighbours[maxErrorNeighbourIndex];
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
	int d = ((this->getX() - n->getX())*(this->getX() - n->getX()) + (this->getY() - n->getY())*(this->getY() - n->getY()));
	return d;
}

void Node::setClosests(vector<Node*> nodes){
	//if(this->firstClosest==NULL)
	this->firstClosest = new Node();
	//if(this->secondClosest==NULL)
	this->secondClosest = new Node();

	Node* tmp = new Node();
	for(int i=0; i<nodes.size();i++){
		if(this->distanceWith(this->secondClosest) < this->distanceWith(nodes[i])){
			secondClosest=nodes[i];
			if(this->distanceWith(this->firstClosest) < this->distanceWith(this->secondClosest)){
				tmp = this->firstClosest;
				this->firstClosest = this->secondClosest;
				this->secondClosest = tmp;
			}
		}
	}
	vector<Node*> firstsNodes;
	firstsNodes.push_back(this->firstClosest);
	firstsNodes.push_back(this->secondClosest);
}

Node* Node::getClosest(int index){
	if(index == 0) return firstClosest;
	else return secondClosest;
}

void Node::addError(int d){
	this->_error += d;
}

Node* findNode(vector<Node*> nodes, int x, int y){
	if(nodes.empty()) return (new Node());
	for(int i =0; i<nodes.size();i++){
		if(nodes[i]->getX() == x && nodes[i]->getY() == y) return nodes[i];
	}
	return (new Node(x,y));
}