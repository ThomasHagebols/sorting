// TODO value 12 disappears...

#include <algorithm>
#include <cassert>
#include <iterator>
#include <list>
#include <vector>

// Needed for timer
#include <chrono>
#include <ctime>
#include <iostream>

using namespace std;
using namespace std::chrono;

int UPingPongMerge(vector<list<long long>> runs, int runSize[], const int length);

template<typename Run>
inline bool run_greater(const Run& x, const Run& y)
{
	return x.front() > y.front();
}

// reverse less predicate to turn min-heap into max-heap
template<typename Run>
inline bool run_less(const Run& x, const Run& y)
{
	return run_greater(y, x);
}

template<typename Run>
inline bool run_end_greater(const Run& x, const Run& y)
{
	return x.back() > y.back();
}

template<class Iterator>
void pThree_Sort(Iterator begin, Iterator end, int const length) {
	typedef typename std::iterator_traits<Iterator>::value_type RunType;
	typedef std::list<RunType> Run;

	std::vector<Run> runs;
	//std::vector<long long> headsVal;
	//std::vector<long long> tailsVal;
	//std::vector<Run> * heads;
	//std::vector<Run> * tails;

	// sort into runs
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	for (Iterator it = begin; it != end; it++) {
		//Run& x = *it;
		Run newRun;
		newRun.emplace_front(*it);
		typename std::vector<Run>::iterator i =
			std::lower_bound(runs.begin(), runs.end(), newRun, run_less<Run>);
		if (i == runs.end()) {
			i = std::upper_bound(runs.begin(), runs.end(), newRun, run_end_greater<Run>);
			if (i == runs.end())
				runs.push_back(newRun);
			else
				i->emplace_back(*it);
		}
		else
			i->emplace_front(*it);
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

int pThreeSort(long long values[], long long pingPongSwap[], const int length) {
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
