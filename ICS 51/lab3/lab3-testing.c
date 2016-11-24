#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>


// These functions should be implemented in lab3.c
extern void selectionSort( int integer_array[], int array_size );
extern void factorial(unsigned int input, unsigned int *output);
extern void vectorOperations (int number_of_elements, int *first_array, int *second_array, int *operation_array, int *output_array);
extern void changeCase(char char_array[], int array_size);
extern unsigned fibonacci(unsigned n);

void test_selectionSort();
void test_factorial ();
void test_vectorOperations();
void test_changeCase();
void test_fibonacci ();

extern char *yourName;
extern char *yourStudentID;

unsigned int num_of_tests = 0;
unsigned int num_of_tests_passed = 0;

int main(void)
{
	 // Once you are done implementing the required functions, enable the testcases		  
	#define TEST_PART1 1
	#define TEST_PART2 1
	#define TEST_PART3 1
	#define TEST_PART4 1 
	#define TEST_PART5 1 

	printf ("ICS 51, Lab 3 \nName: %s\nStudent ID: %s\n\n",yourName, yourStudentID);

	#if TEST_PART1
		printf("====================== PART1 ======================\n");
		test_selectionSort();
		printf("\n");
	#endif


	#if TEST_PART2
		printf("====================== PART2 ======================\n");
		test_factorial();
		printf("\n");
	#endif

	
	#if TEST_PART3
		printf("====================== PART3 ======================\n");
		test_vectorOperations();
		printf("\n");
	#endif


	#if TEST_PART4
		printf("====================== PART4 ======================\n");
		test_changeCase();
		printf("\n");
	#endif

	#if TEST_PART5
		printf("====================== PART5 ======================\n");
		test_fibonacci();
		printf("\n");
	#endif

		printf("===================== SUMMARY =====================\n");

	if (num_of_tests_passed == 0)
		printf( "All %d tests failed.\n\n" , num_of_tests);
	else if (num_of_tests == num_of_tests_passed)
		printf( "All %d tests passed.\n\n" , num_of_tests);
	else
		printf( "%d out of %d tests passed.\n\n" , num_of_tests_passed, num_of_tests);
		
	getchar();
	return 0;
}


int findMinIndex_c (int integer_array[], int i, int j)
{
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
}

void selectionSort_c(int integer_array[], int array_size)
{
	int j;
	int iMin;
	int temp;

	// advance the position through the entire array //
	// (could do j < n-1 because single element is also min element) //
	for (j = 0; j < array_size-1; j++) {

		// find the index of min element in the unsorted a[j .. n-1] //
 		iMin = findMinIndex_c (integer_array, j, array_size);
 
		if(iMin != j) { // swap values
			temp = integer_array[iMin];
			integer_array[iMin] = integer_array [j];
			integer_array[j] = temp;	
		}
	}
}

void test_selectionSort()
{
	int arrayOfNumbers1[ 15 ] = {4, 5, 1, 222, 5, 5, 33, 11, -4, 12, -333, 10, -28349, 74, 323232};
	int arrayOfNumbers2[ 15 ] = {+32131, +432, +232, +4, -1, -4, -5, -7, -8, -8, -9, -100000, -200000, -300000, -9999999};
	int arrayOfNumbers3[ 15 ] = {4, -5, 1, -222, 5, -5, 33, -11, -4, 12, -333, 10, +28349, 74, -323232};
	int arrayOfNumbers4[ 1  ] = {100};
	int arrayOfNumbers5[ 2  ] = {-10, -100};
	int *arrayOfNumbers6 = NULL;

	int expected_arrayOfNumbers1[ 15 ] = {4, 5, 1, 222, 5, 5, 33, 11, -4, 12, -333, 10, -28349, 74, 323232};
	int expected_arrayOfNumbers2[ 15 ] = {+32131, +432, +232, +4, -1, -4, -5, -7, -8, -8, -9, -100000, -200000, -300000, -9999999};
	int expected_arrayOfNumbers3[ 15 ] = {4, -5, 1, -222, 5, -5, 33, -11, -4, 12, -333, 10, +28349, 74, -323232};
	int expected_arrayOfNumbers4[ 1  ] = {100};
	int expected_arrayOfNumbers5[ 2  ] = {-100, -10};
	int *expected_arrayOfNumbers6 = NULL;
		
	int i;
	int err = 0;

	int num_elements = 15;
	printf("Original array was:\n");

	for(i=0; i<num_elements; i++){
		printf("%d ", arrayOfNumbers1[i]);
	}

	selectionSort(arrayOfNumbers1, num_elements);
	selectionSort_c(expected_arrayOfNumbers1, num_elements);

	printf("\nSorted array should be:\n");
	for(i=0; i<num_elements; i++){
		printf("%d ", expected_arrayOfNumbers1[i]);
	}

	err = 0;
	printf("\nYour sorted array is:\n");
	for(i=0; i<num_elements; i++){
		printf("%d ", arrayOfNumbers1[i]);
		if (arrayOfNumbers1[i] != expected_arrayOfNumbers1[i]){
			err = 1;
		}
	}

	num_of_tests++;
	if (!err){
		printf( "\nTest passed.\n" );
		num_of_tests_passed++;
	}
	else{
		printf( "\nTest failed.\n" );
	}

	printf("\n");

	printf("\nOriginal array was:\n");

	for(i=0; i<num_elements; i++){
		printf("%d ", arrayOfNumbers2[i]);
	}

	selectionSort(arrayOfNumbers2, num_elements);
	selectionSort_c(expected_arrayOfNumbers2, num_elements);

	printf("\nSorted array should be:\n");
	for(i=0; i<num_elements; i++){
		printf("%d ", expected_arrayOfNumbers2[i]);
	}

	err = 0;
	printf("\nYour sorted array is:\n");
	for(i=0; i<num_elements; i++){
		printf("%d ", arrayOfNumbers2[i]);
		if (arrayOfNumbers2[i] != expected_arrayOfNumbers2[i]){
			err = 1;
		}
	}

	num_of_tests++;
	if (!err){
		printf( "\nTest passed.\n" );
		num_of_tests_passed++;
	}
	else{
		printf( "\nTest failed.\n" );
	}

	printf("\n");
	
	printf("\nOriginal array was:\n");

	for(i=0; i<num_elements; i++){
		printf("%d ", arrayOfNumbers3[i]);
	}

	selectionSort(arrayOfNumbers3, num_elements);
	selectionSort_c(expected_arrayOfNumbers3, num_elements);

	printf("\nSorted array should be:\n");
	for(i=0; i<num_elements; i++){
		printf("%d ", expected_arrayOfNumbers3[i]);
	}

	err = 0;
	printf("\nYour sorted array is:\n");
	for(i=0; i<num_elements; i++){
		printf("%d ", arrayOfNumbers3[i]);
		if (arrayOfNumbers3[i] != expected_arrayOfNumbers3[i]){
			err = 1;
		}
	}

	num_of_tests++;
	if (!err){
		printf( "\nTest passed.\n" );
		num_of_tests_passed++;
	}
	else{
		printf( "\nTest failed.\n" );
	}

	printf("\n");
	
	num_elements = 1;
	printf("\nOriginal array was:\n");

	for(i=0; i<num_elements; i++){
		printf("%d ", arrayOfNumbers4[i]);
	}

	selectionSort(arrayOfNumbers4, num_elements);
	selectionSort_c(expected_arrayOfNumbers4, num_elements);

	printf("\nSorted array should be:\n");
	for(i=0; i<num_elements; i++){
		printf("%d ", expected_arrayOfNumbers4[i]);
	}

	err = 0;
	printf("\nYour sorted array is:\n");
	for(i=0; i<num_elements; i++){
		printf("%d ", arrayOfNumbers4[i]);
		if (arrayOfNumbers4[i] != expected_arrayOfNumbers4[i]){
			err = 1;
		}
	}

	num_of_tests++;
	if (!err){
		printf( "\nTest passed.\n" );
		num_of_tests_passed++;
	}
	else{
		printf( "\nTest failed.\n" );
	}

	printf("\n");
	
	num_elements = 2;
	printf("\nOriginal array was:\n");

	for(i=0; i<num_elements; i++){
		printf("%d ", arrayOfNumbers5[i]);
	}

	selectionSort(arrayOfNumbers5, num_elements);
	selectionSort_c(expected_arrayOfNumbers5, num_elements);

	printf("\nSorted array should be:\n");
	for(i=0; i<num_elements; i++){
		printf("%d ", expected_arrayOfNumbers5[i]);
	}

	err = 0;
	printf("\nYour sorted array is:\n");
	for(i=0; i<num_elements; i++){
		printf("%d ", arrayOfNumbers5[i]);
		if (arrayOfNumbers5[i] != expected_arrayOfNumbers5[i]){
			err = 1;
		}
	}

	num_of_tests++;
	if (!err){
		printf( "\nTest passed.\n" );
		num_of_tests_passed++;
	}
	else{
		printf( "\nTest failed.\n" );
	}

	printf("\n");
	
	num_elements = 0;
	printf("\nOriginal array is:\n");

	for(i=0; i<num_elements; i++){
		printf("%d ", arrayOfNumbers6[i]);
	}

	selectionSort(arrayOfNumbers6, num_elements);
	selectionSort_c(expected_arrayOfNumbers6, num_elements);

	printf("\nSorted array should be:\n");
	for(i=0; i<num_elements; i++){
		printf("%d ", expected_arrayOfNumbers6[i]);
	}

	err = 0;
	printf("\nYour sorted array is:\n");
	for(i=0; i<num_elements; i++){
		printf("%d ", arrayOfNumbers6[i]);
		if (arrayOfNumbers6[i] != expected_arrayOfNumbers6[i]){
			err = 1;
		}
	}

	num_of_tests++;
	if (!err){
		printf( "\nTest passed.\n" );
		num_of_tests_passed++;
	}
	else{
		printf( "\nTest failed.\n" );
	}

}

unsigned int factorial_c(unsigned int n)
{
	unsigned int c;
	unsigned int result = 1;
 
	for (c = 1; c <= n; c++)
	result = result * c;
 
	return result;
}

void test_factorial()
{
	int n = 12;
	unsigned int result = -1;
	int i;
	int err = 0;
	for (i=0;  i < n;  i++) {
		factorial(i, &result);
		if ( result != factorial_c(i) ) {
			err = 1;
			printf( "Test failed. Factorial(%d): expected %d, got %d\n" , i, factorial_c(i), result);
		}
	}

	num_of_tests++;
	if (!err){
		printf( "Test passed.\n" );
		num_of_tests_passed++;
	}
}

int performOperation_c (int operation, int first, int second)
{
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
}

void vectorOperations_c (int number_of_elements, int *first_array, int *second_array, 
                         int *operation_array, int *output_array)
{
	int i;
	for (i=0; i<number_of_elements; i++)
	{
		output_array[i] = performOperation_c(operation_array[i], first_array[i], second_array[i]);
	}
}

void test_vectorOperations()
{
	int err = 0;
	int i = 0;

	int number_of_elements = 10;
	int operation_array[] = {1, 2, 1, 4, 1, 2, 4, 3, 3, 0};
	int first_array[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 182 };
	int second_array[] = {-3, 14, 5674, 289, - 89, 234, 54, 234, 98, 71} ;
	int output_array[10];
	int expected_output_array[10];

	vectorOperations(number_of_elements, first_array, second_array, operation_array, output_array);
	vectorOperations_c(number_of_elements, first_array, second_array, operation_array, expected_output_array);

	for (i=0; i<number_of_elements; i++) {
		if (output_array[i] != expected_output_array[i]) {
			err = 1;
			printf( "Test failed at index %d: expected %d, got %d\n" , i, expected_output_array[i], output_array[i]);
		}
	}
	
	num_of_tests++;
	if (!err){
		printf( "Test passed.\n" );
		num_of_tests_passed++;
	}
}

void test_changeCase()
{
	int i = 0;

	char arrayOfLetters1[ 21 ] = {'T', 'h', 'i', 's', 'I', 's', 'T', 'h', 'e', 'F', 'i', 'n', 'a', 'l', 'L', 'a', 'b', 'O', 'f', '5', '1'};
	char arrayOfLetters2[ 35 ] = {'i', 'A', 'M', 'o', 'n', 'A', 's', 'e', 'a', 'f', 'o', 'o', 'd', 'D', 'I', 'E', 'T', '.', 'I', 's', 'e', 'e', 'F', 'O', 'O', 'D', 'a', 'n', 'd', 'I', 'e', 'a', 't', 'I', 'T'};
	char arrayOfLetters3[ 10 ] = {'1', '2', '3', '4', 'A', '5', '6', '7', '8', '9'};

	char expected_arrayOfLetters1[ 21 ] = {'t', 'H', 'I', 'S', 'i', 'S', 't', 'H', 'E', 'f', 'I', 'N', 'A', 'L', 'l', 'A', 'B', 'o', 'F', '5', '1'};
	char expected_arrayOfLetters2[ 35 ] = {'I', 'a', 'm', 'O', 'N', 'a', 'S', 'E', 'A', 'F', 'O', 'O', 'D', 'd', 'i', 'e', 't', '.', 'i', 'S', 'E', 'E', 'f', 'o', 'o', 'd', 'A', 'N', 'D', 'i', 'E', 'A', 'T', 'i', 't'};
	char expected_arrayOfLetters3[ 10 ] = {'1', '2', '3', '4', 'a', '5', '6', '7', '8', '9'};

	for(i=0; i<21; i++){
		printf("%c", arrayOfLetters1[i]);
	}
	printf(" ==> ");

	changeCase(arrayOfLetters1, 21);

	for(i=0; i<21; i++){
		printf("%c", arrayOfLetters1[i]);
	}

	num_of_tests++;
	if (!memcmp(arrayOfLetters1, expected_arrayOfLetters1, 21)){
		printf( "\nTest passed.\n" );
		num_of_tests_passed++;
	}
	else{
		printf( "\nTest failed.\n" );
	}


	printf("\n");
	for(i=0; i<35; i++){
		printf("%c", arrayOfLetters2[i]);
	}
	printf(" ==> ");

	changeCase(arrayOfLetters2, 35);

	for(i=0; i<35; i++){
		printf("%c", arrayOfLetters2[i]);
	}

	num_of_tests++;
	if (!memcmp(arrayOfLetters2, expected_arrayOfLetters2, 35)){
		printf( "\nTest passed.\n" );
		num_of_tests_passed++;
	}
	else
		printf( "\nTest failed.\n" );



	printf("\n");
	for(i=0; i<10; i++){
		printf("%c", arrayOfLetters3[i]);
	}
	printf(" ==> ");

	changeCase(arrayOfLetters3, 10);

	for(i=0; i<10; i++){
		printf("%c", arrayOfLetters3[i]);
	}

	num_of_tests++;
	if (!memcmp(arrayOfLetters3, expected_arrayOfLetters3, 10)){
		printf("\nTest passed.\n");
		num_of_tests_passed++;
	}
	else{
		printf("\nTest failed.\n");
	}
}

unsigned int fibonacci_c(unsigned int n)
{
	if ( n < 2 )
		return 1;
	else
		return ( fibonacci_c(n-1) + fibonacci_c(n-2) );
} 

void test_fibonacci()
{
	unsigned n = 30;
	unsigned i;
	int err = 0;
	for (i=0;  i < n;  i++) {
		if ( fibonacci(i) != fibonacci_c(i) ) {
			err = 1;
			printf( "Test failed. Fibonacci(%d): expected %d, got %d\n" , i, fibonacci_c(i), fibonacci(i));
		}
	}

	num_of_tests++;
	if (!err){
		printf( "Test passed.\n"  );
		num_of_tests_passed++;
	}
}