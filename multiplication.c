#include "apc.h"

int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
	Dlist *temp1 = *tail1, *temp2 = *tail2;
	Dlist *headr1 = NULL, *tailr1 = NULL;       // Store partial result for first row
	Dlist *headr2 = NULL, *tailr2 = NULL;       // Store partial result for subsequent rows
	int count = 0;                              // Track position (used for padding zeros)
	int carry = 0;

	while (temp2)                               // Loop through each digit of operand2 (multiplier)
	{
		carry = 0;

		for (int i = 0; i < count; i++)         // Add trailing zeros to align position
		{
			dl_insert_first(&headr2, &tailr2, 0);
		}

		temp1 = *tail1;                         // Reset to last digit of operand1 (multiplicand)

		while (temp1)                           // Multiply each digit of operand1 with current digit of operand2
		{
			int data;

			if (carry != 0)
			{
				data = temp1->data * temp2->data + carry;
				carry = 0;
			}
			else
				data = temp1->data * temp2->data;

			if (data > 9)                        // Compute carry if result > 9
			{
				carry = data / 10;
			}

			if (count == 0)                      // Insert into first row result
				dl_insert_first(&headr1, &tailr1, data % 10);
			else                                 // Insert into next row result
				dl_insert_first(&headr2, &tailr2, data % 10);

			temp1 = temp1->prev;
		}

		if (carry != 0)                          // Add leftover carry if present
		{
			if (count == 0)
				dl_insert_first(&headr1, &tailr1, carry);
			else
				dl_insert_first(&headr2, &tailr2, carry);
			carry = 0;
		}

		if (temp2->next != NULL)                // If more digits left in operand2
		{
			addition(&headr1, &tailr1, &headr2, &tailr2, headR, tailR);  // Add intermediate products

			dl_delete_list(&headr1, &tailr1);    // Clear previous row
			dl_delete_list(&headr2, &tailr2);    // Clear current row
			headr1 = *headR;                     // Store result into headr1 for next iteration
			tailr1 = *tailR;
			*headR = NULL;                       // Reset final result holders
			*tailR = NULL;
		}

		temp2 = temp2->prev;                    // Move to next digit of operand2
		count++;                                // Increase shift count for next row
	}

	*headR = headr1;                            // Set final result head
	*tailR = tailr1;                            // Set final result tail

	if (carry != 0)                             // Add leftover carry if any
	{
		dl_insert_first(headR, tailR, carry);
		carry = 0;
	}
}
