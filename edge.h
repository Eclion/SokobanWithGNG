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
		void addAge(int a);
		int getAge();
		Node* getNode(int index);

	private:
		int _age;
		Node* _n1;
		Node* _n2;

};


#endif
