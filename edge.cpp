#include "edge.h"
#include "node.h"

Edge::Edge(){
	Edge(new Node(),new Node(),0);
}

Edge::Edge(Node* n1, Node* n2, int age){
	n1->addNeigbour(n2);
	n2->addNeigbour(n1);
	_n1=n1;
	_n2=n2;
	_age=age;
}

Edge::~Edge(){

}

void Edge::addAge(int a){
	_age += a;
}

int Edge::getAge(){
	return this->_age;
}

Node* Edge::getNode(int index){
	if(index == 0) return _n1;
	else return _n2;
}