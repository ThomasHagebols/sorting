#include <vector>
#include <list>
#include <algorithm>
#include <malloc.h>
#include <tuple>

using namespace std;

//compare the run size
bool pairCompare(const pair<int, int> &firstElem, const pair<int, int> &secondElem) {
	return firstElem.second < secondElem.second;
}

//function for inserting the runs into elems1
int insertArray(long long elemArray[], list<long long> pile, int runSize, int nextEmptyArrayLoc) {
	for (int i = { nextEmptyArrayLoc }; i < nextEmptyArrayLoc + runSize; i++) {
		elemArray[i] = pile.front();
		pile.pop_front();
	}
	return 0;
}

int UPingPongMerge(vector<list<long long>> runs, int runSize[], int const length)
{
	//initialize array 
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

	//sort ascending on sizes
	sort(runSizeRef.begin(), runSizeRef.end(), pairCompare);

	int nextEmptyArrayLoc = { 0 };

	vector<tuple<int, int, int>> elemsRun;

	//used for inserting the runs and store the metadata for these runs
	for (int j = { 0 }; j < runSizeRef.size(); j++) {
		insertArray(elems1, runs[runSizeRef[j].first], runSizeRef[j].second, nextEmptyArrayLoc);
		elemsRun.push_back(make_tuple(1, nextEmptyArrayLoc, runSizeRef[j].second));
		nextEmptyArrayLoc += runSizeRef[j].second;
	}

	tuple<int, int, int> curRun = elemsRun.front();
	int index = {};

	//check whether there is more than 1 run left
	while (elemsRun.size() >= 2) {

		//necesarry for checking whether there is a next run and whether merging the current run and next run is beneficial
		if (index >= (elemsRun.size() -1) || (get<2>(curRun) + get<2>(elemsRun[index +1])) > (get<2>(elemsRun.front()) + get<2>(elemsRun[1]))) {
			curRun = elemsRun.front();
			index = 0;
		}
		//check whether the current run is in the first array
		if (get<0>(curRun) == 1) {
			//check if the next run is in the first array
			if (get<0>(elemsRun[index + 1]) == 1) {
				merge(&elems1[get<1>(curRun)], &elems1[get<1>(curRun)] + get<2>(curRun),
					&elems1[get<1>(elemsRun[index + 1])], &elems1[get<1>(elemsRun[index + 1])] + get<2>(elemsRun[index + 1]),
					&elems2[get<1>(curRun)]);
			}
			//otherwise merge with the second array
			else {
				merge(&elems1[get<1>(curRun)], &elems1[get<1>(curRun)] + get<2>(curRun),
					&elems2[get<1>(elemsRun[index + 1])], &elems2[get<1>(elemsRun[index + 1])] + get<2>(elemsRun[index + 1]),
					&elems2[get<1>(curRun)]);
			}
			get<0>(elemsRun[index]) = 2;
		}
		else {
			//the current run is in the second array and check whether the next run is in the first array
			if (get<0>(elemsRun[index + 1]) == 1) {
				merge(&elems2[get<1>(curRun)], &elems2[get<1>(curRun)] + get<2>(curRun),
					&elems1[get<1>(elemsRun[index + 1])], &elems1[get<1>(elemsRun[index + 1])] + get<2>(elemsRun[index + 1]),
					&elems1[get<1>(curRun)]);
			}	else {
				//merge with the second array
				merge(&elems2[get<1>(curRun)], &elems2[get<1>(curRun)] + get<2>(curRun),
					&elems2[get<1>(elemsRun[index + 1])], &elems2[get<1>(elemsRun[index + 1])] + get<2>(elemsRun[index + 1]),
					&elems1[get<1>(curRun)]);
			}
			get<0>(elemsRun[index]) = 1;
		}
		//change metadata of the runs
		get<2>(elemsRun[index]) += get<2>(elemsRun[index + 1]);
		elemsRun.erase(elemsRun.begin() + index +1);
		index++;
		//change current run
		if (index < elemsRun.size()) {
			curRun = elemsRun[index];
		}
	}
	//used for storing the result
	//if (get<0>(elemsRun[0]) == 1) {
	//	copy(elems1, elems1 + length, result);
	//} else {
	//	copy(elems2, elems2 + length, result);
	//}

	delete[] elems1;
	elems1 = NULL;
	delete[] elems2;
	elems2 = NULL;
	//delete[] result;
	//result = NULL;
	return 0;
}