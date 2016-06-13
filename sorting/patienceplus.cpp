#include <math.h>
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
using namespace chrono;

inline bool cmp_greater(const long long& x, const long long& y)
{
	return x > y;
}

// reverse less predicate to turn min-heap into max-heap
inline bool cmp_less(const long long& x, const long long& y)
{
	return x < y;
}

template<typename Run>
inline bool run_front_greater(const Run& x, const Run& y)
{
	return x.front() > y.front();
}

template<class Iterator>
long long patience_sort_plus(Iterator begin, Iterator end, int const length) {
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
		i = upper_bound(tailValues.begin(), tailValues.end(), *it, cmp_greater);
		if (i == tailValues.end()) {
			i = lower_bound(headValues.begin(), headValues.end(), *it, cmp_less);
			if (i == headValues.end()) {
				Run newRun;
				newRun.emplace_front(*it);

				runs.push_back(newRun);
				headValues.push_back(*it);
				tailValues.push_back(*it);
			}
			else {
				int index = distance(headValues.begin(), i);
				runs[index].emplace_front(*it);
				headValues[index] = *it;
			}
		}
		else {
			int index = distance(tailValues.begin(), i);
			runs[index].emplace_back(*it);
			tailValues[index] = *it;
		}
	}
	high_resolution_clock::time_point t2 = high_resolution_clock::now();



	// priority queue allows us to merge runs efficiently
	// we use greater-than comparator for min-heap
	high_resolution_clock::time_point t3 = high_resolution_clock::now();
	make_heap(runs.begin(), runs.end(), run_front_greater<Run>);
	for (Iterator it = begin; it != end; it++) {
		pop_heap(runs.begin(), runs.end(), run_front_greater<Run>);
		Run &smallPile = runs.back();
		*it = smallPile.front();
		smallPile.pop_front();
		if (smallPile.empty()){
			runs.pop_back();
		}
		else {
			push_heap(runs.begin(), runs.end(), run_front_greater<Run>);
		}
	}
	assert(runs.empty());
	high_resolution_clock::time_point t4 = high_resolution_clock::now();

	long long pileCreTime = duration_cast<microseconds>(t2 - t1).count();
	long long mergeTime = duration_cast<microseconds>(t4 - t3).count();
	printf("\nTime needed for pileCre: %d microseconds ", pileCreTime);
	printf("\nTime needed for merging: %d microseconds ", mergeTime);

	return pileCreTime;
}

long long patsortplus(long long values[], const int length) {

	return patience_sort_plus(values, values + length, length);
}
