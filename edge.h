#ifndef DEF_EDGE
#define DEF_EDGE

using namespace std;
class Node;

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
		float _distance;
		Node* _n1;
		Node* _n2;

};


#endif
