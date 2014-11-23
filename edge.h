#ifndef DEF_EDGE
#define DEF_EDGE

#include "node.h"

using namespace std;

class Edge
{
	public:
		Edge();
		Edge(Node* n1, Node* n2,int age=0);
		virtual ~Edge();		

	private:
		int _age;
		Node* _n1,_n2;

};


#endif
