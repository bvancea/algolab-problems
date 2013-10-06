#include <iostream>
#include <cstring>

using namespace std;

int* coinTable = new int[101];

int false_coint(void) {
/*int main(void) {*/

	int cases, coins, weightings;
	int coinsPerSide;
	int *left, *right;
	char weightingResult;

	cin >> cases;
	for (int i = 0; i < cases; i++) {
		cin >> coins;
		cin >> weightings;
		memset(coinTable, 0, (coins + 1) * sizeof (int));

		for (int j = 0; j < weightings; j++) {
			cin >> coinsPerSide;
			left = new int[coinsPerSide];
			right = new int[coinsPerSide];
			for (int k = 0; k < coinsPerSide; k++) {
				cin >> left[k];
			}
			for (int k = 0; k < coinsPerSide; k++) {
				cin >> right[k];
			}
			cin >> weightingResult;
			switch (weightingResult) {
				case '<':
					break;
				case '>':
					break;
				case '=':
					for (int k = 0; k < coinsPerSide; k++) {
						coinTable[left[k]] = 1;
						coinTable[right[k]] = 1;
					}
					break;
			}

		}

		int different = -1;
		int differentNumber = 0;
		for (int k = 1; k < coins + 1; k++) {
			if (coinTable[k] == 0 ) {
				different = k;
				differentNumber++;
			}
		}
		if (differentNumber > 1) {
			cout << '0' << "\n";
		} else {
			cout << different << "\n";
		}
	}
	return 0;
}


