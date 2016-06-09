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

inline bool run_greater(const long long& x, const long long& y)
{
	return x > y;
}

// reverse less predicate to turn min-heap into max-heap
inline bool run_less(const long long& x, const long long& y)
{
	return run_greater(y, x);
}

template<class Iterator>
void pThree_Sort(Iterator begin, Iterator end, int const length) {
	typedef typename iterator_traits<Iterator>::value_type RunType;
	typedef list<RunType> Run;

	vector<Run> runs;
	vector<long long> tailValues;
	vector<long long> headValues;
	typename vector<long long>::iterator i;
	//vector<Run> * tails;

	// sort into runs
	// TODO fix problem that piles are incorrectly built
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	for (Iterator it = begin; it != end; it++) {
		i = lower_bound(headValues.begin(), headValues.end(), *it, run_less);
		if (i == headValues.end()) {
			i = upper_bound(tailValues.begin(), tailValues.end(), *it, run_greater);
			if (i == tailValues.end()) {
				Run newRun;
				newRun.emplace_front(*it);

				runs.push_back(newRun);
				headValues.push_back(*it);
				tailValues.push_back(*it);
			}
			else {
				int index = distance(tailValues.begin(), i);
				runs[index].emplace_back(*it);
				tailValues[index] = *it;
			}
		}
		else {
			int index = distance(headValues.begin(), i);
			runs[index].emplace_front(*it);
			headValues[index] = *it;
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
