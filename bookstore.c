#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


enum publications{B, P, E}; 

struct Book {
   char  nameB[60];
   char  authorB[40];
   int  priceB;
   bool   isInStockB;
};

struct Periodical {
   char  nameP[60];
   char  editorP[40];
   float  priceP;
   bool   isInStockP;
   int volNoP;
};

struct Encyclopedia {
   char  nameE[60];
   char  publisherE[40];
   int  priceE;
   bool   isInStockE;
};

union Data {
   struct Book *book;
   struct Periodical *periodical;
   struct Encyclopedia *encyclopedia;
};

struct Node {
  struct Node *next;
  
  union Data data;
  int currentStruct;
}; 


void askAction();
struct Node* createLinkedList(FILE*);
void displayAll();
void display(int);
void insertNode(struct Node*);
void deleteNode(int);
int size();
void save();
void quit();
void trimString(char[]);
int compare(const char*, const char*);


struct Node *head;


int main() {
	FILE *filePointer = fopen ("inputbookdb.txt", "r");
	if(!filePointer) {
		printf("Error: File is not found!");
		return 2;
	}
	
	head = createLinkedList(filePointer);
	fclose(filePointer);
	
	while(true) {
		askAction();
	}
	
	return 0;
}

void askAction() {
	printf("1) Insertion\n2) Deletion\n3) Size\n4) Display\n5) Display All\n6) Saving\n7) Quitting\nPlease enter the action: ");
	char str[15];
	scanf("%s", &str);
	if(strcmp(str, "1") != 0 && strcmp(str, "2") != 0 && strcmp(str, "3") != 0 && strcmp(str, "4") != 0 && strcmp(str, "5") != 0 && strcmp(str, "6") != 0 && strcmp(str, "7") != 0) {
		printf("Error: Please enter a number between 1-7.\n\n\n");
		return;
	}
	
	
	int action = atoi(str);
	if(action == 1) {
		printf("Please enter the type(B, P, E): ");
		char publicationType;
		scanf(" %c", &publicationType);
		
		union Data data;
		enum publications type;
		char data1[60];
		char data2[40];
		int iData3;
		float fData3;
		char data4;
		int data5;
		if(publicationType=='B') {
			type = B;
			
			printf("Please enter the name: ");
			scanf("%s", &data1);
			
			printf("Please enter the author: ");
			scanf("%s", &data2);
			
			printf("Please enter the price: ");
			scanf("%d", &iData3);
			
			printf("Please enter the isInStock(T, F): ");
			scanf(" %c", &data4);
			
			struct Book *book;
			book  = (struct Book*)malloc(sizeof(struct Book));
			strcpy(book->nameB, data1);
			strcpy(book->authorB, data2);
			book->priceB = iData3;
			book->isInStockB = data4 == 'T' ? true : false;
			
			data.book = book;
		}
		else if(publicationType=='P') {
			type = P;
			
			printf("Please enter the name: ");
			scanf("%s", &data1);
			
			printf("Please enter the editor: ");
			scanf("%s", &data2);
			
			printf("Please enter the price: ");
			scanf("%f", &fData3);
			
			printf("Please enter the isInStock(T, F): ");
			scanf(" %c", &data4);
			
			printf("Please enter the volNo: ");
			scanf("%d", &data5);
			
			struct Periodical *periodical;
			periodical  = (struct Periodical*)malloc(sizeof(struct Periodical));
			strcpy(periodical->nameP, data1);
			strcpy(periodical->editorP, data2);
			periodical->priceP = fData3;
			periodical->isInStockP = data4 == 'T' ? true : false;
			periodical->volNoP = data5;
			
			data.periodical = periodical;
		}
		else if(publicationType=='E') {
			type = E;
			
			printf("Please enter the name: ");
			scanf("%s", &data1);
			
			printf("Please enter the publisher: ");
			scanf("%s", &data2);
			
			printf("Please enter the price: ");
			scanf("%d", &iData3);
			
			printf("Please enter the isInStock(T, F): ");
			scanf(" %c", &data4);
			
			struct Encyclopedia *encyclopedia;
			encyclopedia  = (struct Encyclopedia*)malloc(sizeof(struct Encyclopedia));
			strcpy(encyclopedia->nameE, data1);
			strcpy(encyclopedia->publisherE, data2);
			encyclopedia->priceE = iData3;
			encyclopedia->isInStockE = data4 == 'T' ? true : false;
			
			data.encyclopedia = encyclopedia;
		}
		else {
			printf("Error: Please enter 'B', 'P' or 'E'.");
			return;
		}
			
		struct Node *newNode;
		newNode = (struct Node*)malloc(sizeof(struct Node));
		newNode->currentStruct = type;
		newNode->data = data;
		newNode->next = NULL;
			
		insertNode(newNode);
		printf("\n");
		printf("Publication has been added successfully!");
	}
	else if(action == 2) {
		printf("Please enter the index: ");
		int index;
		scanf("%d", &index);
		
		printf("\n");
		deleteNode(index);
		printf("Publication has been deleted successfully!");
	}
	else if(action == 3) {
		printf("\n");
		printf("Size: %d\n", size());
	}
	else if(action == 4) {
		printf("Please enter the index: ");
		int index;
		scanf("%d", &index);
		
		printf("\n");
		display(index);
	}
	else if(action == 5) {
		printf("\n");
		displayAll();
	}
	else if(action == 6) {
		save();
		printf("\n");
		printf("\"outputbookdb.txt\" is saved successfully!");
	}
	else if(action == 7) {
		quit();
		printf("\n");
		printf("Good Bye!");
		exit(0);
	}
	
	
	printf("\n\n\n");
}

struct Node* createLinkedList(FILE *filePointer) {
	struct Node *head = NULL;
	struct Node *currentNode = NULL;
	char buffer[200];
	while (fgets(buffer, sizeof(buffer), filePointer)) {
		enum publications type;
		char data1[60];
		char data2[40];
		int iData3;
		float fData3;
		bool data4;
		int data5;
		
		int counter = 0;
		char *str;
		str = strtok(buffer, "#");
		while (str != NULL) {
			trimString(str);
			
			if(counter == 0) {
				if(str[0] == 'B')
					type = B;
				else if(str[0] == 'P')
					type = P;
				else if(str[0] == 'E')
					type = E;
				//printf("type: %d", type);
			}
			else if(counter == 1) {
				strcpy(data1, str);
				//printf("data1: %s", data1);
			}
			else if(counter == 2) {
				strcpy(data2, str);
				//printf("data2: %s", data2);
			}
			else if(counter == 3) {
				if(type == P) {
					fData3 = atof(str);
					//printf("data3: %f", fData3);
				}
				else {
					iData3 = atoi(str);
					//printf("data3: %d", iData3);
				}
			}
			else if(counter == 4) {
				if(str[0] == 'T')
					data4 = true;
				else
					data4 = false;
				//printf("data4: %s", data4 ? "true" : "false");
			}
			else if(counter == 5) {
				data5 = atoi(str);
				//printf("data5: %d", data5);
			}
			
			counter++;
			str = strtok(NULL, "#");
			//printf("\n");
		}
		//printf("\n");
		
		
		union Data data;
		if(type == B) {
			struct Book *book;
			book  = (struct Book*)malloc(sizeof(struct Book));
			strcpy(book->nameB, data1);
			strcpy(book->authorB, data2);
			book->priceB = iData3;
			book->isInStockB = data4;
			
			data.book = book;
		}
		else if(type == P) {
			struct Periodical *periodical;
			periodical  = (struct Periodical*)malloc(sizeof(struct Periodical));
			strcpy(periodical->nameP, data1);
			strcpy(periodical->editorP, data2);
			periodical->priceP = fData3;
			periodical->isInStockP = data4;
			periodical->volNoP = data5;
		
			data.periodical = periodical;
		}
		else if(type == E) {
			struct Encyclopedia *encyclopedia;
			encyclopedia  = (struct Encyclopedia*)malloc(sizeof(struct Encyclopedia));
			strcpy(encyclopedia->nameE, data1);
			strcpy(encyclopedia->publisherE, data2);
			encyclopedia->priceE = iData3;
			encyclopedia->isInStockE = data4;
			
			data.encyclopedia = encyclopedia;
		}
		
		
		struct Node *node;
		node = (struct Node*)malloc(sizeof(struct Node));
		node->currentStruct = type;
		node->data = data;
		node->next = NULL;
		
		if(head==NULL) {
			head = node;
		}
		
		if(currentNode!=NULL) {
			currentNode->next = node;
		}
		
		currentNode = node;
	}
	
	return head;
} 

void displayAll() {
	if(head==NULL) {
		return;
	}
	
	
	struct Node *currentNode = head;
	
	while (true) {
		char data1[60];
		char data2[40];
		int iData3;
		float fData3;
		bool data4;
		int data5;
		
		int type = currentNode->currentStruct;
		if(type == B) {
			strcpy(data1, currentNode->data.book->nameB);
			strcpy(data2, currentNode->data.book->authorB);
			iData3 = currentNode->data.book->priceB;
			data4 = currentNode->data.book->isInStockB;
			printf("Book -> name: %s, author: %s, price: %d, isInStock: %s\n", data1, data2, iData3, data4 ? "true" : "false");
		}
		else if(type == P) {
			strcpy(data1, currentNode->data.periodical->nameP);
			strcpy(data2, currentNode->data.periodical->editorP);
			fData3 = currentNode->data.periodical->priceP;
			data4 = currentNode->data.periodical->isInStockP;
			data5 = currentNode->data.periodical->volNoP;
			printf("Periodical -> name: %s, author: %s, price: %.2f, isInStock: %s, volNo: %d\n", data1, data2, fData3, data4 ? "true" : "false", data5);
		}
		else if(type == E) {
			strcpy(data1, currentNode->data.encyclopedia->nameE);
			strcpy(data2, currentNode->data.encyclopedia->publisherE);
			iData3 = currentNode->data.encyclopedia->priceE;
			data4 = currentNode->data.encyclopedia->isInStockE;
			printf("Encyclopedia -> name: %s, author: %s, price: %d, isInStock: %s\n", data1, data2, iData3, data4 ? "true" : "false");
		}
		
		if(currentNode->next != NULL)
			currentNode = currentNode->next;
		else
			break;
	}
}

void display(int index) {
	if(head==NULL) {
		printf("Error: There exist no 0. node!\n");
		return;
	}
	
	
	struct Node *currentNode = head;
	
	int i;
	for(i=0; i<index; i++) {
		if (currentNode->next == NULL) {
			printf("Error: There exist no %d. node!\n", index);
			return;
		}
		
		currentNode = currentNode->next;
	}


	char data1[60];
	char data2[40];
	int iData3;
	float fData3;
	bool data4;
	int data5;
		
	int type = currentNode->currentStruct;
	if(type == B) {
		strcpy(data1, currentNode->data.book->nameB);
		strcpy(data2, currentNode->data.book->authorB);
		iData3 = currentNode->data.book->priceB;
		data4 = currentNode->data.book->isInStockB;
		printf("Book -> name: %s, author: %s, price: %d, isInStock: %s\n", data1, data2, iData3, data4 ? "true" : "false");
	}
	else if(type == P) {
		strcpy(data1, currentNode->data.periodical->nameP);
		strcpy(data2, currentNode->data.periodical->editorP);
		fData3 = currentNode->data.periodical->priceP;
		data4 = currentNode->data.periodical->isInStockP;
		data5 = currentNode->data.periodical->volNoP;
		printf("Periodical -> name: %s, author: %s, price: %.2f, isInStock: %s, volNo: %d\n", data1, data2, fData3, data4 ? "true" : "false", data5);
	}
	else if(type == E) {
		strcpy(data1, currentNode->data.encyclopedia->nameE);
		strcpy(data2, currentNode->data.encyclopedia->publisherE);
		iData3 = currentNode->data.encyclopedia->priceE;
		data4 = currentNode->data.encyclopedia->isInStockE;
		printf("Encyclopedia -> name: %s, author: %s, price: %d, isInStock: %s\n", data1, data2, iData3, data4 ? "true" : "false");
	}
}

void insertNode(struct Node *newNode) {
	if(head==NULL) {
		head = newNode;
		return;
	}
	
	
	int type1 = newNode->currentStruct;
	char name1[60];
	if(type1 == B) {
		strcpy(name1, newNode->data.book->nameB);
	}
	else if(type1 == P) {
		strcpy(name1, newNode->data.periodical->nameP);
	}
	else {
		strcpy(name1, newNode->data.encyclopedia->nameE);
	}
	
	
	// IF newNode WILL BE HEAD
	int type2 = head->currentStruct;
	char name2[60];
	if(type2 == B)
		strcpy(name2, head->data.book->nameB);
	else if(type2 == P)
		strcpy(name2, head->data.periodical->nameP);
	else
		strcpy(name2, head->data.encyclopedia->nameE);
	
	int result = compare(name1, name2);
	if(result <= 0) {
		newNode->next = head;
		head = newNode;
		return;
	}
	
	
	// IF newNode WILL BE NEITHER HEAD NOR TAIL
	struct Node *beforeNode = head;
	struct Node *currentNode = head->next;
	while(currentNode!=NULL) {
		int type2 = currentNode->currentStruct;
		char name2[60];
		if(type2 == B) {
			strcpy(name2, currentNode->data.book->nameB);
		}
		else if(type2 == P) {
			strcpy(name2, currentNode->data.periodical->nameP);
		}
		else {
			strcpy(name2, currentNode->data.encyclopedia->nameE);
		}
		
		
		int result = compare(name1, name2);
		if(result <= 0) {
			beforeNode->next = newNode;
			newNode->next = currentNode;
			return;
		}
		
		beforeNode = currentNode;
		currentNode = currentNode->next;
	}
	
	
	// IF newNode WILL BE TAIL
	beforeNode->next = newNode;
}

void deleteNode(int index) {
	if(head==NULL) {
		printf("Error: There exist no 0. node!\n");
		return;
	}
	
	
	struct Node *beforeNode = head;
	struct Node *currentNode = head->next;
	
	
	if(index == 0) {
		free(head);
		head = currentNode;
		return;
	}
	
	
	int i;
	for(i=0; i<index-1; i++) {
		if (currentNode == NULL) {
			printf("Error: There exist no %d. node!\n", index);
			return;
		}
		
		
		beforeNode = currentNode;
		currentNode = currentNode->next;
	}
	
	
	if(currentNode!=NULL) {
		beforeNode->next = currentNode->next;
		free(currentNode);
	}
	else {
		printf("Error: There exist no %d. node!\n", index);
	}
}

int size() {
	if(head==NULL) {
		return 0;
	}
	
	struct Node *currentNode = head;
	int counter = 0;
	while(currentNode != NULL) {
		currentNode = currentNode->next;
		counter++;
	}
	
	return counter;
}

void save() {
	FILE *fp = fopen("outputbookdb.txt", "w");
	
	struct Node *currentNode = head;
	while(currentNode != NULL) {
		char data1[60];
		char data2[40];
		int iData3;
		float fData3;
		bool data4;
		int data5;
			
		int type = currentNode->currentStruct;
		if(type == B) {
			strcpy(data1, currentNode->data.book->nameB);
			strcpy(data2, currentNode->data.book->authorB);
			iData3 = currentNode->data.book->priceB;
			data4 = currentNode->data.book->isInStockB;
			
			char str[200];
			strcpy(str, "B # ");
			strcat(str,  data1);
			strcat(str,  " # ");
			strcat(str,  data2);
			strcat(str,  " # ");
			
			char buffer[15];
			memset(&buffer, 0, sizeof(buffer));
			sprintf(buffer, "%d", iData3);
			strcat(str,  buffer);
			strcat(str,  " # ");
			
			strcat(str,  data4 ? "T" : "F");
			fprintf(fp, str);
		}
		else if(type == P) {
			strcpy(data1, currentNode->data.periodical->nameP);
			strcpy(data2, currentNode->data.periodical->editorP);
			fData3 = currentNode->data.periodical->priceP;
			data4 = currentNode->data.periodical->isInStockP;
			data5 = currentNode->data.periodical->volNoP;
			
			char str[200];
			strcpy(str, "P # ");
			strcat(str,  data1);
			strcat(str,  " # ");
			strcat(str,  data2);
			strcat(str,  " # ");
			
			char buffer[15];
			memset(&buffer, 0, sizeof(buffer));
			sprintf(buffer, "%.2f", fData3);
			strcat(str,  buffer);
			strcat(str,  " # ");
			
			strcat(str,  data4 ? "T" : "F");
			strcat(str,  " # ");
			
			char buffer2[15];
			memset(&buffer2, 0, sizeof(buffer2));
			sprintf(buffer2, "%d", data5);
			strcat(str,  buffer2);
			
			fprintf(fp, str);
		}
		else if(type == E) {
			strcpy(data1, currentNode->data.encyclopedia->nameE);
			strcpy(data2, currentNode->data.encyclopedia->publisherE);
			iData3 = currentNode->data.encyclopedia->priceE;
			data4 = currentNode->data.encyclopedia->isInStockE;
			
			char str[200];
			strcpy(str, "E # ");
			strcat(str,  data1);
			strcat(str,  " # ");
			strcat(str,  data2);
			strcat(str,  " # ");
			
			char buffer[15];
			memset(&buffer, 0, sizeof(buffer));
			sprintf(buffer, "%d", iData3);
			strcat(str,  buffer);
			strcat(str,  " # ");
			
			strcat(str,  data4 ? "T" : "F");
			
			fprintf(fp, str);
		}
		
		currentNode = currentNode->next;
		if(currentNode != NULL)
			fprintf(fp, "\n");
	}
	
	fclose(fp);
}

void quit() {
	if(head==NULL) {
		return;
	}
	
	struct Node *currentNode = head;
	while(currentNode != NULL) {
		struct Node *temp = currentNode;
		currentNode = currentNode->next;
		free(temp);
	}
}

void trimString(char str[]) {
	if(str[0]!=' ')
		return;
			
	int i = 0;
	while (true) {
		if(str[i+1]=='\0') {
			if(str[i-1]==' ')
				str[i-1] = '\0';
			else if(str[i]==' ')
				str[i] = '\0';
			break;
		}
			
    	str[i] = str[i+1];
    	i++;
	}
}

int compare(const char* s1, const char* s2) {
    while( (*s1==*s2) && *s1 )
        s1++, s2++;
        
    return *s1 < *s2 ? -1 : *s1 > *s2;
}















