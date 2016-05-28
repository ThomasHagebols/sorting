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

// Initialize parameters
int const length = 5000;
bool timeSeed = false;

// Initialize the arrays which need to be sorted
long long unsorted[length];
long long copyUnsorted[length];

int patsort(long long values[], int length);
int patsortplus(long long values[], int length);
// int patsortplus(int values[], int length);

//typedef int(*__compar_d_fn_t) (const void *, const void *, void *);
//void _quicksort(void *const pbase, size_t total_elems, size_t size, __compar_d_fn_t cmp, void *arg);

int cmpfunc(const void * a, const void * b)
{
	return (*(long long*)a - *(long long*)b);
}

int main()
{
	// Initializa random number generator seed (time) and n
	if (timeSeed == true)
		std::srand(std::time(0));
	else
		std::srand(1);
	
	// Fill array with random variables
	for (int n{0}; n < length; n++)
	{
		unsorted[n] = std::rand();
	}

	printf("Number of values to be sorted: %d \n", length);
	printf("Using time as seed value: %s \n", timeSeed ? "true" : "false");

	// Optional printing of the generated array before sorting
	//printf("before sorting the list is: \n");
	//for (int n{0}; n < length; n++)
	//{
	//	printf("%d ", copyUnsorted[n]);
	//}

	// Perform different sorting algorithms and time the runtime
	for (int i{0}; i < 3; i++)
	{
		std::copy(unsorted, unsorted + length, copyUnsorted);
		
		high_resolution_clock::time_point t1 = high_resolution_clock::now();
		switch (i)
		{
			// Error. Unreachable declaration.
			cout << "\n\nError unreachable declaration in switch" << endl;
			break;
		case 0:
			//qsort
			cout << "\n\nqsort:" << endl;
			qsort(copyUnsorted, length, sizeof(long long), cmpfunc);
			break;
		case 1:
			//Patience sort
			cout << "\n\nPatience sort:" << endl;
 			patsort(copyUnsorted, length);
			break;
		case 2:
			//Patience+ sort
			cout << "\n\nPatient+ sort:" << endl;
			patsortplus(copyUnsorted, length);
			break;
		case 3:
			//P3 sort
			cout << "\n\nP3 sort:" << endl;

			break;
		case 4:
			//TimSort
			cout << "\n\nTimsort:" << endl;
			break;
		default:
			// i undefined
			cout << "\n\nSwitch out of bound:" << endl;
			break;
		}
		high_resolution_clock::time_point t2 = high_resolution_clock::now();

		//Calculate and print execution time
		auto duration = duration_cast<microseconds>(t2 - t1).count();
		printf("\nTime needed for sorting: %d microseconds \n", duration);

		// Optional printing of the array after sorting
		//printf("After sorting the list is: \n");
		//for (int n{ 0 }; n < length; n++)
		//{
		//	printf("%d ", copyUnsorted[n]);
		//}
	}

    return 0;
}

