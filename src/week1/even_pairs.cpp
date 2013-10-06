#include <iostream>

using namespace std;

int even_pairs(void) {
/*int main(void) {*/
	int dataset;
	cin >> dataset;
	int pairs = 0, current;
	int sumEven = 0;
	int sumOdd = 0;
	for (int i = 1; i <= dataset; i++) {
		cin >> current;
		switch(current) {
		case 0:
			pairs += sumEven + 1;
			sumEven++; 				//add (i,i) as new even sum
			break;
		case 1:
			pairs += sumOdd;		//all odd sums become even
			swap(sumEven, sumOdd);	//and all even sums become odd
			sumOdd++;				//add (i,i) as new odd sum
			break;
		}
	}
	cout << pairs;
	return 0;
}

void swap (int& a, int& b) {
	int aux = a;
	a = b;
	b = aux;
}
