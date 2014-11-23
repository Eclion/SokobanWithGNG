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
