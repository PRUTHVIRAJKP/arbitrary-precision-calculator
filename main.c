/*
NAME : PRUTHVIRAJ K P

DATA : 7/7/25

Project Description:
The Arbitrary Precision Calculator (APC) is a command-line based calculator implemented in C language to perform arithmetic operations (+, -, x, /) 
on very large numbers that exceed the standard data type limits in C (like int, long, etc.). It handles such numbers by storing each digit as a node in
 a doubly linked list, enabling operations without any size constraints.


*/


#include "apc.h"

int main(int argc, char *argv[])
{
	// Initialize all list pointers for operands and result
	Dlist *head1 = NULL, *tail1 = NULL;
	Dlist *head2 = NULL, *tail2 = NULL;
	Dlist *headR = NULL, *tailR = NULL;

	// Validate number of command-line arguments
	if (argc != 4)
	{
		printf("Error: Invalid number of arguments.\n");
		printf("Usage: ./a.out <operand1> <operator> <operand2>\n");
		exit(1);
	}

	// Validate operand1 contains only digits
	char *str1 = argv[1];
	int i = 0;
	while (str1[i])
	{
		if (str1[i] < '0' || str1[i] > '9')
		{
			printf("Error! : operaotr 1 should only has number, other characters are invalid\n");
			exit(1);
		}
		i++;
	}

	// Validate operand2 contains only digits
	char *str2 = argv[3];
	i = 0;
	while (str2[i])
	{
		if (str2[i] < '0' || str2[i] > '9') // Fixed: should check str2[i], not str1[i]
		{
			printf("Error! : operaotr 2  should only has number, other characters are invalid\n");
			exit(1);
		}
		i++;
	}

	// Extract operator character
	char operator = argv[2][0];

	switch (operator)
	{
	case '+':
	{
		// Convert strings to digit list for addition
		digit_to_list(&head1, &tail1, &head2, &tail2, argv);
		// Perform addition
		addition(&head1, &tail1, &head2, &tail2, &headR, &tailR);
		// Print result
		print_list(headR);
	}
	break;

	case '-':
	{
		int flag = 0;

		// Compare lengths to decide operand order
		if (strlen(argv[1]) < strlen(argv[3]))
		{
			digit_to_list(&head2, &tail2, &head1, &tail1, argv);
			flag = 1;
			//printf(" inside the string lenght comparision\n");
		}
		else if (strlen(argv[1]) == strlen(argv[3]))
		{
			// Compare lexicographically if lengths are equal
			if (strcmp((argv[1]), (argv[3])) < 0)
			{
				//printf(" inside the strcmp true comparision\n");
				flag = 1;
				digit_to_list(&head2, &tail2, &head1, &tail1, argv);
			}
			else
				digit_to_list(&head1, &tail1, &head2, &tail2, argv);
		}
		else
		{
			digit_to_list(&head1, &tail1, &head2, &tail2, argv);
		}

		// Perform subtraction
		subtraction(&head1, &tail1, &head2, &tail2, &headR, &tailR);

		// Negate result if operand1 < operand2
		if (flag == 1)
		{
			Dlist *my = headR;
			while (my)
			{
				if (my->data != 0)
				{
					my->data = -(my->data); // Apply minus sign to the first non-zero digit
					break;
				}
				else
				{
					dl_delete_first(&headR, &tailR); // Remove leading zeros
				}
				my = my->next;
			}
		}
		print_list(headR);
	}
	break;

	case 'x':
	{
		// Convert to list for multiplication
		digit_to_list(&head1, &tail1, &head2, &tail2, argv);
		// Perform multiplication
		multiplication(&head1, &tail1, &head2, &tail2, &headR, &tailR);
		// Print result
		print_list(headR);
	}
	break;

	case '/':
		// Convert to list for division
		digit_to_list(&head1, &tail1, &head2, &tail2, argv);
		// Perform division
		division(&head1, &tail1, &head2, &tail2, &headR, &tailR);
		break;

	default:
		// Handle invalid operator
		printf("Invalid Input:-( Try again...\n");
	}

	return 0;
}
