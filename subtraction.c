#include "apc.h"

int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
	Dlist *temp1 = *tail1;                     // Start from least significant digit of operand1
	Dlist *temp2 = *tail2;                     // Start from least significant digit of operand2
	int borrow = 0;                            // Initialize borrow to 0

	while (temp1 || temp2)                     // Loop until both operands are processed
	{
		if (temp1 && temp2)                    // If both operands have digits
		{
			if (temp1->data < temp2->data)     // If borrowing is needed
			{
				int data1 = temp1->data + 10;  // Add 10 to current digit
				Dlist *mytemp = temp1->prev;  // Start borrow from higher digit

				if (mytemp != NULL)
				{
					do                          // Borrow logic
					{
						if (mytemp->data != 0)
						{
							mytemp->data -= 1;  // Reduce first non-zero digit
							break;
						}
						else
							mytemp->data = 9;   // Set 0 to 9 and continue backward
						
						mytemp = mytemp->prev;
					} while (mytemp);
				}

				int res = data1 - temp2->data; // Compute difference
				dl_insert_first(headR, tailR, res);  // Store result
				borrow = 1;
			}
			else
			{
				if (borrow == 1)                // If borrow flag is set
				{
					int data = temp1->data - temp2->data;
					dl_insert_first(headR, tailR, data);
					borrow = 0;
				}
				else
				{
					int data = temp1->data - temp2->data;
					dl_insert_first(headR, tailR, data);
				}
			}
			temp1 = temp1->prev;                // Move to next digit
			temp2 = temp2->prev;
		}
		else if (temp1 && temp2 == NULL)        // Remaining digits in operand1
		{
			if (borrow == 1)
			{
				int data = temp1->data;
				dl_insert_first(headR, tailR, data);
				borrow = 0;
			}
			else
			{
				int data = temp1->data;
				dl_insert_first(headR, tailR, data);
			}
			temp1 = temp1->prev;
		}
	}

	Dlist *temp3 = *headR;                      // Pointer to result head
	while (temp3)                               // Remove leading zeros
	{	
		if (temp3->data == 0)
			dl_delete_first(headR, tailR);
		else 
			break;
		temp3 = temp3->next;
	}
}
