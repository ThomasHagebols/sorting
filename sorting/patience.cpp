/* Code from http://euler.math.uga.edu/wiki/index.php?title=Patience_sorting
TODO take a look at https://en.wikibooks.org/wiki/Algorithm_Implementation/Sorting/Patience_sort */

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
	return x.back() > y.back();
}

template<typename Run>
inline bool run_front_greater(const Run& x, const Run& y)
{
	return x.front() > y.front();
}

template<typename Run>
inline bool run_less(const Run& x, const Run& y)
{
	return x.back() < y.back();
}

template<typename Iterator>
long long patience_sort(Iterator begin, Iterator end)
{
	typedef typename std::iterator_traits<Iterator>::value_type RunType;
	typedef std::list<RunType> Run;

	std::vector<Run> runs;

	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	for (Iterator it = begin; it != end; it++)
	{
		Run newRun;
		newRun.emplace_front(*it);
		typename std::vector<Run>::iterator i =
			std::upper_bound(runs.begin(), runs.end(), newRun, run_greater<Run>);
		if (i == runs.end())
			runs.push_back(newRun);
		else
			i->emplace_back(*it);
	}
	high_resolution_clock::time_point t2 = high_resolution_clock::now();

	// Make min heap and use the heap to merge more efficiently
	high_resolution_clock::time_point t3 = high_resolution_clock::now();
	make_heap(runs.begin(), runs.end(), run_front_greater<Run>);
	for (Iterator it = begin; it != end; it++) {
		pop_heap(runs.begin(), runs.end(), run_front_greater<Run>);
		Run &smallPile = runs.back();
		*it = smallPile.front();
		smallPile.pop_front();
		if (smallPile.empty()) {
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
	//printf("\nTime needed for pileCre: %d microseconds ", pileCreTime);
	//printf("\nTime needed for merging: %d microseconds ", mergeTime);

	return pileCreTime;
}

long long patsort(long long values[], int const length) {
	return patience_sort(values, values + length);
}
