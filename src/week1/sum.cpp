#include <iostream>

using namespace std;

int sum(void) {
/*int main(void) {*/
	int cases;
	int terms;
	double sum;
	double current;
	cin >> cases;
	for (int i = 0; i < cases; i++) {
		cin >> terms;
		sum = 0;
		for (int j = 0; j < terms; j++) {
			cin >> current;
			sum += current;
		}
		cout << sum << endl;
	}
	return 0;
}
