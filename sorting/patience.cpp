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
	return x.front() > y.front();
}

// reverse less predicate to turn min-heap into max-heap
template<typename Run>
inline bool run_less(const Run& x, const Run& y)
{
	return run_greater(y, x);
}

template<typename Iterator>
int patience_sort(Iterator begin, Iterator end)
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
			i->emplace_front(*it);
	}
	high_resolution_clock::time_point t2 = high_resolution_clock::now();

	// sorted array already satisfies heap property for min-heap
	// TODO reverse sort order
	high_resolution_clock::time_point t3 = high_resolution_clock::now();
	for (Iterator it = begin; it != end; it++)
	{
		std::pop_heap(runs.begin(), runs.end(), run_less<Run>);
		*it = runs.back().front();
		runs.back().pop_front();
		if (runs.back().empty())
			runs.pop_back();
		else
			std::push_heap(runs.begin(), runs.end(), run_less<Run>);
	}
	high_resolution_clock::time_point t4 = high_resolution_clock::now();


	auto durationPile = duration_cast<microseconds>(t2 - t1).count();
	auto durationMerge = duration_cast<microseconds>(t4 - t3).count();
	printf("\nTime needed for pileCre: %d microseconds ", durationPile);
	printf("\nTime needed for merging: %d microseconds ", durationMerge);

	return 0;
}

int patsort(long long values[], int const length) {
	patience_sort(values, values + length);
	return 0;
}
