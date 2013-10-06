#include <iostream>
#include <algorithm>
#include <cstring>
#include <climits>

#define MAX_CURRENCY_VALUE 10000

using namespace std;

int change(int currency, int* coins, int coinsSize, int* memTable);
void initializeMemtable(int* memTable);

int checking_change(void) {
/*int main(void) {*/
	int cases, samples, coinsSize, current, *coins;
	int* memTable = new int[MAX_CURRENCY_VALUE];
	cin >> cases;
	for	(int i = 0; i < cases; i++) {
		cin >> coinsSize >> samples;
		coins = new int[coinsSize];
		for (int j = 0; j < coinsSize; j++) {
			cin >> coins[j];
		}
		initializeMemtable(memTable);
		for (int j = 0; j < samples; j++) {
			cin >> current;
			int minChange = change(current, coins, coinsSize, memTable);
			if (minChange == INT_MAX) {
				cout << "not possible\n";
			} else {
				cout << minChange << "\n";
			}
		}

	}
	return 0;
}

int change(int currency, int* coins, int coinsSize, int* memTable) {
	if (currency == 0 ) return 0;
	if (currency < 0) return INT_MAX;
	int minCoins = INT_MAX;
	int memoized = memTable[currency];
	if (memoized != INT_MAX) {
		return memoized;
	} else {
		for (int i = coinsSize - 1; i >= 0; i--) {
			if (currency - coins[i] >= 0) {
				int candidateMin = change((currency - coins[i]), coins, coinsSize, memTable );
				if (candidateMin != INT_MAX) {
					candidateMin++;
				}
				minCoins = min(minCoins,candidateMin);
			}
		}
		memTable[currency] = minCoins;

	}
	return minCoins;
}

void initializeMemtable(int* memTable) {
	for (int i = 0; i < MAX_CURRENCY_VALUE; i++) {
		memTable[i] = INT_MAX;
	}
}
