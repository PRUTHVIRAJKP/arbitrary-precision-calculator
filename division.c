#include "apc.h"

int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
	unsigned long int count = 0;                     // Initialize result counter

	while (1)
	{
		Dlist *temp1 = *head1, *temp2 = *head2;
		int list1 = 0, list2 = 0, flag = 0;

		while (temp1)                                // Count digits in dividend
		{
			list1++;
			temp1 = temp1->next;
		}

		while (temp2)                                // Count digits in divisor
		{
			list2++;
			temp2 = temp2->next;
		}

		if (list1 < list2)                           // Dividend < Divisor
		{
			printf("\nResult is %ld\n", count);      // Print final result
			return 0;
		}
		else if (list1 == list2)                     // Equal lengths
		{
			temp1 = *head1;
			temp2 = *head2;
			while (temp1)                            // Compare digit-by-digit
			{	
				if (temp1->data >= temp2->data)      // If dividend ≥ divisor
				{
					flag = 1;
					break;
				}
				else                                 // Dividend < divisor
				{
					printf("\nResult is %ld\n", count);
					return 1;
				}
				temp1 = temp1->next;
				temp2 = temp2->next;
			}
		}
		else                                          // Dividend has more digits
		{
			flag = 1;
		}

		if (flag == 1)                                // If division can proceed
		{
			count++;                                  // Increment quotient
			subtraction(head1, tail1, head2, tail2, headR, tailR); // Subtract divisor
			*head1 = *headR;                          // Update dividend to result
			*tail1 = *tailR;
			*headR = NULL;                            // Reset result list
			*tailR = NULL;
		}
	}
}
