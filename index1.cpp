#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int parent(int pos){
	return pos/2;
}

void swap(int* heap, int a, int b){
	int temp = heap[a];
	heap[a] = heap[b];
	heap[b] = temp;
}

int get_min(int* heap){
	return heap[1];
}

bool is_leaf(int pos, int SIZE){
	if(pos >= SIZE / 2 && pos <= SIZE) return true;
	return false;
}

int left(int pos){
	return 2*pos;
}

int right(int pos){
	return 2*pos+1;
}
void min_heapify(int* heap, int pos, int SIZE){
	//check (child) or (!child)
	if(is_leaf(pos, SIZE))return;
	
	int leftValue = heap[left(pos)];
	int rightValue = heap[right(pos)];
	
	if(heap[pos] > leftValue || heap[pos] < rightValue){
		if(leftValue < rightValue){
			swap(heap, pos, left(pos));
			min_heapify(heap, left(pos), SIZE);
		}else{
			swap(heap, pos, right(pos));
			min_heapify(heap, right(pos), SIZE);
		}
	}
}

int extract_min(int* heap, int *SIZE){
	int min = heap[1];
	//Nilai root dituker sama array terakhir
	heap[1] = heap[*SIZE];
	*SIZE -= 1;
	
	//fungsi -> check array terakhir > or !
	min_heapify(heap, 1, *SIZE);
	return min;
}

int insert(int* heap, int SIZE, int value){
	SIZE += 1;
	heap[SIZE] = value;
	
	int pos = SIZE;
	
	while(pos > 1 && heap[pos] < heap[parent(pos)]){
		swap(heap, pos, parent(pos));
		pos = parent(pos);
	}
	return SIZE;
}

void print_head(int* heap, int SIZE){
	for(int i = 1; i <= SIZE / 2; i++){
		printf("Parent: %d Left child: %d Right child: %d \n", heap[i], heap[2 * i], heap[2 * i + 1]);
	}
}
int main() {
	int heap[100];
	int SIZE = 0;
	SIZE = insert(heap, SIZE, 17);
	SIZE = insert(heap, SIZE, 16);
	SIZE = insert(heap, SIZE, 15);
	SIZE = insert(heap, SIZE, 12);
	SIZE = insert(heap, SIZE, 19);
	
	print_head(heap, SIZE);	
	int min = get_min(heap);
	
	printf("max: %d\n",min);
	min = extract_min(heap, &SIZE);
	printf("Max value after extract: %d\n", min);
	
	min = get_min(heap);
	printf("Max Value: %d", min);
}
