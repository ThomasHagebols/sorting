#include <vector>
#include <list>
#include <algorithm>
#include <malloc.h>
#include <tuple>

using namespace std;

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
int UPingPongMerge(vector<list<long long>> runs, int runSize[], int const length)
{
	//initialize array with number of integers
	long long * elems1;
	elems1 = new long long[length] {};
	long long * elems2;
	elems2 = new long long[length] {};
	//long long * result;
	//result = new long long[length] {};
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
		insertArray(elems1, runs[runSizeRef[j].first], runSizeRef[j].second, nextEmptyArrayLoc);
		elemsRun.push_back(make_tuple(1, nextEmptyArrayLoc, runSizeRef[j].second));
		nextEmptyArrayLoc += runSizeRef[j].second;
	}

	tuple<int, int, int> curRun = elemsRun.front();
	int index = {};
	while (elemsRun.size() >= 2) {
		if (index >= (elemsRun.size() -1) || (get<2>(curRun) + get<2>(elemsRun[index +1])) > (get<2>(elemsRun.front()) + get<2>(elemsRun[1]))) {
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
		if (index < elemsRun.size()) {
			curRun = elemsRun[index];
		}
	}

	//if (get<0>(elemsRun[0]) == 1) {
	//	copy(elems1, elems1 + length, result);
	//} else {
	//	copy(elems2, elems2 + length, result);
	//}

	//for (int i{ 0 }; i < length; i++) {
	//	printf("%d ", result[i]);
	//}

	delete[] elems1;
	elems1 = NULL;
	delete[] elems2;
	elems2 = NULL;
	//delete[] result;
	//result = NULL;
	return 0;
}