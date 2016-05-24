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
void patience_sort_plus(Iterator first, Iterator last, int const length) {
	typedef typename std::iterator_traits<Iterator>::value_type E;
	typedef std::list<E> Run;

	//Calculate the size 
	//int memSize{ (int) sqrt(length) };
	std::vector<Run> runs;
	//std::vector<long long> headsVal;
	//std::vector<long long> tailsVal;
	long long tailHighest;
	long long headHighest;
	tailHighest = 0;
	headHighest = 0;
	Run tailHigh;
	Run headHigh;
	tailHigh.emplace_front(tailHighest);
	headHigh.emplace_front(headHighest);

	//std::vector<Run> * heads;
	//std::vector<Run> * tails;

	// sort into runs
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	for (Iterator it = first; it != last; it++) {
		E& x = *it;
		Run newRun;
		newRun.emplace_front(x);
		if (newRun.front() > tailHigh.front())
		{
			if (newRun.front() < headHigh.front())
			{
				typename std::vector<Run>::iterator j =
					std::upper_bound(runs.begin(), runs.end(), newRun, run_end_greater<E>());
				if (j != runs.end())
				{
					j->emplace_front(x);
					headHigh.pop_front();
					headHigh.emplace_front(x);
				}
			}
			else
			{
				runs.push_back(newRun);
				tailHigh.pop_front();
				tailHigh.emplace_front(x);
				if (newRun.front() > headHigh.front())
				{
					headHigh.pop_front();
					headHigh.emplace_front(x);
				}
			}
		}
		else
		{
			typename std::vector<Run>::iterator i =
				std::lower_bound(runs.begin(), runs.end(), newRun, run_less<E>());
			if (i != runs.end())
			{
				i->emplace_front(x);
			}
			else
			{
				runs.push_back(newRun);
			}
		}
	}
	
	high_resolution_clock::time_point t2 = high_resolution_clock::now();

	auto durationPile = duration_cast<microseconds>(t2 - t1).count();
	printf("\nTime needed for pileCre: %d microseconds ", durationPile);

	// priority queue allows us to merge runs efficiently
	// we use greater-than comparator for min-heap
	high_resolution_clock::time_point t3 = high_resolution_clock::now();
	std::make_heap(runs.begin(), runs.end(), run_greater<E>());
	for (Iterator it = first; it != last; it++) {
		std::pop_heap(runs.begin(), runs.end(), run_greater<E>());
		Run &smallPile = runs.back();
		*it = smallPile.front();
		smallPile.pop_front();
		if (smallPile.empty())
			runs.pop_back();
		else
			std::push_heap(runs.begin(), runs.end(), run_greater<E>());
	}
	assert(runs.empty());
	high_resolution_clock::time_point t4 = high_resolution_clock::now();



	auto durationMerge = duration_cast<microseconds>(t4 - t3).count();

	printf("\nTime needed for merging: %d microseconds ", durationMerge);
}

int patsortplus(long long values[], int length) {
	patience_sort_plus(values, values + length, length);
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