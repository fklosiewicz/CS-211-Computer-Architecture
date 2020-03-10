/* CS 211 PA1: list
 * Created for: fk206
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int data;
	struct Node* next;
} Node;

struct Node* newNode(int data) {
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node) * 2);
		newNode->data = data;
		newNode->next = NULL;
	return newNode;
}	

int SearchNode(struct Node* head, int key) {
	struct Node* node = head;
	int present = 0;
	while(node != NULL) {
		if(node->data == key) {
			present = 1;
			return present;
		}
		node = node->next;
	}
	return present;
}

void InsertNode(struct Node** head, struct Node* newNode) {
	if(SearchNode(*head, newNode->data) == 1) {
		return;
	}
	
	if(*head == NULL|| (*head)->data >= newNode->data) {
		newNode->next = *head;
		*head = newNode;
		return;
	}
	Node* current = *head;
	
	while(current->next != NULL && current->next->data < newNode->data) {
		current = current->next;
	}

	newNode->next = current->next;
	current->next = newNode;	
	return;
}

void PrintLL(struct Node* head) {
	struct Node* node = head;
	while(node != NULL) {
		if(node->next == NULL) {
			printf("%d",node->data);
			return;
		} else {
		printf("%d ", node->data);
		node = node->next;
		}
	}
	return;
}

int CountLL(struct Node* head) {
	struct Node* node = head;
	int numberofnodes = 0;
	while(node != NULL) {
		numberofnodes++;
		node = node->next;
	}
	return numberofnodes;
}

void DeleteNode(struct Node** head, int nodetodelete) {

	Node* key = *head;

	if(key != NULL && key->data == nodetodelete) {
		*head = key->next;
		free(key);
		return;
	}
	Node* pointertolast = *head;
	if(key != NULL && key->data != nodetodelete) {
		while(key != NULL && key->data != nodetodelete) {
			pointertolast = key;
			key = key->next;
		}
	}

	if(key == NULL) {
		return;
	}
	pointertolast->next = key->next;

	return;
	}

int main(int argc, char **argv)
{
	char ch;
	int i;
	Node *head = NULL;
	while(scanf(" %c %d", &ch, &i) != EOF && ch != '\n') {
		if(ch == 'i') {
			InsertNode(&head, newNode(i));
			printf("%d : ", CountLL(head));
			PrintLL(head);
		}
		if(ch == 'd') {
			if(CountLL(head) > 0) {
				DeleteNode(&head, i);
				if(CountLL(head) > 0) {
					printf("%d : ", CountLL(head));
					PrintLL(head);
				} else {
					printf("%d :", CountLL(head));
					PrintLL(head);
				}
			} else {
				printf("%d :", CountLL(head));
				PrintLL(head);
			}	
		} 
		
	printf("\n");
	}
	if(ch != 'i' || ch != 'd') {
		return EXIT_SUCCESS;
}

    return EXIT_SUCCESS;
}









































