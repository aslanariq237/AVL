#include<stdio.h>
#include<stdlib.h>
#include<string.h>


struct Product{
	int price;
	char name[30];
	struct Product *right, *left;
	int height;
};


// make a root AVL 
struct Product* root = NULL;

// create a node
struct Product* createNewNode(char name[30], int price){
	struct Product* product = (struct Product*)malloc(sizeof(struct Product));
	product->price = price;
	strcpy(product->name, name);
	product->left = product->right = NULL;
	product->height = 1;
	return product;
}

// get height of AVL tree 
int getHeight(struct Product* node){
	if(node==NULL){
		return 0;
	}
	return node->height;
}

// get balance factor 
int getBalanceFactor(struct Product* node){
	if(node == NULL){
		return 0;
	}
	return getHeight(node->left) - getHeight(node->right);
}

// check the max of two node 
int getMax(int a, int b){
	return (a>b)?a:b;
}

// right rotation 
struct Product* rightRotation(struct Product* node){
	
	struct Product* x = node->left;
	struct Product* sub_x = x->right;
	
	x->right = node;
	node->left = sub_x;
	
	node->height = getMax(getHeight(node->left), getHeight(node->right));
	x->height = getMax(getHeight(x->left), getHeight(x->right));
	
	return x;
}

// left rotation 
struct Product* leftRotation(struct Product* node){
	struct Product* x = node->right;
	struct Product* sub_x = x->left;
	
	x->left = node;
	node->right = sub_x;
	
	node->height = getMax(getHeight(node->left), getHeight(node->right));
	x->height = getMax(getHeight(x->left), getHeight(x->right));
	
	return x;
}

// insert data product
struct Product* insert_product(struct Product* node, char name[30], int price){
	if(node == NULL){
		return createNewNode(name,price);
	}
	
	if(price < node->price){
		node->left = insert_product(node->left, name, price);
	}
	else if(price > node->price){
		node->right = insert_product(node->right, name, price);
	}
	else{
		return node;
	}
	
	node->height = 1 + getMax(getHeight(node->left), getHeight(node->right));
	
	int balanceFactor = getBalanceFactor(node);
	
	//LL 
	if(balanceFactor > 1 && price < node->left->price){
		// Right rotation
		return rightRotation(node);
	}
	//LR
	if(balanceFactor > 1 && price > node->left->price){
		// left rotation
		node->left = leftRotation(node->left);
		
		// right rotation
		return rightRotation(node);
	}
	
	//RR
	if(balanceFactor < -1 && price > node->right->price){
		return leftRotation(node);
	}
	//RL
	if(balanceFactor < -1 && price < node->right->price){
		// right rotation 
		node->right = rightRotation(node->right);
		
		// left rotation 
		node->left = leftRotation(node);
	}
	
	return node;
}

void insert_menu(){
	system("cls");
//	1. Validasi input
//	- cek panjang string untuk nama  5 - 10 char
//	- nama produk harus di awali sama huruf kapital
//	- cek price harus diantara 1 - 50

	char name[30];
	int wrong = 0;
	
	bool checklen = false, checkcap = false;
	
	do{
		wrong = 0;
		checklen = false;
		checkcap = false;
		printf("input product name [5 - 110 char | must started with capital :]");
		scanf("%[^\n]", name);getchar();
		
		//panjang string
		if(strlen(name) < 5 || strlen(name) > 10){
			wrong++;
			checklen = true;
		}
		
		//check diawali kapital atau tidak
		//range ascii kapital 65 - 90
		if(name[0] < 65 || name[0] > 90){
			wrong++;
			checkcap = true;
		}
		
		
		//err messages
		if(checklen == true){
			printf("The input le must be valid!\n");
		}
		if(checkcap == true){
			printf("The input must be start with capitalize\n");
		}
	}while(wrong > 0);
	
	//check price
	int price = 0;
	do{
		printf("Input Product price [1 - 50] \n");
		scanf("%d", &price);
	}while(price < 1 || price > 50);
	root = insert_product(root, name, price);
	printf("Insert Has Been Successful!\n");
}


//view
void view(struct Product* node){
	if(node != NULL){
		printf("\t Product |\t Price \n");
		printf("\t %s |\t  %d\n",node->name, node->price);
		view(node->left);
		view(node->right);
	}
}

struct Product* getPredecessor(struct Product* node){
	struct Product* curr = node->left;
	while(curr->right){
		curr = curr->right;
	}
	return curr;
}

struct Product* delete_menu(struct Product* node, char name[30]){
	if(node == NULL){
		printf("Data Not Found\n");
		return NULL;
	}
	
	//search Data Pakai BST
	if(strcmp(name ,node->name) > 0){
		node->left = delete_menu(node->left, name);
	}else if(strcmp(name, node->name) < 0){
		node->right = delete_menu(node->right, name);
	}else{
		//Tidak Punya Subtree
		if(node->left == NULL || node->right==NULL){
			struct Product* temp = NULL;
			if(node->left){
				temp = node->left;
			}else{
				temp = node->right;
			}
			
			free(node);
			node = temp;
		}
		else{
			struct Product* predec = getPredecessor(node);
			strcpy(node->name, predec->name);
			node->left = delete_menu(node->left, node->name);
		}
	}
	// update height & balancing
	node->height = 1 + getMax(getHeight(node->left), getHeight(node->right));
	
	int balance = getBalanceFactor(node);
	
	//LL Case -> Left Left Case
	if(balance > 1 && getBalanceFactor(node->left) >= 0){
		return rightRotation(node);
	}
	//LR case -> Left Right Case
	if(balance > 1 && getBalanceFactor(node->left) < 0){
		node->left = leftRotation(node->left);
		return rightRotation(node);
	}
	
	//RR Case
	if(balance < 1 && getBalanceFactor(node->left) <= 0){
		return leftRotation(node); //44
	}
	if(balance < 1 && getBalanceFactor(node->left) > 0){
		node->right = rightRotation(node->right);
		return leftRotation(node);
	}
	
	return node;
	
}


	


//Menu Function

void menu() {
	int ch = 0;
	
	do{
		printf("Management Product\n");
		printf("==================\n");
		printf("1. Insert Product\n");
		printf("2. View All Product\n");
		printf("3. Delete Product\n");
		printf("4. Find Product\n");
		printf("5. Exit\n");
		printf(">> ");
		scanf("%d", &ch);getchar();
		if(ch == 1) {
			//insert
			insert_menu();	
		}else if(ch == 2){
			//view
			view(root);
		}else if(ch == 3){
			//delete
			delete_menu(root, "Tomato");
			printf("Delete Successfull!");
		}	
	}while(ch != 5);
	
}

int main(){
	menu();
	
	return 0;
}
