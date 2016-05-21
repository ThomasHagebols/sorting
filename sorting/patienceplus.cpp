#include <vector>
#include <stack>
#include <list>
#include <iterator>
#include <algorithm>
#include <cassert>
#include <malloc.h>

using namespace std;

template<class E>
struct run_less {
	bool operator()(const std::list<E> &list1, const std::list<E> &list2) const {
		return list1.front() < list2.front();
	}
};

	template<class E>
	struct run_greater {
		bool operator()(const std::list<E> &list1, const std::list<E> &list2) const {
			return list1.front() > list2.front();
		}
	};

template<class Iterator>
void patience_sort_plus(Iterator first, Iterator last) {
	typedef typename std::iterator_traits<Iterator>::value_type E;
	typedef std::list<E> Run;
	std::vector<long long> tails;
	std::vector<Run> runs;

	// sort into runs
	for (Iterator it = first; it != last; it++) {
		E& x = *it;
		Run newRun;
		newRun.emplace_front(x);
		typename std::vector<Run>::iterator i =
			std::lower_bound(runs.begin(), runs.end(), newRun, run_less<E>());
		if (i != runs.end())
			i->emplace_front(x);
		else
			runs.push_back(newRun);
	}

	// priority queue allows us to merge runs efficiently
	// we use greater-than comparator for min-heap
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
}

int patsortplus(long long values[], int length) {
	patience_sort_plus(values, values + length);
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