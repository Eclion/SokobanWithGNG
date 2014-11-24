/*
Node* nodes = {}
Edge* edges = {}
while(play){
	(x,y) = position
	if(size(nodes) <= 1) nodes.push(Node(x,y,error=0);
	if(size(nodes) == 2) edges.push(Edge(node1,node2,age=0));

	
	first = closest((x,y),nodes);
	second = secondClosest((x,y),nodes);
	edge.push (first,second,age=0);
	first.error += sqrt((x-first.x)²+(y-first.y)²;

//	Attract first toward (x,y)

	foreach(Edge e in first.edges){
		
		e.age++;
		if(e.age > MAX_AGE) edges.remove(e);
	}
	
//	Attract neighbours(first) toward (x,y)

	foreach(Node n in nodes) n.error -= ERROR_DECAY;

	if(first.error > MAX_ERROR){
		maxErrNei = maxErrorNeighbour(first);
		newNode = between(first,maxErrNei);
		first.error/=2;
		maxErrNei.error/=2;
		newError = first.error+maxErrNei.error//
		nodes.push(newNode,newError);
	}
}
*/
