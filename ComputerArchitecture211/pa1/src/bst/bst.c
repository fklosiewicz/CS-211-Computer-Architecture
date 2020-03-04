/* CS 211 PA1: bst
 * Created for: fk206
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int data;
	struct Node* left;
	struct Node* right;
}	Node;

struct Node* newNode(int data) {
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node) * 3);
	newNode->data = data;
	newNode->left = NULL;
	newNode->right = NULL;

	return newNode;
}

void InOrderRecursive(struct Node* root) {
	if (root == NULL) {
		return;
	}
	printf("(");
	InOrderRecursive(root->left);
	printf("%d",root->data);
	InOrderRecursive(root->right);
	printf(")");
}

int SearchNode(struct Node* root, int key) {
	struct Node* node = root;
	int present = 0;
	while(node != NULL) {
		if(node->data == key) {
			return 1;
		}
		if(key > node->data) {
			if(node->right != NULL) {
				node = node->right;
				continue;
			}
			else {
				return present;
			}
		}
		if(key < node->data) {
			if(node->left != NULL) {
				node = node->left;
				continue;
			}
			else {
				return present;
			}
		}
	} return present;
}

void InsertNode(struct Node** root, struct Node* newNode) {
	if(SearchNode(*root, newNode->data) == 1) {
		printf("not inserted\n");
		return;
	}

//	printf("Node to insert has value of: %d \n", newNode->data);
	
	if(*root == NULL) {
		*root = newNode;
		printf("inserted\n");
//		printf("Successful insertion of the root node!\n");
		return;
	}

	Node* current = *root;
	while(current != NULL) {
		if(newNode->data > current->data) {
			if(current->right == NULL) {
				current->right = newNode;
				printf("inserted\n");
				return;
			} else {
				current = current->right;
			}
		}
		if(newNode->data <= current->data) {
			if(current->left == NULL) {
				current->left = newNode;
				printf("inserted\n");
				return;
			} else {
				current = current->left;
			}
	}
	}
}

struct Node* MaxofLeft(struct Node** root) {
	Node* current = *root;
	if(current->left == NULL) {
		return current;
	} else {
		return MaxofLeft(&(current->left));
	}
}

struct Node* DeleteNode(struct Node** root, int key) {	

//	printf("Key to delete is: %d", key);
//
	Node* c = *root;
/*
	if(SearchNode(c, key) == 0) {
		printf("absent\n");
		return c;
	}

	if(SearchNode(c,key) == 1) {
		printf("deleted\n");
	}
*/
	if(c == NULL) {
		return c;
	}
	
	else {
		if(c->data > key) {
			c->left = DeleteNode(&c->left, key);
		}
		else if(c->data < key) {
			c->right = DeleteNode(&c->right, key);
		} else {
			if(c->right == NULL && c->left == NULL) {
				c = NULL;
			}

			else if((c->right == NULL && c->left != NULL)) {
				c = c->left;
			}
			else if((c->left == NULL && c->right != NULL)) {
				c = c->right;
			}
			else {
			Node* maxofleft = MaxofLeft(&c->right);
			c->data = maxofleft->data;
			c->right = DeleteNode(&c->right, maxofleft->data); // Deletes the copied maxofleft node from original spot
			}
		}
	}
		return c;
}				


int main(int argc, char **argv) {

	char ch;
	int i;
	Node *root = NULL;
	while(scanf(" %c",&ch) != EOF) {
		if(ch == 'i') {
			scanf(" %d", &i);
			InsertNode(&root, newNode(i));
		}
		if(ch == 's') {
			scanf(" %d", &i);
			if(SearchNode(root,i) == 0) {
				printf("absent\n");
				continue;
			}
			else {
				printf("present\n");
				continue;
			}
		}
		if(ch == 'p') {
	//		printf("Trying to recursively print!");
			InOrderRecursive(root);
			printf("\n");
		}
		if(ch == 'd') {
			scanf(" %d", &i);
			if(SearchNode(root,i) == 0) {
				printf("absent\n");
			} else {
				printf("deleted\n");
				root = DeleteNode(&root, i);
			}
//			printf("Beginning to delete...");
		//	root = DeleteNode(&root,i);
		}
}

    return EXIT_SUCCESS;
}
