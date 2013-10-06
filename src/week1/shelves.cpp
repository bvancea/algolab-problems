#include <iostream>
#include <cmath>
#include <climits>

using namespace std;
void computeBest(long long l, long long m, long long n);
void startFromA(long long l, long long m, long long n);
void startFromB(long long l, long long m, long long n);

long long bestA, bestB, bestR;

int shelves(void) {
/*int main(void) {*/
	long long cases;
	long long m,n,l;
	cin >> cases;
	for (long long i = 0; i < cases; i++) {
		cin >> l >> m >> n;
		bestA = bestB = 0;
		bestR = l;
		computeBest(l, m, n);
		cout << bestA << " " << bestB << " " << bestR << "\n";
	}
	return 0;
}

void computeBest(long long l, long long m, long long n) {
	if (m == n || m > l) {
		bestA = 0;
		bestB = l / n;
		bestR = l % n;
		return;
	} else if (n > l) {
		bestA = l / m;
		bestB = 0;
		bestR = l % m;
		return;
	}

	if ( n > sqrt(l)) {
		startFromB(l, m, n);
	} else {
		startFromA(l, m, n);
	}
}

void startFromA(long long l, long long m, long long n) {
	long long a,b,r;
	long long maxL = sqrt(l);
	for (long long i = maxL; i >= 0; i--) {
		a = i;
		b = (l - m * a)/n;
		r =  (l - n * b - a*m);
		if (a >= 0 && r >= 0) {
			if ((r < bestR) || (r <= bestR && b > bestB)) {
				bestA = a;
				bestB = b;
				bestR = r;
			}
		}
	}
}

void startFromB(long long l, long long m, long long n) {
	long long a, b,r;
	long long maxL = sqrt(l);
	for (long long i = maxL; i >= 0l; i--) {
		b = i;
		a = (l - n * b)/m;
		r =  (l - n * b - a*m);
		if (a >= 0 && r >= 0) {
			if ((r < bestR) || (r <= bestR && b > bestB)) {
				bestA = a;
				bestB = b;
				bestR = r;
			}
		}
	}
}
