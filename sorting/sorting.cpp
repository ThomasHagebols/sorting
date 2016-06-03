// sorting.cpp : Defines the entry point for the console application.
// Random and partially sorted arrays will be created and sorted using different algorithms
// The runtime of the different algorithms will be timed

#include "stdafx.h"
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <chrono>
#include <random>
#include <list>

using namespace std;
using namespace std::chrono;


// TODO Check if char is permitted in C++
//gnuqsort(char *base_ptr, int total_elems, int size, int(*cmp)());

// Initialize parameters
const int length = 100;
int const disorder = 10;
float const percentage = 0.10;
bool const timeSeed = false;

// Initialize the arrays which need to be sorted
long long unsortedRandom[length];
long long UnsortedSemi[length];
long long unsortedIncreasing[length];
long long valuesCopy[length];

int patsort(long long values[], const int length);
int patsortplus(long long values[], const int length);
int pThreeSort(long long values[], const int length);
//int UPingPongMerge(vector<list<long long>> runs, vector<int> runSize);

int compare_doubles(const void *a, const void *b)
{
	const long long *da = (const long long *)a;
	const long long *db = (const long long *)b;

	return (*da > *db) - (*da < *db);
}

//#define __const const;
////#define __COMPAR_FN_T;
//typedef int(*__compar_fn_t) (const void *, const void *);
//typedef __compar_fn_t comparison_fn_t;
//typedef int(*__compar_d_fn_t) (const void *, const void *);
//void _quicksort(void *const pbase, size_t total_elems, size_t size, __compar_d_fn_t cmp);

int cmpfunc(const void * a, const void * b)
{
	return (*(long long*)a - *(long long*)b);
}

int int_cmp(const void *a, const void *b)
{
	const int *ia = (const int *)a; // casting pointer types 
	const int *ib = (const int *)b;
	return *ia - *ib;
	/* integer comparison: returns negative if b > a
	and positive if a > b */
}

int addNoise(long long values[], int const size)
{
	// Random number generator for noise
	std::default_random_engine generator;
	std::normal_distribution<double> distribution(0, disorder);
	
	for (int n{ 0 }; n < size; n++)
	{
		float v1 = ((double)rand() / (RAND_MAX));

		if (v1 <= percentage)
			values[n] = values[n] + distribution(generator);
	}

	return 0;
}

int genData()
{
	// Initializa random number generator seed (time) and n
	if (timeSeed == true)
		std::srand(std::time(0));
	else
		std::srand(1);

	// Fill array with random variables
	for (int n{ 0 }; n < length; n++)
	{
		unsortedRandom[n] = std::rand();
	}

	// Copy unsortedRandom and sort it to get a sorted list with some randomness
	// in the interval between elements (multiple elements can be the same)
	std::copy(unsortedRandom, unsortedRandom + length, UnsortedSemi);
	qsort(UnsortedSemi, length, sizeof(long long), cmpfunc);

	// Fill array with increasing elements
	for (int n{ 0 }; n < length; n++)
	{
		unsortedIncreasing[n] = n;
	}

	// add noise
	addNoise(unsortedRandom, length);
	addNoise(unsortedIncreasing, length);

	return 0;
}

int doSorts(long long values[], const int length)
{
	// Optional printing of the generated array before sorting
	//printf("before sorting the list is: \n");
	//for (int n{0}; n < length; n++)
	//{
	//	printf("%d ", values[n]);
	//}

	// Perform different sorting algorithms and time the runtime
	for (int i{ 0 }; i < 4; i++)
	{
		std::copy(values, values + length, valuesCopy);

		high_resolution_clock::time_point t1 = high_resolution_clock::now();
		switch (i)
		{
			// Error. Unreachable declaration.
			cout << "\n\nError unreachable declaration in switch" << endl;
			break;
		case 0:
			//qsort
			cout << "\nqsort:" << endl;
			qsort(valuesCopy, length, sizeof(long long), cmpfunc);
			/*_quicksort(copyUnsortedRandom, length, sizeof(long long), compare_doubles);*/
			break;
		case 1:
			//Patience sort
			cout << "\n\nPatience sort:" << endl;
			patsort(valuesCopy, length);
			break;
		case 2:
			//Patience+ sort
			cout << "\n\nPatient+ sort:" << endl;
			patsortplus(values, length);
			//patsortplus(valuesCopy, length);
			break;
		case 3:
			//P3 sort
			cout << "\n\nP3 sort:" << endl;
			pThreeSort(values, length);
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
		//	printf("%d ", valuesCopy[n]);
		//}
	}
	return 0;
}

int main()
{
	genData();
	printf("Number of values to be sorted: %d \n", length);
	printf("Using time as seed value: %s \n", timeSeed ? "true" : "false");

	cout << "\n\n-----------------Random data-----------------" << endl;
	doSorts(unsortedRandom, length);
	cout << "\n\n-----------Random semi sorted data-----------" << endl;
	doSorts(UnsortedSemi, length);
	cout << "\n\n--------Semi increasing sorted data----------" << endl;
	doSorts(unsortedIncreasing, length);

    return 0;
}