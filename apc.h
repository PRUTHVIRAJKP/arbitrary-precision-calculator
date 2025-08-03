#ifndef APC_H
#define APC_H


#define SUCCESS 0
#define FAILURE -1

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>
typedef struct node
{
	struct node *prev;
	int data;
	struct node *next;

}Dlist;

/* Include the prototypes here */

/*store the operands into the list */
void digit_to_list(Dlist **head1,Dlist **tail1,Dlist **head2,Dlist **tail2,char *argv[]);

/*Addition */
int addition(Dlist **head1,Dlist **tail1,Dlist **head2,Dlist **tail2,Dlist **headR,Dlist **tailR);

/*subtraction*/
int subtraction(Dlist **head1,Dlist **tail1,Dlist **head2,Dlist **tail2,Dlist **headR,Dlist **tailR);

/*Multiplication*/
int multiplication(Dlist **head1,Dlist **tail1,Dlist **head2,Dlist **tail2,Dlist **headR,Dlist **tailR);


/*Division */
int division(Dlist **head1,Dlist **tail1,Dlist **head2,Dlist **tail2,Dlist **headR,Dlist **tailR);

/*function used to insert data as a first node in the double linkded list*/
//used to insert resultant
int dl_insert_first(Dlist **head, Dlist **tail, int data);

/*function used to insert data as a last node in the double linkded list*/
//used to insert operator
int dl_insert_last(Dlist **head, Dlist **tail, int data);

/*used to print the resultant list*/
void print_list(Dlist *head);

int dl_delete_first(Dlist **head, Dlist **tail);

int dl_delete_list(Dlist **head, Dlist **tail);




#endif
