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
void patience_sort_plus(Iterator begin, Iterator end) {
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

	// priority queue allows us to merge runs efficiently
	// we use greater-than comparator for min-heap
	high_resolution_clock::time_point t3 = high_resolution_clock::now();
	std::make_heap(runs.begin(), runs.end(), run_greater<Run>);
	for (Iterator it = begin; it != end; it++) {
		std::pop_heap(runs.begin(), runs.end(), run_greater<Run>);
		Run &smallPile = runs.back();
		*it = smallPile.front();
		smallPile.pop_front();
		if (smallPile.empty()){
			runs.pop_back();
		}
		else {
			std::push_heap(runs.begin(), runs.end(), run_greater<Run>);
		}
	}
	assert(runs.empty());
	high_resolution_clock::time_point t4 = high_resolution_clock::now();

	auto durationPile = duration_cast<microseconds>(t2 - t1).count();
	auto durationMerge = duration_cast<microseconds>(t4 - t3).count();
	printf("\nTime needed for pileCre: %d microseconds ", durationPile);
	printf("\nTime needed for merging: %d microseconds ", durationMerge);
}

int patsortplus(long long values[], const int length) {
	patience_sort_plus(values, values + length);
	return 0;
}