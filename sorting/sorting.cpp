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

<<<<<<< HEAD
// Initialize the arrays which need to be sorted and calculate the number of elements in the array "divide the total size of the array by the size of the array element"
long long unsorted[100000];
long long copyUnsorted[100000];
int length = sizeof(unsorted) / sizeof(long long);
=======
// Initialize parameters
int const length = 5000;
bool timeSeed = false;

// Initialize the arrays which need to be sorted
long long unsorted[length];
long long copyUnsorted[length];
>>>>>>> origin/master

int patsort(long long values[], int length);
int patsortplus(long long values[], int length);
int quickSort(long long values[], int left, int right);

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
	for (int i{0}; i < 4; i++)
	{
		std::copy(unsorted, unsorted + length, copyUnsorted);
<<<<<<< HEAD

		// Optional printing of the generated array before sorting
		//printf("before sorting the list is: \n");
		//for (int n{0}; n < length; n++)
		//{
		//	printf("%d ", copyUnsorted[n]);
		//}
=======
>>>>>>> origin/master
		
		high_resolution_clock::time_point t1 = high_resolution_clock::now();
		switch (i)
		{
			// Error. Unreachable declaration.
			cout << "\n\nError unreachable declaration in switch" << endl;
			break;
		case 0:
			//qsort
<<<<<<< HEAD
			cout << "quicksort clean:" << endl;
			quickSort(copyUnsorted,0,length-1);
			//gnuqsort(copyUnsorted, length, sizeof(int), cmpfunc);
			break;
		case 1:
			//Patience sort
			cout << "Patience sort:" << endl;
 			//patsort(copyUnsorted, length);
			//patsortplus(copyUnsorted, length);
			break;
		case 2:
			//Patience+ sort
			cout << "Patient+ sort:" << endl;
			//patsortplus(copyUnsorted, length);
			break;
		case 3:
			//P3 sort
			cout << "Qsort Microsoft:" << endl;
			qsort(copyUnsorted, length, sizeof(long long), cmpfunc);
=======
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

>>>>>>> origin/master
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

