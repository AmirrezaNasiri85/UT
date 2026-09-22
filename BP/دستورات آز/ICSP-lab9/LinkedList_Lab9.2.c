#include <stdio.h>
#include <string.h>
typedef struct student std;

struct student {
	int grade;
	char name[20];
	std* next;
};


typedef int color;

//
// Insert is used to enter a new item into the stack
//Input: 
// Output: 0 if not successful
//			1 if successful
//
int Insert(std * d, char* name, int grade)
{
	//Step 1: Allocate memory
	std *temp = (std *)malloc(sizeof(std));
	if (temp == NULL)
		return 0;		//If not successful, return 0;
	temp->next = NULL;
	temp->grade = grade;
	strcpy(temp->name, name);
	//step 2: get the link of the first item and put as the next of temp
	temp->next = d->next;
	//step 3: update dummy's next to the new node
	d->next = temp;
	return 1;
}

int PrintList(std* d)
{
	//Print the list until reaching the last node
	while (d->next != NULL) {
		d = d->next;
		printf("the grade of %s = %d\n", d->name, d->grade);
	}

}

////////////////
//This function is designed to remove a node from the list
int Remove(std* d, char* name)
{
	std * prevNode, curNode;
	prevNode = d;
	while (prevNode != NULL) {
		curNode = prevNode->next;
		if (!strcmp(curNode->name, name)) { //The names are equal
			prevNode->next = curNode->next;
			return 0;
		}
		prevNode = curNode;
	}
	printf("No such a name found\n");
	return 1;

}

int main()
{
	char names[][20] = { "Golzari", "Hadian","Blookazari" };
	std dummy;  //Dummy node for the start of the linked list
	dummy.next = NULL;
	PrintList(&dummy);
	Insert(&dummy, names[0], 18);
	PrintList(&dummy);
	Insert(&dummy, names[1], 19);
	PrintList(&dummy);
	Insert(&dummy, names[2], 20);
	PrintList(&dummy);
	Remove(&dummy, "Golzari");
	PrintList(&dummy);




}