#include "node.h"
#include "edge.h"
#include <vector>
#include <math.h>
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
	if(_edges.empty()) return (this);
	Node* _maxErrorNeighbour= getNeighbourNode(_edges[0]);
	for(int i=1; i < _edges.size(); i++){
		if(getNeighbourNode(_edges[i])->getError() > _maxErrorNeighbour->getError()){
			_maxErrorNeighbour = getNeighbourNode(_edges[i]);
		}
	}

	return _maxErrorNeighbour;
}

Node* Node::getNeighbourNode(Edge* e){
	if(this->getX()==e->getNode(0)->getX() && this->getY()==e->getNode(0)->getY()) return e->getNode(1);
	else return e->getNode(0);
}

void Node::addEdge(Edge* e){
	this->_edges.push_back(e);
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
	cout<<"n1->x = "<<n1->getX()<<endl;
	return new Node((n1->getX()+n2->getX())/2,
			(n1->getY()+n2->getY())/2,
			0);
}

int Node::distanceWith(Node* n){
	int d = sqrt(pow(this->getX()-n->getX(),2) + pow(this->getY()-n->getY(),2));
	return d;
}

void Node::setClosests(vector<Node*> nodes){
	//if(this->firstClosest==NULL)
	this->firstClosest = new Node();
	//if(this->secondClosest==NULL)
	this->secondClosest = new Node();
	//cout<<"nodes size = " << nodes.size() << endl;
	for(int i=0; i<nodes.size();i++){
		if(this->distanceWith(nodes[i])==0) continue;
		if(this->distanceWith(this->firstClosest) > this->distanceWith(nodes[i])){
			this->secondClosest=this->firstClosest;
			this->firstClosest=nodes[i];
		}else if(this->distanceWith(this->secondClosest) > this->distanceWith(nodes[i])){
			this->secondClosest = nodes[i];
		}
	}
}

Node* Node::getClosest(int index){
	if(index == 0) return firstClosest;
	else return secondClosest;
}

void Node::addError(int d){
	this->_error += d;
	if(this->_error < 0) this->_error = 0;
}

Node* findNode(vector<Node*> nodes, int x, int y){
	if(nodes.empty())return (new Node());
	for(int i =0; i<nodes.size();i++){
		if(nodes[i]->getX() == x && nodes[i]->getY() == y)return nodes[i];
	}
	return (new Node(x,y));
}