#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>
#include <set>

using namespace std;

struct Boat {
	int ring;
	int length;
	int maxStartingPosition() {
		return ring + length;
	}
	int minStartingPosition() {
		return ring - length;
	}
};

set<int> pickedBoats;
bool compareBoats(Boat a, Boat b) {
	return (a.ring < b.ring);
}

void printBoats(Boat*, int);

int boats(void) {
/*int main(void) {*/
	int cases, wizards, optimalBoats, maxDistance;
	cin >> cases;
	for (int i = 0; i < cases; i++) {
		cin >> wizards;
		Boat* boats = new Boat[wizards];
		for (int j = 0; j < wizards; j++) {
			cin >> boats[j].length >> boats[j].ring;
		}
		sort(boats, boats + wizards, compareBoats);
		pickedBoats.clear();
		optimalBoats = 1;
		pickedBoats.insert(0);
		int currentDist = boats[0].minStartingPosition();
		int j = 1;
		bool noBoatsLeft = false;
		while (j < wizards && !noBoatsLeft) {

			if (boats[j].ring >= currentDist) {
				//there is a boat that can be placed
				optimalBoats++;
				//just get the minimum distance
				int nextDistance = INT_MAX;
				int k = j;
				int picked;
				while (k < wizards &&
						currentDist <= boats[k].ring &&
						boats[k].minStartingPosition() <= currentDist + boats[k].length &&
						pickedBoats.find(k) == pickedBoats.end()) {
					if (currentDist + boats[k].length < nextDistance) {
						picked = k;
						nextDistance = currentDist + boats[k].length;
						j = picked+1;
					}
					k++;
				}
				if (nextDistance != INT_MAX) {
					pickedBoats.insert(picked);
					currentDist = nextDistance;
				}
				cout << currentDist << "\n";
			} else {
				noBoatsLeft = true;
			}

		}
		cout << optimalBoats << "\n";
	}
	return 0;
}

void printBoats(Boat* boats, int size) {
	cout << "\nBoats: { ";
	for (int i = 0; i < size; ++i) {
		cout << "(" << boats[i].ring << "," << boats[i].length << ")";
	}
	cout << "}\n";
}
