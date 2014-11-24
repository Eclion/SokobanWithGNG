#ifndef DEF_NODE
#define DEF_NODE

#include <vector>

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
		int getX();
		int getY();
		float getError();
		void addNeigbour(Node* n);
		int distanceWith(Node* n);

	private:
		int _x,_y;
		float _error;
		vector<Node*> neighbours;
};

vector<Node*> findClosests(Node* n);

#endif
