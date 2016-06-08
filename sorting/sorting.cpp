// sorting.cpp : Defines the entry point for the console application.
// Random and partially sorted arrays will be created and sorted using different algorithms
// The runtime of the different algorithms will be timed

#include "stdafx.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <chrono>
#include <random>
#include <list>

using namespace std;
using namespace std::chrono;

// Initialize parameters
const int length = 10000;
int alg[] = { 2 };
bool inputDataPrint = false;
bool outputDataPrint = false;
bool const timeSeed = false;
int const disorder = 10;
float const percentage = 0.10;



// Initialize the arrays which need to be sorted
long long random[length] = {};
long long semiSorted[length] = {};
long long reverseSemiSorted[length] = {};
long long valuesCopy[length] = {};
long long pingPongSwap[length] = {};

int patsort(long long values[], const int length);
int patsortplus(long long values[], const int length);
int pThreeSort(long long values[], long long pingPongSwap[], const int length);

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


//TODO cmp cleanen
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
	
	if (timeSeed == true)
		std::srand(std::time(0));
	else
		std::srand(1);

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
		random[n] = std::rand();
	}

	// Fill array with increasing elements
	for (int n{ 0 }; n < length; n++)
	{
		semiSorted[n] = n;
	}

	// Fill array with decreasing elements
	for (int n{ 0 }; n < length; n++)
	{
		reverseSemiSorted[n] = length - n;
	}

	// add noise
	addNoise(semiSorted, length);
	addNoise(reverseSemiSorted, length);

	return 0;
}

int doSorts(long long values[], const string inputOrder, const int length)
{
	// Initialize log file
	ofstream logfile;
	logfile.open("logfile" + std::to_string(length) + ".csv", ofstream::app);

	string algorithm = {};
	high_resolution_clock::time_point t1;

	// Optional printing of the generated array before sorting
	if (inputDataPrint == true) {
		printf("before sorting the list is: \n");
		for (int n{ 0 }; n < length; n++)
		{
			printf("%d ", values[n]);
		}
	}

	// Perform different sorting algorithms and time the runtime
	for (int i : alg)
	{
		std::copy(values, values + length, valuesCopy);

		switch (i)
		{
			// Error. Unreachable declaration.
			t1 = high_resolution_clock::now();
			cout << "\n\nError unreachable declaration in switch" << endl;
			logfile << "Error unreachable declaration in switch" << endl;
			algorithm = "ERROR";
			break;
		case 0:
			//qsort
			algorithm = "qsort";
			cout << "\n" + algorithm + ":" << endl;
			t1 = high_resolution_clock::now();
			qsort(valuesCopy, length, sizeof(long long), cmpfunc);
			//TODO fix GNU quicksort
			/*_quicksort(copyrandom, length, sizeof(long long), compare_doubles);*/
			break;
		case 1:
			//Patience sort
			algorithm = "PatSort";
			cout << "\n" + algorithm + ":" << endl;
			t1 = high_resolution_clock::now();
			patsort(valuesCopy, length);
			break;
		case 2:
			//Patience+ sort
			algorithm = "PatPlus";
			cout << "\n" + algorithm + ":" << endl;
			t1 = high_resolution_clock::now();
			patsortplus(valuesCopy, length);
			break;
		case 3:
			//P3 sort
			algorithm = "P3";
			cout << "\n" + algorithm + ":" << endl;
			t1 = high_resolution_clock::now();
			pThreeSort(valuesCopy, pingPongSwap, length);
			break;
		case 4:
			//TimSort
			algorithm = "TimSort";
			cout << "\n" + algorithm + ":" << endl;
			t1 = high_resolution_clock::now();
			break;
		default:
			// i undefined
			cout << "\n\nSwitch out of bound:" << endl;
			logfile << "\n\"Switch out of bound\";" << endl;
			algorithm = "ERROR";
			t1 = high_resolution_clock::now();
			break;
		}
		high_resolution_clock::time_point t2 = high_resolution_clock::now();

		//Calculate and print execution time
		auto duration = duration_cast<microseconds>(t2 - t1).count();
		printf("\nTime needed for sorting: %d microseconds \n", duration);
		logfile << "\n"+ algorithm + ";" + to_string(length) + ";" + inputOrder + ";" + to_string(duration);

		// Optional printing of the array after sorting
		if (outputDataPrint == true) {
			printf("after sorting the list is: \n");
			for (int n{ 0 }; n < length; n++)
			{
				printf("%d ", valuesCopy[n]);
			}
		}
	}

	logfile.close();

	return 0;
}

int main()
{
	// Clear old log file
	ofstream logfile;
	logfile.open("logfile" + std::to_string(length) + ".csv");
	logfile << "Algorithm;input length;input type;Time (microseconds)";
	logfile.close();

	genData();
	printf("Number of values to be sorted: %d \n", length);
	printf("Using time as seed value: %s \n", timeSeed ? "true" : "false");

	cout << "\n\n-----------------Random data-----------------" << endl;
	doSorts(random, "Random",length);
	cout << "\n\n-------- Increasing semi sorted data---------" << endl;
	doSorts(semiSorted, "IncreasingSemiSorted",length);
	cout << "\n\n--------Reverse semi sorted data----------" << endl;
	doSorts(reverseSemiSorted, "reverseSemiSorted", length);

    return 0;
}
