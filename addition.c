#include "apc.h"

int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
	Dlist *temp1 = *tail1;              // Set temp1 to last digit of operand1
	Dlist *temp2 = *tail2;              // Set temp2 to last digit of operand2
	int carry = 0;                      // Initialize carry to 0

	while (temp1 || temp2)             // Loop while at least one operand has digits
	{
		if (temp1 && temp2)            // If both operands have digits
		{	
			int data;
			if (carry == 1)            // Add carry if it exists
			{
				data = temp1->data + temp2->data + carry;
				carry = 0;
			}
			else
				data = temp1->data + temp2->data;

			if (data > 9)              // Handle carry for result > 9
			{
				dl_insert_first(headR, tailR, data % 10); // Store unit digit
				carry = 1;
			}
			else
				dl_insert_first(headR, tailR, data % 10); // Store digit

			temp1 = temp1->prev;       // Move to previous digit
			temp2 = temp2->prev;
		}
		else if (temp1 && temp2 == NULL) // If only operand1 has digits
		{
			int data;
			if (carry == 1)
			{
				data = temp1->data + carry;
				carry = 0;
			}
			else
				data = temp1->data;

			if (data > 9)
			{
				dl_insert_first(headR, tailR, data % 10);
				carry = 1;
			}
			else
				dl_insert_first(headR, tailR, data % 10);

			temp1 = temp1->prev;
		}
		else if (temp2 && temp1 == NULL) // If only operand2 has digits
		{
			int data;
			if (carry == 1)
			{
				data = temp2->data + carry;
				carry = 0;
			}
			else
				data = temp2->data;

			if (data > 9)
			{
				dl_insert_first(headR, tailR, data % 10);
				carry = 1;
			}
			else
				dl_insert_first(headR, tailR, data % 10);

			temp2 = temp2->prev;
		}
	}

	if (carry == 1)                     // Insert remaining carry if any
	{
		dl_insert_first(headR, tailR, carry);
		carry = 0;
	}
}
