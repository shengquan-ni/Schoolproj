/*
	ICS 51. Lab #3

	IMPORTATNT NOTES:

	- Noramally, the compiler adds the prologue/epilogue code for the callee. However, when the 
	__declspec(naked) attribute is used, it is the programmer's responsibility to write the 
	prologue/epilogue code. In this lab you need to write prologue/epilogue code sections only 
	for the functions that have been declared with the naked attribute, namely:

	   + findMinIndex
	   + recFactorial
	   + performOperation
	   + fibonacci

	- You cannot define any local variable in the C code. If you need additional variables in your
	assembly code, you have to allocate space for them in the prologue of the function. 

	- You are not allowed to change anything in this file except for adding your assembly code 
    between the lines marked "BEGIN YOUR CODE HERE" and "END YOUR CODE HERE".

	- Remember to fill in your name, student ID below.

	- ONLY submit the lab3.c file for grading.

*/

char *yourName = "Shengquan Ni";
char *yourStudentID = "46564157";

/***********************************************************************************************

	PART 1: Selection Sort

	Selection sort is an in-place comparison sort algorithm that works by dividing the input list 
	into two parts: the sublist of items already sorted, which is built up from left to right of 
	the list, and the sublist of items remaining to be sorted that occupy the rest of the list. 
	Initially, the sorted sublist is empty and the unsorted sublist is the entire input list. 
	The algorithm proceeds by finding the smallest element in the unsorted sublist, exchanging it 
	with the leftmost unsorted element (putting it in sorted order), and moving the sublist 
	boundaries one element to the right. To learn more, read: 
	https://en.wikipedia.org/wiki/Selection_sort#Example

	Our implementation here uses a function called "findMinIndex" to find the index of smallest
	element between ith index and jth index of the array. The function "selectionSort" uses
	this function to find the smallest number and exchanges it with the leftmost unsorted element
	in each iteration. You need to implement the behavior of both functions in x86 assembly.

************************************************************************************************/

__declspec(naked) 
int findMinIndex (int integer_array[], int i, int j)
{

// C code to be converted to x86 assembly
/*
    int iMin = i;
    // test against elements after i and before j to find the smallest 
    for ( i ; i < j; i++) {
        // if this element is less, then it is the new minimum   
        if (integer_array[i] < integer_array[iMin]) {
            // found new minimum; remember its index 
            iMin = i;
        }
    }

    return iMin;
*/

	__asm{
			// BEGIN YOUR CODE HERE
		    push ebp
			mov ebp,esp
			push ebx
			push ecx
			push edx
			push esi
			mov esi, integer_array
			mov eax,i
			mov ebx,j
			mov ecx,i
			L1:
			inc ecx
			cmp ecx,ebx
			jge END
			mov edx, dword ptr[esi + ecx * 4]
			cmp dword ptr[esi + eax * 4],edx
			jl L1
			mov eax,ecx
			jmp L1
			END:
			// END YOUR CODE HERE
			pop esi
			pop edx
			pop ecx
			pop ebx
			mov esp,ebp
			pop ebp
			ret 
	}

}

void selectionSort (int integer_array[], int array_size)
{

// C code to be converted to x86 assembly
/*  
	int j;
	int iMin;
	int temp;

	// advance the position through the entire array //
	// (could do j < n-1 because single element is also min element) //
	for (j = 0; j < array_size-1; j++) {

		// find the index of min element in the unsorted a[j .. n-1] //
 		iMin = findMinIndex (integer_array, j, array_size);
 
		if(iMin != j) { // swap values
			temp = integer_array[iMin];
			integer_array[iMin] = integer_array [j];
			integer_array[j] = temp;	
		}
	}
*/

	__asm{
			// BEGIN YOUR CODE HERE
			push eax
			push ebx
			push ecx
			push edx
			push esi
			push edi
			mov edi, integer_array
			mov ecx, 0
			mov ebx,array_size
			L1:
			cmp ecx, ebx
			jge END
			push ebx
			push ecx
			push integer_array
			call findMinIndex
			add esp,12
			cmp eax, ecx
			je L2
			mov edx, dword ptr[edi + eax * 4]
			mov esi, edx
			mov edx, dword ptr[edi + ecx * 4]
			mov dword ptr[edi + eax * 4], edx
			mov edx, esi
			mov dword ptr[edi + ecx * 4], edx
			L2:
			inc ecx
			jmp L1
			END:
			pop edi
			pop esi
			pop edx
			pop ecx
			pop ebx
			pop eax
			// END YOUR CODE HERE

	}

}

/***********************************************************************************************

    PART 2: Recursive Factorial

	Implement two functions that calculates the factorial of an integer not greater than 12.

	The 1st function, factorial (unsigned int input, unsigned int *output), is the non 
	recursive wrapper function which takes the input, sets up the stack, calls the recursive 
	function and finally puts the result in the location pointed to by the pointer argument called
    output.

	The 2nd function, recFactorial(unsigned int n), is the recursive function that actually 
	calculates the factorial.

	Given an unsigned integer number n,we define FACTORIAL(n) as:

        FACTORIAL(n) =  1                   ,    if n = 0 or n = 1
                        n * FACTORIAL(n-1)  ,    if n > 1
		
	Tip:
		
	- You need to use IMUL instruction to multiply unsigned integers. Learn how to use it:
	http://www.cs.virginia.edu/~evans/cs216/guides/x86.html#instructions

************************************************************************************************/

__declspec(naked) 
unsigned int recFactorial (unsigned int n)
{

// C code to be converted to x86 assembly
/*
	if (n<=1) 
		return 1;
	else 
		return n * recFactorial(n-1); 
*/

	__asm{
			// BEGIN YOUR CODE HERE
			push ebp
			mov ebp,esp
			push ecx
			mov ebx,1
			mov ecx,n
			cmp ecx,ebx
			jle L1
			dec ecx
			push ecx
			call recFactorial
			pop ecx
			imul eax,n
			jmp END
			L1:
			mov eax,1
			// END YOUR CODE HERE
			END:
			pop ecx
			mov esp,ebp
			pop ebp
			ret
	}

}

void factorial (unsigned int input, unsigned int *output)
{

// C code to be converted to x86 assembly
/*
	*output = recFactorial (input);
*/

	__asm{
			// BEGIN YOUR CODE HERE
			mov ebx,input
			mov ecx,output
			push ebx
			call recFactorial
			pop ebx
			mov dword ptr[ecx],eax
			// END YOUR CODE HERE
	}

}

/***********************************************************************************************

    PART 3: Vector Operation

	The vectorOperations function gets as parameters 4 arrays of the same length and
	the number of elements in those arrays. 

	For each pair of elements in first_array and second_array, it calls performOperation
	and stores the returned result in the same index of output_array.

	output_array[index] = performOperation(operation_array[index], first_array[index], second_array[index]).

	You also need to implement the body of performOperation function according to the provided
	C code.
  
************************************************************************************************/

__declspec(naked) 
int performOperation (int operation, int first, int second)
{

// C code to be converted to x86 assembly
/*
	if (operation==0) 
		return first + second;
	else if (operation==1)
		return first - second;
	else if (operation==2)
		return (first > second)? first : second;
	else if (operation==3)
		return (first < second)? first : second;
	else
		return first;
*/

	__asm {
			// BEGIN YOUR CODE HERE
			push ebp
			mov ebp, esp
			push ebx
			push ecx
			push edx
			mov eax,0
			mov ebx,first
			mov ecx,second
			mov edx,operation
			cmp edx,eax
			jne L1
			mov eax,ebx
			add eax,ecx
			jmp END
			L1:
			inc eax
			cmp edx,eax
			jne L2
			mov eax,ebx
			sub eax,ecx
			jmp END
			L2:
			inc eax
			cmp edx,eax
			jne L3
			cmp ebx,ecx
			jg L4
			mov eax,ecx
			jmp END
			L4:
			mov eax,ebx
			jmp END
			L3:
			inc eax
			cmp edx,eax
			jne L6
			cmp ebx,ecx
			jl L6
			mov eax,ecx
			jmp END
			L6:
			mov eax,ebx
			END:
			pop edx
			pop ecx
			pop ebx
			mov esp,ebp
			pop ebp
			// END YOUR CODE HERE
			ret
	}
  
}

void vectorOperations (int number_of_elements, int *first_array, int *second_array, 
					   int *operation_array, int *output_array)
{
// C code to be converted to x86 assembly
/*
	int i;
	for (i=0; i<number_of_elements; i++)
	{
		output_array[i] = performOperation(operation_array[i], first_array[i], second_array[i]);
	}
*/

	__asm {
			// BEGIN YOUR CODE HERE
			mov eax,0
			mov ecx,number_of_elements
			mov ebx,first_array
			mov edx,second_array
			mov esi,operation_array
			mov edi,output_array
			L1:
			cmp eax,ecx
			jge END
			push ecx
			push eax
			mov ecx,eax
			push dword ptr[edx+eax*4]
			push dword ptr[ebx+eax*4]
			push dword ptr[esi+eax*4]
			call performOperation
			add esp,12
			mov dword ptr[edi+ecx*4],eax
			pop eax
			pop ecx
			inc eax
			jmp L1
			END:
			// END YOUR CODE HERE
	}
}

/***********************************************************************************************

    PART 4: Change Letter Case

	You are given an array of characters (a string) that may contain numbers, upper and	lower case 
    letters, punctuations symbols, etc. Implement a function to convert all uppercase letters to 
    lowercase and vice versa. 
    For example "ThisIsTheFinalLabOf51" should be converted to "tHISiStHEfINALlABoF51". 
	The function has the following argument: An array of charaters and the size of the array. The 
	array should be changed in place. There is no explicit output for this function.

	Tips:

	- Note that each element of the arrays is a char (1 byte). You can NOT use a 32-bit register 
	to read/write from/to a memory location. Instead you should use the 8-bit version of the x86
	general-purpose registers. 
	More info: http://www.cs.virginia.edu/~evans/cs216/guides/x86.html#registers

	- The link to the ascii codes is here: http://www.asciitable.com/

************************************************************************************************/

void changeCase (char char_array[], int array_size ) {

	__asm{
			// BEGIN YOUR CODE HERE
			mov eax,0
			mov bl,64
			mov bh,90
			mov cl,96
			mov ch,122
			mov edi,array_size
			mov esi,char_array
			L1:
			cmp eax,edi
			jge END
			mov dl, byte ptr[esi + eax]
			cmp bl,dl
			jge PASS
			cmp bh,dl
			jl L2
			add byte ptr[esi + eax], 32
			jmp PASS
			L2:
			cmp bl, dl
			jge PASS
			cmp ch, dl
			jl PASS
			sub byte ptr[esi + eax], 32
			PASS:
			inc eax
			jmp L1
			END:
			// END YOUR CODE HERE
	}
}

/***********************************************************************************************

    PART 5: Fibonacci

	Implement a recursive function in assembly which returns the Nth number in the fibbonaci
	series (1, 1, 2, 3, 5, 8, ...).

************************************************************************************************/

__declspec(naked) 
unsigned int fibonacci (unsigned int n) {

// C code to be converted to x86 assembly
/*
	if (n < 2) 
		return 1;
	else 
		return fibonacci(n - 1) + fibonacci(n - 2);
*/

	__asm{
			// BEGIN YOUR CODE HERE
			push ebp
			mov ebp,esp
			mov ecx,2
			mov ebx,n
			cmp ebx,ecx
			jl L1
			dec ebx
			push ebx
			call fibonacci
			pop ebx
			mov edx,eax
			push edx
			dec ebx
			push ebx
			call fibonacci
			pop ebx
			pop edx
			add eax,edx
			mov esp,ebp
			pop ebp
			ret
			L1:
			mov eax,1
			mov esp,ebp
			pop ebp
			// END YOUR CODE HERE
			ret
	}
}