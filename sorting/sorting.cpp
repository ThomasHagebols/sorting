// sorting.cpp : Defines the entry point for the console application.
// An array with n random elements will be created and sorted using different algorithms
// The runtime of the different algorithms will be timed

#include "stdafx.h"
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

// TODO Check if char is permitted in C++
//gnuqsort(char *base_ptr, int total_elems, int size, int(*cmp)());

// Initialize the arrays which need to be sorted and calculate the number of elements in the array "divide the total size of the array by the size of the array element"
int unsorted[10];
int copyUnsorted[10];
int length = sizeof(unsorted) / sizeof(int);

int cmpfunc(const void * a, const void * b)
{
	return (*(int*)a - *(int*)b);
}

// int gnuqsort(int *base_ptr, int *total_elems, int *size, int(*cmp)());

int main()
{
	// Initializa random number generator seed (time) and n
	std::srand(std::time(0));
	int n;
	int i;
	
	// Fill array with random variables
	for (n = 0; n < length; n++)
	{
		unsorted[n] = std::rand();
	}

	// Perform different sorting algorithms and time the runtime
	for (i = 0; i < 2; i++)
	{
		std::copy(unsorted, unsorted + length, copyUnsorted);

		// Optional printing of the generated array before sorting
		printf("before sorting the list is: \n");
		for (n = 0; n < length; n++)
		{
			printf("%d ", copyUnsorted[n]);
		}
		
		high_resolution_clock::time_point t1 = high_resolution_clock::now();
		switch (i)
		{
			// Error. Unreachable declaration.
			cout << "Error unreachable declaration in switch" << endl;
			break;
		case 0:
			//qsort
			qsort(copyUnsorted, length, sizeof(int), cmpfunc);
			//gnuqsort(copyUnsorted, length, sizeof(int), cmpfunc);
			break;
		case 1:
			//Patience sort
			qsort(copyUnsorted, length, sizeof(int), cmpfunc);
			break;
		case 2:
			//Patience+ sort

			break;
		case 3:
			//P3 sort
			break;
		case 4:
			//TimSort
			break;
		default:
			// i undefined
			cout << "Switch out of bound" << endl;
			break;
		}
		high_resolution_clock::time_point t2 = high_resolution_clock::now();

		// Optional printing of the array after sorting
		printf("\nAfter sorting the list is: \n");
		for (n = 0; n < length; n++)
		{
			printf("%d ", copyUnsorted[n]);
		}

		//Calculate and print execution time
		auto duration = duration_cast<microseconds>(t2 - t1).count();
		printf("\nTime needed for sorting: %d microseconds ", duration);
	}

    return 0;
}

