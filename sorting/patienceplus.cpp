#include <iostream>
#include <vector>
#include <stack>
#include <iterator>
#include <algorithm>
#include <cassert>

template <class E>
struct pile_less {
	bool operator()(const std::stack<E> &pile1, const std::stack<E> &pile2) const {
		return pile1.top() < pile2.top();
	}
};

template <class E>
struct pile_begin_less {
	bool operator()(const std::stack<E> &pile1, const std::stack<E> &pile2) const {
		return pile1.back() < pile2.back();
	}
};

template <class E>
struct pile_greater {
	bool operator()(const std::stack<E> &pile1, const std::stack<E> &pile2) const {
		return pile1.top() > pile2.top();
	}
};


template <class Iterator>
void patience_sort_plus(Iterator first, Iterator last) {
	typedef typename std::iterator_traits<Iterator>::value_type E;
	typedef std::stack<E> Pile;

	std::vector<Pile> piles;

	// sort into piles
	for (Iterator it = first; it != last; it++) {
		E& x = *it;
		Pile newPile;
		newPile.push(x);
		typename std::vector<Pile>::iterator i =
			std::lower_bound(piles.begin(), piles.end(), newPile, pile_less<E>());
		typename std::vector<Pile>::iterator j =
			std::lower_bound(piles.begin(), piles.end(), newPile, pile_begin_less<E>());
		if (i != piles.end())
			i->push(x);
		else if (j != piles.begin())
			j->push_back(newPile.end());
		else
			piles.push_back(newPile);
	}

	// priority queue allows us to merge piles efficiently
	// we use greater-than comparator for min-heap
	std::make_heap(piles.begin(), piles.end(), pile_greater<E>());
	for (Iterator it = first; it != last; it++) {
		std::pop_heap(piles.begin(), piles.end(), pile_greater<E>());
		Pile &smallPile = piles.back();
		*it = smallPile.top();
		smallPile.pop();
		if (smallPile.empty())
			piles.pop_back();
		else
			std::push_heap(piles.begin(), piles.end(), pile_greater<E>());
	}
	assert(piles.empty());
}

int patsortplus(int values[], int length) {
	patience_sort_plus(values, values + length);
	return 0;
}
// No newline at end of file