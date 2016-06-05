/* Code from http://euler.math.uga.edu/wiki/index.php?title=Patience_sorting
TODO take a look at https://en.wikibooks.org/wiki/Algorithm_Implementation/Sorting/Patience_sort */

#include <vector>
#include <algorithm>
#include <list>
#include <iterator>

// Needed for timer
#include <iostream>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

template<typename RunType>
inline bool run_greater(const RunType& x, const RunType& y)
{
	return x.front() > y.front();
}

// reverse less predicate to turn max-heap into min-heap
template<typename RunType>
inline bool run_less(const RunType& x, const RunType& y)
{
	return run_greater(y, x);
}

template<typename Iterator>
int patience_sort(Iterator begin, Iterator end)
{
	typedef typename std::iterator_traits<Iterator>::value_type DataType;
	typedef std::list<DataType> RunType;

	std::vector<RunType> runs;

	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	for (Iterator it = begin; it != end; it++)
	{
		RunType newRun;
		newRun.emplace_front(*it);
		typename std::vector<RunType>::iterator insert_it =
			std::lower_bound(runs.begin(), runs.end(), newRun,
				run_greater<RunType>);
		if (insert_it == runs.end())
			runs.push_back(newRun);
		else
			insert_it->emplace_front(*it);
	}
	high_resolution_clock::time_point t2 = high_resolution_clock::now();

	// sorted array already satisfies heap property for min-heap
	// TODO reverse sort order
	high_resolution_clock::time_point t3 = high_resolution_clock::now();
	for (Iterator it = begin; it != end; it++)
	{
		std::pop_heap(runs.begin(), runs.end(), run_less<RunType>);
		*it = runs.back().front();
		runs.back().pop_front();
		if (runs.back().empty())
			runs.pop_back();
		else
			std::push_heap(runs.begin(), runs.end(), run_less<RunType>);
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