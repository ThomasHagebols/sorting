#include <iostream>
#include <vector>
#include <stack>
#include <list>
#include <iterator>
#include <algorithm>
#include <cassert>
#include <chrono>
#include <ctime>
#include <cstdlib>
#include <malloc.h>
#include <tuple>

//using namespace std::chrono;
using namespace std;

int UPingPongMerge(vector<list<long long>> runs, int runSize[], int const length);

int const length = 1000;

//to do: veranderen int naar Pile voor accepteren van runs

bool pairCompare(const pair<int, int> &firstElem, const pair<int, int> &secondElem) {
	return firstElem.second < secondElem.second;
}

int insertArray(long long elemArray[], list<long long> pile, int runSize, int nextEmptyArrayLoc) {
	for (int i = { nextEmptyArrayLoc }; i < nextEmptyArrayLoc + runSize; i++) {
		elemArray[i] = pile.front();
		pile.pop_front();
	}
	return 0;
}
int UPingPongMerge(vector<list<long long>> runs, int runSize[], int const size)
{
	//initialize array with number of integers
	//const int length = 36;
    long long elems1[length];
	long long elems2[length];
	long long result[length];
	vector<pair<int, int>> runSizeRef;
	//fill array with index and sizes
		for (int i = { 0 }; i != runs.size(); i++) {
		runSizeRef.push_back(make_pair(i, runSize[i]));
	}

	//sort array ascending sizes
	sort(runSizeRef.begin(), runSizeRef.end(), pairCompare);

	int nextEmptyArrayLoc = { 0 };

	vector<tuple<int, int, int>> elemsRun;

	for (int j = { 0 }; j < runSizeRef.size(); j++) {
		//copy(runs[runSizeRef[j].first], runs[runSizeRef[j].first].size(), elems1[nextEmptyArrayLoc]);
		insertArray(elems1, runs[runSizeRef[j].first], runSizeRef[j].second, nextEmptyArrayLoc);
		elemsRun.push_back(make_tuple(1, nextEmptyArrayLoc, runSizeRef[j].second));
		nextEmptyArrayLoc += runSizeRef[j].second;
	}

	tuple<int, int, int> curRun = elemsRun.front();
	int index = { 0 };
	while (elemsRun.size() >= 2) {
		cout << elemsRun.size() << endl;
		if (index == (elemsRun.size() -1) || (get<2>(curRun) + get<2>(elemsRun[index +1])) > (get<2>(elemsRun.front()) + get<2>(elemsRun[1]))) {
			curRun = elemsRun.front();
			index = 0;
		}
		if (get<0>(curRun) == 1) {
			if (get<0>(elemsRun[index + 1]) == 1) {
				merge(&elems1[get<1>(curRun)], &elems1[get<1>(curRun)] + get<2>(curRun),
					&elems1[get<1>(elemsRun[index + 1])], &elems1[get<1>(elemsRun[index + 1])] + get<2>(elemsRun[index + 1]),
					&elems2[get<1>(curRun)]);
			}
			else {
				merge(&elems1[get<1>(curRun)], &elems1[get<1>(curRun)] + get<2>(curRun),
					&elems2[get<1>(elemsRun[index + 1])], &elems2[get<1>(elemsRun[index + 1])] + get<2>(elemsRun[index + 1]),
					&elems2[get<1>(curRun)]);
			}
			get<0>(elemsRun[index]) = 2;
		}
		else {
			if (get<0>(elemsRun[index + 1]) == 1) {
				merge(&elems2[get<1>(curRun)], &elems2[get<1>(curRun)] + get<2>(curRun),
					&elems1[get<1>(elemsRun[index + 1])], &elems1[get<1>(elemsRun[index + 1])] + get<2>(elemsRun[index + 1]),
					&elems1[get<1>(curRun)]);
			}	else {
				merge(&elems2[get<1>(curRun)], &elems2[get<1>(curRun)] + get<2>(curRun),
					&elems2[get<1>(elemsRun[index + 1])], &elems2[get<1>(elemsRun[index + 1])] + get<2>(elemsRun[index + 1]),
					&elems1[get<1>(curRun)]);
			}
			get<0>(elemsRun[index]) = 1;
		}
		get<2>(elemsRun[index]) += get<2>(elemsRun[index + 1]);
		elemsRun.erase(elemsRun.begin() + index +1);
		index++;
		if (elemsRun.size() > 1) {
			curRun = elemsRun[index];
		}
	}
	long long results[length];
	if (get<0>(elemsRun[0]) == 1) {
		copy(elems1, elems1 + length, result);
	} else {
		copy(elems2, elems2 + length, result);
	}
	return 0;
}

	//int main()
	//{
	//	vector<list<long long>> runs;
	//	list<long long> run1;
	//	list<long long> run2;
	//	list<long long> run3;
	//	list<long long> run4;
	//	list<long long> run5;
	//	list<long long> run6;
	//	list<long long> run7;
	//	list<long long> run8;

	//	run1.emplace_front(15);
	//	run1.emplace_front(9);
	//	run1.emplace_front(6);
	//	run1.emplace_front(5);
	//	run1.emplace_front(1);

	//	run2.emplace_front(11);
	//	run2.emplace_front(10);
	//	run2.emplace_front(7);
	//	run2.emplace_front(2);

	//	run3.emplace_front(29);
	//	run3.emplace_front(15);
	//	run3.emplace_front(9);
	//	run3.emplace_front(3);

	//	run4.emplace_front(17);
	//	run4.emplace_front(12);
	//	run4.emplace_front(8);

	//	run5.emplace_front(13);
	//	run5.emplace_front(11);
	//	run5.emplace_front(7);
	//	run5.emplace_front(1);

	//	run6.emplace_front(20);
	//	run6.emplace_front(14);
	//	run6.emplace_front(10);
	//	run6.emplace_front(9);
	//	run6.emplace_front(3);
	//	run6.emplace_front(1);

	//	run7.emplace_front(11);
	//	run7.emplace_front(10);

	//	run8.emplace_front(17);
	//	run8.emplace_front(14);
	//	run8.emplace_front(13);
	//	run8.emplace_front(10);
	//	run8.emplace_front(10);
	//	run8.emplace_front(10);
	//	run8.emplace_front(9);
	//	run8.emplace_front(8);

	//	runs.push_back(run1);
	//	runs.push_back(run2);
	//	runs.push_back(run3);
	//	runs.push_back(run4);
	//	runs.push_back(run5);
	//	runs.push_back(run6);
	//	runs.push_back(run7);
	//	runs.push_back(run8);

	//	int runSizes[8];

	//	runSizes[0] = run1.size();
	//	runSizes[1] = run2.size();
	//	runSizes[2] = run3.size();
	//	runSizes[3] = run4.size();
	//	runSizes[4] = run5.size();
	//	runSizes[5] = run6.size();
	//	runSizes[6] = run7.size();
	//	runSizes[7] = run8.size();
	//	
	//	UPingPongMerge(runs, runSizes);

	//	return 0;
	//}