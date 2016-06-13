// sorting.cpp : Defines the entry point for the console application.
// Random and partially sorted arrays will be created and sorted using different algorithms
// The runtime of the different algorithms will be timed

#include "stdafx.h"
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
const int length = 100000;
int alg[] = { 0, 1, 2, 3 };
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

long long patsort(long long values[], const int length);
long long patsortplus(long long values[], const int length);
long long pThreeSort(long long values[], const int length);

int compare_doubles(const void *a, const void *b)
{
	const long long *da = (const long long *)a;
	const long long *db = (const long long *)b;

	return (*da > *db) - (*da < *db);
}

int cmpfunc(const void * a, const void * b)
{
	return (*(long long*)a - *(long long*)b);
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
	high_resolution_clock::time_point t2;
	long long duration = {};
	long long durationQSort = {};
	float relDuration = {};

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
		long long pileCreTime = {};
		long long mergeTime = {};

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
			break;
		case 1:
			//Patience sort
			algorithm = "PatSort";
			cout << "\n" + algorithm + ":" << endl;
			t1 = high_resolution_clock::now();
			pileCreTime = patsort(valuesCopy, length);
			break;
		case 2:
			//Patience+ sort
			algorithm = "PatPlus";
			cout << "\n" + algorithm + ":" << endl;
			t1 = high_resolution_clock::now();
			pileCreTime = patsortplus(valuesCopy, length);
			break;
		case 3:
			//P3 sort
			algorithm = "P3";
			cout << "\n" + algorithm + ":" << endl;
			t1 = high_resolution_clock::now();
			pileCreTime = pThreeSort(valuesCopy, length);
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
		t2 = high_resolution_clock::now();

		//Calculate and print execution time
		if (algorithm == "qsort") {
			duration = duration_cast<microseconds>(t2 - t1).count();
			durationQSort = duration_cast<microseconds>(t2 - t1).count();
		}
		else {
			duration = duration_cast<microseconds>(t2 - t1).count();
			mergeTime = duration - pileCreTime;
		}

		// Calculate the runtime relative to qsort
		if (durationQSort != 0)
			relDuration = (float)duration / (float)durationQSort;

		// Print and log results
		printf("\nTime needed for sorting: %d microseconds \n", duration);
		logfile << "\n" + algorithm + ";" + to_string(length) + ";" + inputOrder + ";" + to_string(duration) + ";" + to_string(pileCreTime) + ";" + to_string(mergeTime) + ";" + to_string(relDuration);

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
	logfile << "Algorithm;input length;input type;Time (microseconds);Pile creation time;Merge time;Relative runtime (to qsort) Devide by 1000";
	logfile.close();

	genData();
	printf("Number of values to be sorted: %d \n", length);
	printf("Using time as seed value: %s \n", timeSeed ? "true" : "false");

	for (int i = { 0 }; i < 25; i++) {
		cout << "=================================================" << endl;
		cout << "Loop " + to_string(i + 1) << endl;
		cout << "=================================================" << endl;
		cout << "\n\n-----------------Random data-----------------" << endl;
		doSorts(random, "Random", length);
		cout << "\n\n-------- Increasing semi sorted data---------" << endl;
		doSorts(semiSorted, "IncreasingSemiSorted", length);
		cout << "\n\n--------Reverse semi sorted data----------" << endl;
		doSorts(reverseSemiSorted, "reverseSemiSorted", length);
	}
    return 0;
}