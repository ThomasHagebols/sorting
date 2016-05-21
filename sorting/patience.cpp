/* Code from http://euler.math.uga.edu/wiki/index.php?title=Patience_sorting
TODO take a look at https://en.wikibooks.org/wiki/Algorithm_Implementation/Sorting/Patience_sort */

#include <vector>
#include <algorithm>
#include <stack>
#include <iterator>

template<typename PileType>
bool pile_less(const PileType& x, const PileType& y)
{
	return x.top() < y.top();
}

// reverse less predicate to turn max-heap into min-heap
template<typename PileType>
bool pile_more(const PileType& x, const PileType& y)
{
	return pile_less(y, x);
}

template<typename Iterator>
void patience_sort(Iterator begin, Iterator end)
{
	typedef typename std::iterator_traits<Iterator>::value_type DataType;
	typedef std::stack<DataType> PileType;
	std::vector<PileType> piles;



	for (Iterator it = begin; it != end; it++)
	{
		PileType new_pile;
		new_pile.push(*it);
		typename std::vector<PileType>::iterator insert_it =
			std::lower_bound(piles.begin(), piles.end(), new_pile,
				pile_less<PileType>);
		if (insert_it == piles.end())
			piles.push_back(new_pile);
		else
			insert_it->push(*it);
	}


	// sorted array already satisfies heap property for min-heap

	for (Iterator it = begin; it != end; it++)
	{
		std::pop_heap(piles.begin(), piles.end(), pile_more<PileType>);
		*it = piles.back().top();
		piles.back().pop();
		if (piles.back().empty())
			piles.pop_back();
		else
			std::push_heap(piles.begin(), piles.end(), pile_more<PileType>);
	}
}

int patsort(int values[], int length) {
	patience_sort(values, values + length);
	return 0;
}