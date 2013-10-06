#include <iostream>
#include <map>

#define MAX_COINS 1001

using namespace std;

int pickCoins(int* coins, int start, int end);

map<pair<int, int>, int> memo;

int main(int argc, char **argv) {
	int cases, coinsNr;
	int* coins;

	cin >> cases;

	for (int i = 0; i < cases; i++) {
		cin >> coinsNr;
		coins = new int[coinsNr];
		memo.clear();
		for (int j = 0; j < coinsNr; j++) {
			cin >> coins[j];
		}

		int maxGain = pickCoins(coins, 0, coinsNr -1);
		cout << maxGain << "\n";
		delete [] coins;

	}
	return 0;
}

int pickCoins(int* coins, int start, int end) {
	int maxGain = 0;
	pair<int, int> p(start, end);
	if (memo.find(p) != memo.end() ) {
		maxGain = memo.find(p)->second;
	} else if (start == end) {
		maxGain = coins[start];
	} else if (end == start + 1) {
		maxGain =  max(coins[start], coins[end]);
	} else {
		int pickFirst = coins[start] + min(pickCoins(coins, start+2, end), pickCoins(coins, start+1, end-1));
		int pickLast = coins[end] + min(pickCoins(coins, start, end-2), pickCoins(coins, start+1, end-1));
		maxGain = max(pickFirst, pickLast);
	}
	pair< pair<int, int>, int > saved(p, maxGain);
	memo.insert(saved);
	return maxGain;
}





