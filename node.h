#ifndef DEF_NODE
#define DEF_NODE

#include <list>

using namespace std;

class Node
{
	public:
		Node();
		Node(Node* n);
		Node(int x, int y, float error = 0.0f);
		virtual ~Node();
		float maxErrorNeighbour();
		Node & operator= (const Node & other);
		int getX(),getY();
		void addNeigbour(Node* n);

	private:
		int _x,_y;
		float _error;
		list<Node*> neighbours;
};


#endif