#include <stdio.h>

#include <stdlib.h>
struct Edge{
	int source;
	int destination;
};
struct Graph{
	int tot_ver;
	//tot_ver is Total Vertex 
	int to_ed;
	//to_ed is Total Edge
	Edge *edge;
};

int parent[30] = {0};

//crete new Graph

Graph* CreateNewGraph(int tot_ver, int to_ed){
	Graph *newGraph = (Graph*)malloc(sizeof(Graph));
	newGraph->tot_ver = tot_ver;
	newGraph->to_ed = to_ed;
	newGraph->edge = (Edge*)malloc(sizeof(Edge) * to_ed);
	
	return newGraph;
}

void make_set(int to_ed){
	for(int i = 0; i < to_ed; i++){
		parent[i] = i;
	}
}

int find_parent(int vertex){
	if(parent[vertex] == vertex)return vertex;
	
	parent[vertex] = find_parent(parent[vertex]);
	return parent[vertex];
}

bool join(Graph* graph){
	for(int i = 0; i< graph->tot_ver; i++){
		int source_parent = find_parent(graph->edge[i].source);
		int destination_parent = find_parent(graph->edge[i].destination);
		
		if(source_parent == destination_parent){
			return true;
		}
		printf(" %d->%d ", source_parent, destination_parent);
		
		parent[source_parent] = destination_parent;
	}
}


bool isCyclic(Graph* graph){
	make_set(graph->tot_ver);
	return join(graph);
}
int main() {
	Graph* graph = CreateNewGraph(4,4);
	
	graph->edge[0].source = 0;
	graph->edge[0].destination = 1;
	
	graph->edge[1].source = 1;
	graph->edge[1].destination = 2;
	
	graph->edge[2].source = 2;
	graph->edge[2].destination = 3;
	
	graph->edge[3].source = 1;
	graph->edge[3].destination = 3;
	
	if(isCyclic(graph)){
		printf("\n This is Cyclic!!!! \n");
	}else{
		printf("\n This is'nt Cyclic \n");
	}
	return 0;	
}
