#include <algorithm>
#include <iterator>
#include <list>
#include <vector>
#include <cassert>

// Needed for timer
#include <chrono>
#include <ctime>
#include <iostream>

using namespace std;
using namespace std::chrono;

int UPingPongMerge(vector<list<long long>> runs, int runSize[], const int length);

inline bool cmp_greater(const long long& x, const long long& y)
{
	return x > y;
}

inline bool cmp_less(const long long& x, const long long& y)
{
	return x < y;
}

template<class Iterator>
long long pThree_Sort(Iterator begin, Iterator end, int const length) {
	typedef typename iterator_traits<Iterator>::value_type RunType;
	typedef list<RunType> Run;

	vector<Run> runs;
	vector<long long> tailValues;
	vector<long long> headValues;
	typename vector<long long>::iterator i;

	// sort into runs
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	for (Iterator it = begin; it != end; it++) {
		i = upper_bound(tailValues.begin(), tailValues.end(), *it, cmp_greater);
		if (i == tailValues.end()) {
			i = lower_bound(headValues.begin(), headValues.end(), *it, cmp_less);
			if (i == headValues.end()) {
				Run newRun;
				newRun.emplace_front(*it);

				runs.push_back(newRun);
				headValues.push_back(*it);
				tailValues.push_back(*it);
			}
			else {
				int index = distance(headValues.begin(), i);
				runs[index].emplace_front(*it);
				headValues[index] = *it;
			}
		}
		else {
			int index = distance(tailValues.begin(), i);
			runs[index].emplace_back(*it);
			tailValues[index] = *it;
		}
	}
	high_resolution_clock::time_point t2 = high_resolution_clock::now();

	// Merge runs using ping pong
	high_resolution_clock::time_point t3 = high_resolution_clock::now();
	int nrRuns = runs.size();
	cout << nrRuns << endl;

	int * runSizes;
	runSizes = new int[nrRuns];

	//long long * result;
	//result = new long long[length];

	for (int j = { 0 }; j < runs.size(); j++) {
		runSizes[j] = runs[j].size();
	}

	UPingPongMerge(runs, runSizes, length);

	//int x = {};
	//for (Iterator it = begin; it != end; it++) {
	//	*it = result[x];
	//	x++;
	//}

	//delete[] result;
	//result = NULL;

	delete [] runSizes;
	runSizes = NULL;

	runs.erase(runs.begin(), runs.end()); // TODO maybe remove this
	high_resolution_clock::time_point t4 = high_resolution_clock::now();

	long long pileCreTime = duration_cast<microseconds>(t2 - t1).count();
	long long mergeTime = duration_cast<microseconds>(t4 - t3).count();
	//printf("\nTime needed for pileCre: %d microseconds ", pileCreTime);
	//printf("\nTime needed for merging: %d microseconds ", mergeTime);

	return pileCreTime;
}

long long  pThreeSort(long long values[], const int length) {
	return pThree_Sort(values, values + length, length);
}