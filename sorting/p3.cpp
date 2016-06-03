#include <vector>
#include <stack>
#include <list>
#include <iterator>
#include <algorithm>
#include <cassert>
#include <malloc.h>
#include <math.h>

// Needed for timer
#include <iostream>
#include <ctime>
#include <chrono>
using namespace std::chrono;

using namespace std;

int UPingPongMerge(vector<list<long long>> runs, int runSize[], const int length);

template<class E>
struct run_less {
	bool operator()(const std::list<E> &list1, const std::list<E> &list2) const {
		return list1.front() < list2.front();
	}
};

template<class E>
struct run_end_greater {
	bool operator()(const std::list<E> &list1, const std::list<E> &list2) const {
		return list1.back() < list2.back();
	}
};


	template<class E>
	struct run_greater {
		bool operator()(const std::list<E> &list1, const std::list<E> &list2) const {
			return list1.front() > list2.front();
		}
	};

template<class Iterator>
void pThree_Sort(Iterator first, Iterator last, int const length) {
	typedef typename std::iterator_traits<Iterator>::value_type E;
	typedef std::list<E> Run;

	//Calculate the size 
	//int memSize{ (int) sqrt(length) };

	std::vector<Run> runs;
	std::vector<long long> headsVal;
	std::vector<long long> tailsVal;
	std::vector<Run> * heads;
	std::vector<Run> * tails;

	// sort into runs
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	for (Iterator it = first; it != last; it++) {
		E& x = *it;
		Run newRun;
		newRun.emplace_front(x);
		typename std::vector<Run>::iterator i =
			std::lower_bound(runs.begin(), runs.end(), newRun, run_less<E>());
		if (i != runs.end())
			i->emplace_front(x);
		else // This adds the append to back functionality but currently loops the inefficient way (from begin to end, rather than end to begin, which might in some situations be slightly slower even).
		{
			std::upper_bound(runs.begin(), runs.end(), newRun, run_end_greater<E>());
		if (i != runs.end())
			i->emplace_back(x);
		else
			runs.push_back(newRun);
		}
	}
	high_resolution_clock::time_point t2 = high_resolution_clock::now();


	high_resolution_clock::time_point t3 = high_resolution_clock::now();
	int nrRuns = runs.size();
	int * runSizes;
	runSizes = new int[nrRuns];
	for (int j = { 0 }; j < runs.size(); j++) {
		runSizes[j] = runs[j].size();
	}


	UPingPongMerge(runs, runSizes, length);

	delete [] runSizes;
	runSizes = NULL;
	high_resolution_clock::time_point t4 = high_resolution_clock::now();


	auto durationPile = duration_cast<microseconds>(t2 - t1).count();
	auto durationMerge = duration_cast<microseconds>(t4 - t3).count();
	printf("\nTime needed for pileCre: %d microseconds ", durationPile);
	printf("\nTime needed for merging: %d microseconds ", durationMerge);
}

int pThreeSort(long long values[], const int length) {
	pThree_Sort(values, values + length, length);
	return 0;
}

//int main() {
//	// Preallocate memory for the head and tail pointers and values
//	struct node *head_pointers[32] = {};
//	long long head_values[32] = {};
//
//	struct tail_pointers[32] = {};
//	long long tail_values[32] = {};
//
//	int run_sizes[32] = {};

	//SQRT_ELEMS =  
	//runs = (char*) malloc(SQRT_ELEMS * )
	//// Initializa random number generator seed (time) and n
	//std::srand(std::time(0));
	//int n;
	//int i;

	//// Fill array with random variables
	//for (n = 0; n < length; n++)
	//{
	//	unsorted[n] = std::rand();
	//}
	//mem_size = (char*)malloc(sizeof(values) / sizeof(long long));


	//patience_sort_plus(values, values + length);
	//return 0;

// No newline at end of file