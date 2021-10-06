#include <stdio.h>
#include <windows.h>
#include <conio.h>

/// TRUE FALSE DEFINITION
#define TRUE 1
#define FALSE 0


/// BOOK STRUCTURE ///
/*  Here is the declaration of Book structure
	that contain 8 fields to store data
	related to Book
 */
struct Book {
	char author[20];
	char library[20];
	char publisher[20];
	int cost;
	char subject[20];
	int index;
	char loan_to[20];
	char due_date[20];
	struct Book *NEXT;          // To store address of next node
};
/*
	Head node address. It is global so
	that it can be accessed easily any where.
*/
struct Book *HEAD = NULL;

/// Function declaration here
void title();

void data_opt();

void load_data();

void menu_opt();

void main_menu();

void add_new();

void display_menu();

void display_list_title();

void display_node(struct Book *);

void modify();

void delete();

void save_data();

void sort();

void search_book();

void search_author();

/* main function to control the flow of program */
int main() {
	data_opt();                     // Option for new data or saved data
	system("cls");        			// System command to clear screen
	main_menu();                    // Main menu for all options
	return 0;
}

/* Function to print title for library */
void title() {
	printf("*****************************\n");
	printf("  Library Management System\n");
	printf("*****************************\n");
}

/*
	This function load data from a file "data_file.txt"
	and store data in linked list using Queue Data structure
	and address of head node is stored in HEAD variable
    This function is only called when relevant data option
    is chosen to load previously saved data.
*/
void load_data() {
	FILE *file;
	struct Book *b = (struct Book *) malloc(sizeof(struct Book));
	int dd, mm, yyyy;
	if ((file = fopen("data_file.txt", "r")) == NULL) {
		printf("Error! opening file");
	} else {
		while (fscanf(file, "%s %s %s %d %s %d %s %d %d %d", b->author, b->library, b->publisher, &b->cost, b->subject,
		              &b->index, b->loan_to, &dd, &mm, &yyyy) != EOF) {

			sprintf(b->due_date, "%d%d%d", dd, mm, yyyy);
			b->NEXT = NULL;
			if (HEAD == NULL) {
				HEAD = b;
			} else {
				struct Book *LAST = HEAD;
				while (LAST->NEXT != NULL) {
					LAST = LAST->NEXT;
				}
				LAST->NEXT = b;
			}

			b = (struct Book *) malloc(sizeof(struct Book));
		}
	}
	fclose(file);
}

/// DATA OPTION ///
/*
	This function is called at the very first of
    program execution.
	It is used to let the user to choose whether
    to continue with new data or load saved data.
*/
void data_opt() {
	int opt = 1;
	do {
		title();
		printf("1 -> Load Previous Data\n");
		printf("2 -> Start With New Data\n\n");
		printf("Note: Use Integer Only\n");
		printf("------------------------------\n");
		printf("Your Choice: ");
		scanf("%d", &opt);
		switch (opt) {
			case 1:
				load_data();
				opt = TRUE;
				break;
			case 2:
				HEAD = NULL;
				opt = TRUE;
				break;
			default:
				printf("------------------------------\n");
				printf("Invalid Input! Try Again\n");
				printf("Press Any Key To Continue\n");
				printf("------------------------------\n");
				getch();
				system("cls");
		}
	} while (opt != TRUE);
}

/// MAIN MENU ///
/*
	After data_opt this main_menu function is called.
	This function allow the user to choose option
    from menu printed in menu_opt function.
    A switch case statement is used here to choose option.
*/
void main_menu() {
	int opt;
	do {
		title();
		menu_opt();
		scanf("%d", &opt);
		switch (opt) {
			case 1:
				system("cls");
				add_new();
				break;
			case 2:
				display_menu();
				break;
			case 3:
				modify();
				break;
			case 4:
				delete();
				break;
			case 5:
				save_data();
				break;
			case 6:
				sort();
				break;
			case 7:
				search_book();
				break;
			case 8:
				search_author();
				break;
			case 0:
				break;
			default:
				printf("Error: Invalid Input! Try Again\n");
				break;
		}
		printf("\n------------------------------\n");
		printf("Press Any Key To Continue\n");
		printf("------------------------------\n");
		getch();
		system("cls");
	} while (opt != FALSE);
}

/* To print options for main_menu */
void menu_opt() {
	printf("1 -> Add New Entries\n");
	printf("2 -> Browse Entries\n");
	printf("3 -> Modify Entry\n");
	printf("4 -> Delete Entry\n");
	printf("5 -> Save Data\n");
	printf("6 -> Sort Alphabetically\n");
	printf("7 -> Search By Book Name\n");
	printf("8 -> Search By Author Name\n");
	printf("0 -> Exit");
	printf("\nNote: Use Integer Only\n");
	printf("------------------------------\n");
	printf("Your Choice: ");

}

/// ADD NEW ENTRY ///
/*
 * This function allows the user to add
 * new entry in the list.
 * All the information is entered by the user and
 * new node is added to the end of linked list.
 * */
void add_new() {
	struct Book *b = (struct Book *) malloc(sizeof(struct Book));
	title();
	printf("Enter Author Name (MAX 20 Character): ");
	scanf("%s", b->author);
	printf("Enter Library Name (MAX 20 Character): ");
	scanf("%s", b->library);
	printf("Enter Publisher (MAX 20 Character): ");
	scanf("%s", b->publisher);
	printf("Enter Replacement Cost (Integer Only): ");
	scanf("%d", &b->cost);
	printf("Enter Subject to material (MAX 20 Character): ");
	scanf("%s", b->subject);
	printf("Enter Index Number (Integer Only): ");
	scanf("%d", &b->index);
	printf("Currently on loan to:  (MAX 20 Character): ");
	scanf("%s", b->loan_to);
	int dd = 01, mm = 01, yyyy = 2021;
	printf("Enter Date DD/MM/YYYY (Use Integer Only)\nDD : ");
	scanf("%d", &dd);
	printf("MM : ");
	scanf("%d", &mm);
	printf("YYYY : ");
	scanf("%d", &yyyy);
	sprintf(b->due_date, "%d-%d-%d", dd, mm, yyyy);
	b->NEXT = NULL;
	if (HEAD == NULL) {
		HEAD = b;
	} else {
		struct Book *LAST = HEAD;
		while (LAST->NEXT != NULL) {
			LAST = LAST->NEXT;
		}
		LAST->NEXT = b;
	}

	printf("\n*Added Successfully*\n");
}

/// BROWSE LIST ///
void display_menu() {
	system("cls");
	display_list_title();
	struct Book *b = HEAD;
	while (b != NULL) {
		display_node(b);
		b = b->NEXT;
	}
}

void display_list_title() {
	printf("********************************************************************************************************\n");
	printf("%72s", "Library Management System - All Entries\n");
	printf("********************************************************************************************************\n");
	printf("%12s |%12s |%12s |%7s |%12s |%7s |%12s |%15s\n", "Author", "Book Name", "Publisher", "Cost", "Subject",
	       "Index", "Loan To", "Dua Date");
	printf("--------------------------------------------------------------------------------------------------------\n");
}

void display_node(struct Book *b) {
	printf("%12s |%12s |%12s |%7d |%12s |%7d |%12s |%15s\n", b->author, b->library, b->publisher, b->cost,
	       b->subject,
	       b->index, b->loan_to, b->due_date);
}

void swap(struct Book *a, struct Book *b)
{
	struct Book * temp = (struct Book*) malloc(sizeof (struct Book));
	strcpy(temp->author, a->author);
	strcpy(a->author, b->author);
	strcpy(b->author, temp->author);


	strcpy(temp->library, a->library);
	strcpy(a->library, b->library);
	strcpy(b->library, temp->library);

	strcpy(temp->publisher, a->publisher);
	strcpy(a->publisher, b->publisher);
	strcpy(b->publisher, temp->publisher);

	strcpy(temp->subject, a->subject);
	strcpy(a->subject, b->subject);
	strcpy(b->subject, temp->subject);

	strcpy(temp->loan_to, a->loan_to);
	strcpy(a->loan_to, b->loan_to);
	strcpy(b->loan_to, temp->loan_to);

	strcpy(temp->due_date, a->due_date);
	strcpy(a->due_date, b->due_date);
	strcpy(b->due_date, temp->due_date);

	temp->cost = a->cost;
	a->cost = b->cost;
	b->cost=temp->cost;

	temp->index = a->index;
	a->index = b->index;
	b->index=temp->index;
}

/// SORT ALPHABETICALLY ///
void sort() {
	struct Book *temp_head = NULL;
	struct Book *b = HEAD;
	struct Book *new_node = (struct Book *) malloc(sizeof(struct Book));
	while (b != NULL) {
		strcpy(new_node->author, b->author);
		strcpy(new_node->library, b->library);
		strcpy(new_node->publisher, b->publisher);
		strcpy(new_node->subject, b->subject);
		strcpy(new_node->loan_to, b->loan_to);
		strcpy(new_node->due_date, b->due_date);

		new_node->cost = b->cost;
		new_node->index = b->index;
		new_node->NEXT = NULL;
		if (temp_head == NULL) {
			temp_head = new_node;
		} else {
			struct Book *LAST = temp_head;
			while (LAST->NEXT != NULL) {
				LAST = LAST->NEXT;
			}
			LAST->NEXT = new_node;
		}
		b = b->NEXT;
		new_node = (struct Book *) malloc(sizeof(struct Book));
	}
	struct Book *node = temp_head;
	while (node != NULL) {
		struct Book *node2 = node->NEXT;
		while (node2 != NULL) {
			if(strcmp(node->library,node2->library)>0){
				swap(node,node2);
			}
			node2 = node2->NEXT;
		}
		node = node->NEXT;
	}

	node = temp_head;
	system("cls");
	display_list_title();
	while (node != NULL) {
		display_node(node);
		node = node->NEXT;
	}
}

/// SAVE CURRENT DATA ///
/*
	Data currently in the linked list
    is saved in file through file handling.
*/
void save_data() {
	FILE *file;
	struct Book *b = HEAD;
	if ((file = fopen("data_file.txt", "w")) == NULL) {
		printf("Error! opening file");
	} else {
		while (b != NULL) {
			fprintf(file, "%s %s %s %d %s %d %s %s\n", b->author, b->library, b->publisher, b->cost, b->subject,
			        b->index, b->loan_to, b->due_date);
			b = b->NEXT;
		}
	}
	fclose(file);
	printf("\n *Data Saved Successfully*\n");
}

/// MODIFY ENTRY ///
void modify() {
	char name[20];
	int flag = FALSE;
	struct Book *b = HEAD;

	system("cls");
	title();
	printf("Enter Book Name: ");
	scanf("%s", name);
	while (b != NULL) {
		if (strcmp(b->library, name) == FALSE) {
			flag = TRUE;
			break;
		}
		b = b->NEXT;
	}
	if (flag == FALSE) {
		printf("\n*No Data Found*\n");
	} else {
		int opt = 0;
		do {
			system("cls");

			display_list_title();
			display_node(b);

			printf("\n\n1-> Author Name");
			printf("\n2-> Library Name");
			printf("\n3-> Publisher");
			printf("\n4-> Replacement Cost");
			printf("\n5-> Subject To Material");
			printf("\n6-> Index Number");
			printf("\n7-> Currently On Loan To");
			printf("\n8-> Due Date");
			printf("\n9-> Done Modification");
			printf("\n\nEnter Number to Modify Corresponding Data: ");
			scanf("%d", &opt);
			int dd = 01, mm = 01, yyyy = 2021;
			switch (opt) {
				case 1:
					printf("\nEnter Author Name (MAX 20 Character): ");
					scanf("%s", b->author);
					break;
				case 2:
					printf("\nEnter Book Name (MAX 20 Character): ");
					scanf("%s", b->library);
					break;
				case 3:
					printf("\nEnter Publisher (MAX 20 Character): ");
					scanf("%s", b->publisher);
					break;
				case 4:
					printf("\nEnter Replacement Cost (Integer Only): ");
					scanf("%d", &b->cost);
					break;
				case 5:
					printf("\nEnter Subject to material (MAX 20 Character): ");
					scanf("%s", b->subject);
					break;
				case 6:
					printf("\nEnter Index Number (Integer Only): ");
					scanf("%d", &b->index);
					break;
				case 7:
					printf("\nCurrently on loan to:  (MAX 20 Character): ");
					scanf("%s", b->loan_to);
					break;
				case 8:
					printf("\nEnter Date DD/MM/YYYY (Use Integer Only)\nDD : ");
					scanf("%d", &dd);
					printf("MM : ");
					scanf("%d", &mm);
					printf("YYYY : ");
					scanf("%d", &yyyy);
					sprintf(b->due_date, "%d-%d-%d", dd, mm, yyyy);
					break;
				case 9:
					printf("\n* Data Saved Successfully *\n");
					break;
				default:
					printf("\n* Error: Invalid Input *");
					break;
			}
			if (opt != 9) {
				printf("\n\nPress Any Key To Continue");
				getch();
			}
		} while (opt != 9);
	}
}

/// DELETE ENTRY ///
void delete() {
	char name[20];
	int flag = FALSE;
	struct Book *b = HEAD;
	struct Book *pre = NULL;

	system("cls");
	title();
	printf("Enter Book Name: ");
	scanf("%s", name);
	system("cls");
	display_list_title();
	while (b != NULL) {
		if (strcmp(b->library, name) == FALSE) {
			flag = TRUE;
			display_node(b);
			break;
		}
		pre = b;
		b = b->NEXT;
	}
	if (flag == FALSE) {
		printf("\n*No Data Found*\n");
	} else {
		char temp[20];
		printf("\nType:\nyes     -> To Confirm Deletion");
		printf("\nAny Key -> To Cancel Deletion");
		printf("\n\nEnter Your Choice Here: ");
		scanf("%s", temp);
		if (strcmp(temp, "yes") == 0) {
			if (pre == NULL) {
				HEAD = b->NEXT;
			} else {
				pre->NEXT = b->NEXT;
			}
			printf("\n* Data Deleted Successfully *\n");
		}
	}
}

/// SEARCH BY BOOK NAME ///
void search_book() {
	char name[20];
	int flag = FALSE;
	struct Book *b = HEAD;

	system("cls");
	title();
	printf("Enter Book Name: ");
	scanf("%s", name);
	system("cls");
	display_list_title();
	while (b != NULL) {
		if (strcmp(b->library, name) == FALSE) {
			flag = TRUE;
			display_node(b);
		}
		b = b->NEXT;
	}
	if (flag == FALSE) {
		printf("\n*No Data Found*\n");
	}
}

/// SEARCH BY AUTHOR NAME ///
void search_author() {
	char name[20];
	int flag = FALSE;
	struct Book *b = HEAD;

	system("cls");
	title();
	printf("Enter Author Name: ");
	scanf("%s", name);
	system("cls");
	display_list_title();
	while (b != NULL) {
		if (strcmp(b->author, name) == FALSE) {
			flag = TRUE;
			display_node(b);
		}
		b = b->NEXT;
	}
	if (flag == FALSE) {
		printf("\n*No Data Found*\n");
	}

}




