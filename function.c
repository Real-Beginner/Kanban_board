#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "function.h"

int display_menu()
{
	printf("Menu:\n");

	printf("1. Display board\n");

	printf("2. Load board from a file\n");

	printf("3. Edit list\n");

	printf("4. Edit Board\n");

	printf("5. Save board to a file\n");

	printf("6. Quit\n");

	printf("Enter your choice (1-6):");


	int option;
	scanf("%d", &option);
	return option;
}

int display_options_list()
{
	printf("Options:\n");

	printf("1. Edit the name of an item\n");

	printf("2. Add a new item\n");

	printf("3. Delete an item\n");

	printf("4. Return to main menu\n");

	printf("Enter your choice (1-4):");


	int option;
	scanf("%d", &option);while(getchar() != '\n'){}
	return option;
}

int display_options_board()
{
	printf("\nOptions:\n");

	printf("1. Edit the name of a list \n");

	printf("2. Add a new list\n");

	printf("3. Delete a list\n");

	printf("4. Return to main menu\n");

	printf("Enter your choice (1-4):");


	int option;
	scanf("%d", &option);while(getchar() != '\n'){}
	return option;
}

names* load_board() {
	char filename[20];
	printf("Enter filename: ");
	scanf("%s", filename);

	FILE *fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("\nError: could not open file %s\n", filename);
		puts("");
		return NULL;
	}

	struct names *head = NULL;
	struct names *currentList = NULL;

	char line[1000];
	while (fgets(line, sizeof(line), fp) != NULL) {
		// Remove newline character if present
		if (line[strlen(line) - 1] == '\n') {
			line[strlen(line) - 1] = '\0';
		}

		// Check if line ends with ':' (indicating a list)
		if (line[strlen(line) - 1] == ':') {
			// Create a new list
			struct names *newList = malloc(sizeof(names));
			line[strlen(line)-1]= '\0';
			if (newList == NULL) {
				printf("Memory allocation failed\n");
				// Clean up allocated memory
				fclose(fp);
				free(head);
				return NULL;
			}

			// Initialize list properties
			strcpy(newList->name, line);
			newList->next = NULL;
			newList->itemsPtr = NULL;

			// Update pointers
			if (head == NULL) {
				head = newList; // Set head if it's not set already
			}
			if (currentList != NULL) {
				currentList->next = newList;
			}
			currentList = newList;
		} else {
			// It's an item, create a new item
			struct items *newItem = malloc(sizeof(items));
			if (newItem == NULL) {
				printf("Memory allocation failed\n");
				// Clean up allocated memory
				fclose(fp);
				free(head);
				return NULL;
			}
			// Initialize item properties
			strcpy(newItem->itemName, line);
			newItem->next = NULL;

			// Add item to the current list
			if (currentList == NULL) {
				printf("Error: No list specified for the item\n");
				// Clean up allocated memory
				fclose(fp);
				free(head);
				return NULL;
			}
			if (currentList->itemsPtr == NULL) {
				currentList->itemsPtr = newItem;
			} else {
				struct items *lastItem = currentList->itemsPtr;
				while (lastItem->next != NULL) {
					lastItem = lastItem->next;
				}
				lastItem->next = newItem;
			}
		}
	}
	fclose(fp);
	printf("Board loaded successfully from %s\n", filename);puts("");
	return head; // Return the head pointer
}

void save_board(struct names* head)
{
	struct names* curr = head;

	char filename[100];
	printf("Enter the filename to save: ");
	scanf("%s", filename);

	FILE* file;
	char data[1000] = "";
	char colon[3] = ":\n";
	char newline[3] = "\n";

	while (curr != NULL)
	{
		char temp[20];
		strcpy(temp, curr->name);
		strcat(temp, colon);
		strcat(data, temp);

		struct items* ptr = curr->itemsPtr;
		while (ptr != NULL)
		{
			strcpy(temp, ptr->itemName);
			strcat(temp, newline);
			strcat(data, temp);
			ptr = ptr->next;
		}
		curr = curr->next;
	}

	file = fopen(filename, "w");
	if (file == NULL)
	{
		printf("Error opening file.\n");

		return;
	}
	else
	{
		fprintf(file, data);
		printf("Saved successfully to %s\n", filename);puts("");

	}
	// Close the file
	fclose(file);
}

names* default_values()
{
	struct items *headItems1 = malloc(sizeof(items));
	strcpy(headItems1->itemName, "3070_RTX");
	headItems1->next = NULL;

	struct names *head = malloc(sizeof(names));
	strcpy(head->name, "Nick");
	head->itemsPtr = headItems1;
	head->next = NULL;

	struct items *headItems2 = malloc(sizeof(items));
	strcpy(headItems2->itemName, "Oculus_Quest_2");
	headItems2->next = NULL;

	struct names *current = malloc(sizeof(names));
	strcpy(current->name, "Tim");
	current->itemsPtr = headItems2;
	current->next = NULL;
	head->next = current;

	struct items *headItems3 = malloc(sizeof(items));
	strcpy(headItems3->itemName, "Oculus_Quest_1");
	headItems3->next = NULL;

	struct items *headItems3a = malloc(sizeof(items));
	strcpy(headItems3a->itemName, "3070_RTX");
	headItems3a->next = NULL;
	headItems3->next = headItems3a;

	current = malloc(sizeof(names));
	strcpy(current->name, "Dante");
	current->itemsPtr = headItems3;
	current->next = NULL;
	head->next->next = current;


	struct items *headItems4 = malloc(sizeof(items));
	strcpy(headItems4->itemName, "Oculus_Pro");
	headItems4->next = NULL;

	struct items *headItems4a = malloc(sizeof(items));
	strcpy(headItems4a->itemName, "Oculus_Quest_1");
	headItems4a->next = NULL;
	headItems4->next = headItems4a;

	current = malloc(sizeof(names));
	strcpy(current->name, "Abey");
	current->itemsPtr = headItems4;
	current->next = NULL;
	head->next->next->next = current;

	return head;
}

void display_board(struct names *head)
{
	puts("");
	struct names *curr= head;
	while(curr != NULL)
	{
		printf("%s:", curr->name);puts("");
		struct items *ptr= curr->itemsPtr;
		while(ptr != NULL)
		{
			printf("\t%s", ptr->itemName);puts("");
			ptr= ptr->next;
		}
		curr = curr->next;
	}
	puts("");
}

void edit_list(struct names *head)
{
	struct names *curr = head;

	char name_to_edit[20];
	printf("Enter the name of the list to edit: ");
	scanf("%s", name_to_edit);while(getchar() != '\n'){}

	while(curr != NULL)
	{
		if(!strcmp(curr->name, name_to_edit))
		{
			int loop = 1;
			puts("");
			while(loop)
			{
				switch(display_options_list())
				{
				case 1:
					edit_item(curr);
					break;
				case 2:
					add_item(curr);
					break;
				case 3:
					delete_item(curr);
					break;
				case 4: puts("");loop= 0;break;
				default: puts("");break;
				}
			}
			break;
		}
		curr = curr->next;
	}

	if(curr == NULL)
	{
		printf("Can't find list");puts("");puts("");
	}
}

void edit_item(struct names *i)
{
	struct items *curr = i->itemsPtr;
	char name[20];
	printf("Enter the name of the item to edit: ");
	scanf("%s",name);while(getchar() != '\n'){}

	while(curr != NULL)
	{
		if(!strcmp(curr->itemName, name))
		{
			char new_name[20];
			printf("Enter new name for item '%s':",name);
			scanf("%s",new_name);while(getchar() != '\n'){}puts("");
			strcpy(curr->itemName,new_name);
			break;
		}
		curr= curr->next;
	}

	if(curr==NULL)
	{
		printf("Can't find item");puts("");puts("");
	}
}

void add_item(struct names *i)
{
	// If there are no items in the list, create a new item as the first item
	if (i->itemsPtr == NULL) {
		char new_item_name[20];
		printf("Enter the name of the new item: ");
		scanf("%s", new_item_name);while(getchar() != '\n'){}puts("");puts("");

		struct items *newItem = malloc(sizeof(struct items));
		if (newItem == NULL) {
			printf("Memory allocation failed\n");
			return;
		}
		strcpy(newItem->itemName, new_item_name);
		newItem->next = NULL;

		i->itemsPtr = newItem;
	} else {
		// If there are existing items, find the last item and add a new item after it
		struct items *curr = i->itemsPtr;
		while (curr->next != NULL) {
			curr = curr->next;
		}

		char new_item_name[20];
		printf("Enter the name of the new item: ");
		scanf("%s", new_item_name);while(getchar() != '\n'){}

		struct items *newItem = malloc(sizeof(struct items));
		if (newItem == NULL) {
			printf("Memory allocation failed\n");
			return;
		}
		strcpy(newItem->itemName, new_item_name);
		newItem->next = NULL;

		curr->next = newItem;
		puts("");
	}
}

void delete_item(struct names *i)
{
	struct items *curr = i->itemsPtr;

	if (curr == NULL)//that person has no items because he is too broke to buy any
	{
		printf("List is empty\n");
		return;
	}

	char name_of_item_to_delete[20];
	printf("Enter the name of the item to delete: ");
	scanf("%s", name_of_item_to_delete);while(getchar() != '\n'){}

	// Special case: If the item to be deleted is the first item
	if (!strcmp(curr->itemName, name_of_item_to_delete))
	{
		struct items *temp = curr;
		curr = curr->next;
		free(temp);
		return;
	}

	// Traverse the list to find the item to be deleted
	struct items *prev = i->itemsPtr;
	curr = i->itemsPtr->next;
	while (curr != NULL && strcmp(curr->itemName, name_of_item_to_delete) != 0) {
		prev = curr;
		curr = curr->next;
	}

	// If the item is found, delete it
	if (curr != NULL)
	{
		prev->next = curr->next;
		free(curr);puts("");
	}
	else
	{
		puts("");
		printf("Item '%s' does not exists", name_of_item_to_delete);puts("");puts("");
	}
}

void edit_board(struct names *head)
{
	struct names *curr = head;
	int loop = 1;
	while(loop)
	{
		switch(display_options_board())
		{
		case 1:
			edit_name(curr);
			break;
		case 2:
			add_name(curr);
			break;
		case 3:
			delete_name(curr);
			break;
		case 4: puts("");loop= 0;break;
		default:break;
		}
	}

}

void edit_name(struct names *i)
{
	struct names *curr = i;
	char list_to_edit[20];
	printf("Enter the name of the list to edit: ");
	scanf("%s", list_to_edit);while(getchar() != '\n'){}

	while(curr!=NULL)
	{
		if(!strcmp(curr->name, list_to_edit))
		{
			char new_name[20];
			printf("Enter new name for item '%s':",list_to_edit);
			scanf("%s",new_name);while(getchar() != '\n'){}
			strcpy(curr->name,new_name);
			break;
		}
		curr= curr->next;
	}

	if(curr==NULL)
	{
		printf("Can't find list");puts("");
	}
}

void add_name(struct names *i)
{
	struct names *curr = i;
	while(curr->next!= NULL)
	{
		curr= curr->next;
	}

	char list_to_add[20];
	printf("Enter the name of the new list: ");
	scanf("%s", list_to_add);while(getchar() != '\n'){}

	struct names *newList = malloc(sizeof(items));
	strcpy(newList->name,list_to_add);
	newList->next = NULL;
	curr->next = newList;
}

void delete_name(struct names *i)
{
	struct names *curr = i;

	char name_of_list_to_delete[20];
	printf("Enter the name of the list to delete: ");
	scanf("%s", name_of_list_to_delete);while(getchar() != '\n'){}

	// Special case: If the item to be deleted is the first item
	if (!strcmp(curr->name, name_of_list_to_delete))
	{
		struct names *temp = curr;
		curr = curr->next;
		free(temp);
		return;
	}

	// Traverse the list to find the item to be deleted
	struct names *prev = curr;
	curr = curr->next;
	while (curr != NULL && strcmp(curr->name, name_of_list_to_delete) != 0) {
		prev = curr;
		curr = curr->next;
	}

	// If the item is found, delete it
	if (curr != NULL)
	{
		prev->next = curr->next;
		free(curr);
	}
	else
	{
		printf("List '%s' does not exists", name_of_list_to_delete);puts("");
	}
}

void kanban()
{
	struct names *head = default_values();
	setbuf(stdout,NULL);
	int loop = 1;
	while(loop)
	{
		switch(display_menu())
		{
		case 1:
			display_board(head);
			break;
		case 2:
			head=load_board();
			break;
		case 3:
			edit_list(head);
			break;
		case 4:
			edit_board(head);
			break;
		case 5:
			save_board(head);
			break;
		case 6:
			loop=0; break;
		default:
			while(getchar() != '\n'){}
			puts("");
			break;
		}
	}
}
