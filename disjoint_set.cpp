#include <stdio.h>

int parent[30] = {0};

//cari parent awal
int find_parent(int vertex){//0
	if(parent[vertex] == vertex){//0
		return vertex;
	}
	
	parent[vertex] = find_parent(parent[vertex]);
	return parent[vertex];
}

void make_set(int total_vertex){
	for(int i = 0; i < total_vertex; i++){
		parent[i] = i;
	}
}

//join sets
void join_set(int vertexA, int vertexB){
	int parent_vertexA = find_parent(vertexA);//0
	int parent_vertexB = find_parent(vertexB);
	
	printf(" %d -> %d ", parent_vertexA, parent_vertexB);
	
	parent[parent_vertexA] = parent_vertexB;
}

bool isSameDataSet(int vertexA, int vertexB){
	return find_parent(vertexA) == find_parent(vertexB);
}

int main(){
	make_set(3);
	join_set(0,1);
	join_set(1,2);
	join_set(2,0);
	
	if(isSameDataSet(0,2)){
		printf("\n The parent is same!! \n");
	}else{
		printf("\n Different Boy \n");
	}
	
	return 0;
}
