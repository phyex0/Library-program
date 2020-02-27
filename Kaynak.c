#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct library
{
	char catagory[50];
	char available[18];
	char book_name[50];
	char author[50];
	int book_id;
	int quantity;
	double price;
	int shelf_no;
	struct library* next;

}node;


node* read_from_file(node* head);
void view_book(node* root);
node* add_book(node* head);
void menu();
void write_to_file(node* head);
node* edit_book(node* head);
node* delete_book(node* head);
void add_book_variable(node* variable);
void search_book(node* head);
void search_book_variable(node* variable);

int main() {
	node* root;
	root = NULL;

	root = read_from_file(root);
	int choice=0;
	menu();
	scanf("%d", &choice);
	while (choice != 6) {
		switch (choice)
		{
		case 1:root=add_book(root);
			menu();
			scanf("%d", &choice);
			break;
		case 2:root= delete_book(root);
			menu();
			scanf("%d", &choice);
			break;
		case 3: search_book(root);
			menu();
			scanf("%d", &choice);
			break;
		case 4: view_book(root);
			menu();
			scanf("%d", &choice);
			break;
		case 5:root= edit_book(root);
			menu();
			scanf("%d", &choice);
			break;
		
		}
	}

	printf("End of the program....");
	write_to_file(root);
	
	return 0;
 }


node* read_from_file(node* head) {
	node* iter;
	
	FILE* fptr = fopen("data.txt", "r");
	if (fptr == NULL) {
		fptr = fopen("data.txt", "w");
	}

	fseek(fptr, 0, SEEK_END);


	if (ftell(fptr) == 0)
	{
		
		fclose(fptr);
		return NULL;
	}

	else {

		fseek(fptr, 0, SEEK_SET);
		head = (node*)calloc(1,sizeof(node));
		head->next = NULL;
		iter = head;
		head->book_id = -1;

		while (feof(fptr) != 1) {
			
			iter->next = (node*)calloc(1, sizeof(node));
			iter = iter->next;
			iter->next = NULL;
			
			fscanf(fptr, "%[^\n]%*c", &iter->catagory);
			fscanf(fptr, "%[^\n]%*c", &iter->book_name);
			fscanf(fptr, "%[^\n]%*c", &iter->author);
			fscanf(fptr, "%d", &iter->book_id);
			fscanf(fptr, "%d", &iter->quantity);
			fscanf(fptr, "%lf",&iter->price);
			fscanf(fptr, "%d", &iter->shelf_no);
			
		}
		
		fclose(fptr);
		return head;
	}

}

void view_book(node* root) {

	printf("############################# BOOK LIST #############################\n");
	printf("%10s\t%10s\t%20s\t%20s\t%10s\t%s\t%s\n","Category","ID","Book Name","Author","QTY","Price","Shelf NO");
	node* move;
	move = root;
	if(move!=NULL){
		if (move->book_id == -1)
			move = move->next;
	}
	
	while (move != NULL) {
		printf("%-20s\t%d\t%20s\t%20s\t%10d\t%0.2lf\t%d\n", move->catagory, move->book_id, move->book_name, move->author, move->quantity, move->price, move->shelf_no);
		move = move->next;
	}

}

node* add_book(node* head) {

	
	node* temp;

	if (head == NULL) {

		head = (node*)calloc(1,sizeof(node));
		head->next = NULL;

		add_book_variable(head);
		
		return head;
	}

	else {

		temp = (node*)calloc(1,sizeof(node));

		add_book_variable(temp);

		temp->next = head->next;
		head->next = temp;

		return head;
	}	
}

void menu() {
	printf("::::::::::MAIN MENU::::::::::\n");
	printf("==== 1. Add Books        ===\n");
	printf("==== 2. Delete Books     ===\n");
	printf("==== 3. Search Books     ===\n");
	printf("==== 4. View Book List   ===\n");
	printf("==== 5. Edit Books Record===\n");
	printf("==== 6. Close Application===\n");
	printf(":::::::::::::::::::::::::::::\n");
}

void write_to_file(node* head) {
	node* move;
	move = head;
	FILE* fptr;
	fptr = fopen("data.txt", "w");
	
	if(move!=NULL){
		if (move->book_id == -1)
			move = move->next;
	}
	
	while (move != NULL) {

		fprintf(fptr, "%s\n", move->catagory);
		fprintf(fptr, "%s\n", move->book_name);
		fprintf(fptr, "%s\n", move->author);
		fprintf(fptr, "%d\n", move->book_id);
		fprintf(fptr, "%d\n", move->quantity);
		fprintf(fptr, "%lf\n", move->price);
		fprintf(fptr, "%d", move->shelf_no);

		move = move->next;
	}

	fclose(fptr);
}

node* edit_book(node* head) {
	node* move;
	move = head;
	printf("Enter Book Id to be edited: \n");
	int id;
	scanf("%d", &id);

	while (move->book_id != id) {
		move = move->next;
	}
	
	add_book_variable(move);

	return move;
}

node *delete_book(node* head) {

	int id;
	printf("Enter the Book ID to  delete: \n");
	scanf("%d", &id);
	node* del, * move;
	move = head;

	while (move->next->book_id != id) {
		move = move->next;
	}
	del = move->next;
	move->next = del->next;
	free(del);

	return head;
}

void add_book_variable(node* variable) {

	printf("Enter the Category\n");
	scanf(" %[^\n]%*c", variable->catagory);

	printf("Enter the Book name\n");
	scanf(" %[^\n]%*c", variable->book_name);

	printf("Enter the Author\n");
	scanf(" %[^\n]%*c", variable->author);

	printf("Enter the Book ID\n");
	scanf("%d", &variable->book_id);

	printf("Enter the Quantity\n");
	scanf("%d", &variable->quantity);

	printf("Enter the Price\n");
	scanf("%lf", &variable->price);

	printf("Enter the Shelf No\n");
	scanf("%d", &variable->shelf_no);
	strcpy(variable->available, "available");






}

void search_book(node* head){
	node* move;
	move = head;
	int choice;
	printf("*****************************Search Books***************************\n");
	printf("### 1. Search By ID\n");
	printf("### 2. Search By Name\n");
	scanf("%d",&choice);
	
	if (choice == 1) {
		int id;
		printf("Enter the ID...\n");
		scanf("%d", &id);
		while (move->book_id != id) {
			move = move->next;
		}

		search_book_variable(move);
	}

	else if (choice == 2) {
		char name[50];
		printf("Enter the Book Name...\n");
		scanf("%s", name);
		while (move->book_name != name) {
			move = move->next;
		}

		search_book_variable(move);
	}

	else {
		printf("Wrong options, please try again...\n");
		scanf("%d", &choice);
	}
	

}

void search_book_variable(node*variable){
	
	printf("This book is %s\n", variable->available);
	printf("#########################\n");
	printf("ID: %d\n", variable->book_id);
	printf("Name: %s\n", variable->book_name);
	printf("Author: %s\n", variable->author);
	printf("Quantity: %d\n", variable->quantity);
	printf("Price: %.2lf\n", variable->price); 
	printf("Shelf: %d\n", variable->shelf_no);
	printf("#########################\n");


}


