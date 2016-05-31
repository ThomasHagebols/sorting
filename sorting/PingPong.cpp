#include <iostream>
#include <vector>
#include <stack>
#include <iterator>
#include <algorithm>
#include <cassert>
#include <chrono>
#include <ctime>
#include <cstdlib>
#include <tuple> 
 
using namespace std::chrono;
using namespace std;

int UPingPongMerge(long long runs[], int runSize[]);

//to do: veranderen int naar Pile voor accepteren van runs

bool pairCompare(const pair<int, int> &firstElem, const pair<int, int> &secondElem) {
  return firstElem.second < secondElem.second;
}

int insertArray(long long elemArray[], long long pile[], int runSize, int nextEmptyArrayLoc) {
	for (int i = {nextEmptyArrayLoc}; i < runSize ; i++) {
		elemArray[i] = pile[i];
	}
	return 0;
}
// where first = runs[] and last = runs[] + sizeof(runs[])/sizeof(runs[0]) this only works when all runs are equally sized............... otherwise the number of runs needs to be stored seperately and passed
int UPingPongMerge(Iterator first, int numberOfRuns, int runSize[], const length)
{
	Iterator last;
	last = first + numberOfRuns;
	//initialize array with number of integers
	long long elems1[length];
	long long elems2[length];
	vector<pair<int, int>> runSizeRef;
	//fill array with index and sizes
	for(Iterator it = first; it != last; it++){
		long long& element = *it;
		runSizeRef.push_back(make_pair( element, runSize[it]));
	}

	//sort array ascending sizes
	sort(runSizeRef.begin(), runSizeRef.end(), pairCompare);

	int nextEmptyArrayLoc = {0};
	
	//still wrong insertarray and elemsrun
	vector<tuple<int,int,int>> elemsRun;
	// opmerking van Dylan: in C++ moet je sizeof gebruiken en dan krijg je byte size van de array, vervolgens wil je dit
	// delen door de size van een element in de array verder wil je wel de elements zelf in elems1 knallen
	for(int j = {0}; j < sizeof(runSizeRef)/sizeof(runSizeRef[0]); j++){
		copy(runs[j], runs[j] + runSize[j], elems1[nextEmptyArrayLoc]);
		elemsRun.push_back(make_tuple(1,nextEmptyArrayLoc,runSize[j]));
		nextEmptyArrayLoc += runSize[j];
	}
	
	tuple<int, int, int> curRun = elemsRun.front();
	int index = {0};
	while (elemsRun.size() > 1) {
		if (curRun || (get<2>(curRun) + get<2>()) > (get<2>(elemsRun.front()) + get<2>(elemsRun[1]))) {
			curRun = *elemsRun.front();
			index = 0;
		}
		if (get<0>(curRun) == 1) {
			//18 Blindly merge curRun and curRun’s next into Elems2
			//starting at element position curRun.ElemIndex
			get<0>(curRun) = 2;
		} else {
			//21 Blindly merge curRun and curRun’s next into Elems1
			//starting at element position curRun.ElemIndex
			get<0>(curRun) = 1;
		}
		get<2>(curRun) += get<2>(curRun);//add length next item
		index++;
		curRun.erase();

		//24 remove curRun’s next
		//25 curRun.MoveForward
		//26 if (ElemsRuns.First.RunIndex == 1) return Elems1
		//27 else return Elems2
	}

	

//16 if (curRun has no next) or
//(size of merging curRun and its next >
//size of merging the first and second runs)
//CurRun = ElemsRuns.IterateFromFirst
//17 if (curRun.ElemsArr == 1)
//18 Blindly merge curRun and curRun’s next into Elems2
//starting at element position curRun.ElemIndex
//19 curRun.ElemArr = 2
//20 else
//21 Blindly merge curRun and curRun’s next into Elems1
//starting at element position curRun.ElemIndex
//22 curRun.ElemArr = 1
//23 curRun.RunSize += curRun.Next.RunSize
//24 remove curRun’s next
//25 curRun.MoveForward
//26 if (ElemsRuns.First.RunIndex == 1) return Elems1
//27 else return Elems2


}
// 
//int main() {
//  long long unsorted[50000];
//  int length = sizeof(unsorted)/sizeof(long long);
//  std::srand(std::time(0));
//  int n;
//
//  for(n=0; n < length; n++)
//  {
//	  unsorted[n] = std::rand();
//  }
//  high_resolution_clock::time_point total1 = high_resolution_clock::now();
//  UPingPongMerge(unsorted, unsorted + length);
//  high_resolution_clock::time_point total2 = high_resolution_clock::now();
//  auto duration = duration_cast<microseconds>(total2-total1).count();
//  printf("\nTime needed for Total sorting: %d microseconds ", duration);

//  return 0;
//}