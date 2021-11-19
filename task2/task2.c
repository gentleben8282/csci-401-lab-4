/* CSCI 401: Lab #4: Intro to Function Pointers
 * Programmer (Student ID): Ben Corriette (@02956064)
 * Last modified date: 11/18/2021
 * 
 * Summary: Create a program that performs a mathematical operation
 * on two numbers in a file using a single character from user input
 * via a function pointer.
 * 
 * References: Quick Sort and Function Pointers Lab Handout
 *             Linux Programmer's Manual: scanf(), atoi(), exit()           
 *             https://stackoverflow.com/questions/252748/how-can-i-use-an-array-of-function-pointers
 */

#include <stdio.h>
#include <stdlib.h>

const int a = 10;
const int b = 5;

typedef int (*comparer) (int a, int b);

int add (int a, int b) { printf ("Adding 'a' and 'b'\n"); return a + b; }
int subtract (int a, int b) { printf ("Subtracting 'b' from 'a'\n"); return a - b; }
int multiply (int a, int b) { printf ("Multiplying 'a' and 'b'\n"); return a * b; }
int divide (int a, int b) { printf ("Dividing 'a' by 'b'\n"); return a / b; }
int exit_program (int a, int b) { 
  printf ("Exiting program...\n"); 
  exit(EXIT_SUCCESS);
	return EXIT_SUCCESS;
}
int make_calculation(int a, int b, comparer cmp) {
  return cmp(a, b);
}
int (*calculation_functions[5]) (int x, int y);

int main (void)
{
	char operation_selected;
  int calculated_number;
	
	// Initialize function pointer array
	calculation_functions[0] = add;
	calculation_functions[1] = subtract;
	calculation_functions[2] = multiply;
	calculation_functions[3] = divide;
	calculation_functions[4] = exit_program;
	
	// Print instructions to terminal
  printf("Operand 'a' : %d | Operand 'b' : %d\n", a, b);
  printf("Please specify the operation to perform:\n");
  printf("(0: add | 1: subtract | 2: multiply | 3: divide | 4: exit):\n");
  
	// Store the user's input and convert to an integer
	scanf("%c", &operation_selected);
	int function_index = atoi(&operation_selected);
	
	// Make the calculation and print the result
	calculated_number = make_calculation(a, b, *calculation_functions[function_index]);
	printf("x = %d\n", calculated_number);
  
	return EXIT_SUCCESS;
}