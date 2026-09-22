#include <stdio.h>
#include <stdlib.h>
#define NUM_OF_PARTICIPANTS 5
typedef struct information
{
   float first_parameter;
   float second_parameter;
   struct information *next;
}information;
information* CreateNode(float first_parameter_value , float second_parameter_value)
{
    information *the_node;
    // Allocating memory
    the_node = (information*)malloc(sizeof(information));
    the_node->first_parameter = first_parameter_value;
    the_node->second_parameter = second_parameter_value;
    the_node->next = NULL;
    return the_node;
}

void printInformation (information *head)
{
    information *temp;
    temp = head;
    int i = 0;
    while(temp->next != NULL){
    temp = temp->next;
        printf("participant %d's information:\n", i+1);
        printf("first_parameter: %f\n", temp->first_parameter);
        printf("second_parameter: %f\n", temp->second_parameter);
        i++;
    }
    printf("******************\n");
}

int main()
{
    information *head , *temp;
    head = CreateNode(0 , 0);
    temp = head;
    // Allocating memory
    for(int i=0; i<NUM_OF_PARTICIPANTS; i++){
        temp->next = CreateNode(i+1 , 2*(i+1));
        temp = temp->next;
    }
    printInformation (head);
    return 0;
}