#ifndef DEF_NODE
#define DEF_NODE

#include <vector>

#include <iostream>

using namespace std;

class Node
{
	public:
		//Node();
		Node(Node* n);
		Node(int x=10000, int y=10000, float error = 0.0f);
		virtual ~Node();
		Node* maxErrorNeighbour();
		Node & operator= (const Node & other);
		int getX();
		int getY();
		float getError();
		void addNeigbour(Node* n);
		int distanceWith(Node* n);
		void setClosests(vector<Node*> nodes);
		Node* getClosest(int index);
		void addError(int d);

	private:
		int _x,_y;
		float _error;
		vector<Node*> neighbours;
		Node* firstClosest;
		Node* secondClosest;
};

Node* between(Node* n1, Node* n2);
Node* findNode(vector<Node*> nodes, int x, int y);

#endif
