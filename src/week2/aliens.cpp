#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Interval {
	int start;
	int end;
	int distance;
	Interval(int start = 0, int end = 0, int distance = 0) : start(start), end(end), distance(distance) {	};
	bool containedWithin(const Interval& i) {
		return (start >= i.start && end <= i.end);
	}
	Interval& operator=(const Interval& i) {
		start = i.start;
		end = i.end;
		distance = i.distance;
		return *this;
	}
	bool operator==(const Interval& i) {
		return start == i.start && end == i.end;
	}
};
bool* humans;
bool intervalCompare(Interval a, Interval b);
void tryAddChampion(Interval candidate, vector<Interval>& champions, vector<Interval>& aliens);
bool allHumansDown(int humansNr);
void removeDuplicates(vector<Interval>& aliens, Interval duplicate, vector<Interval>& champions);
void killHumans(Interval interval);
bool containedWithin(Interval candidate, vector<Interval>& champions);

int aliens(void) {
/*int main(void) {*/
	int cases;
	cin >> cases;
	int nrAliens, nrHumans;
	vector<Interval> aliens;
	vector<Interval> champions;

	for (int i = 0; i < cases; i++) {
		cin >> nrAliens >> nrHumans;
		int start, end;
		aliens.clear();
		champions.clear();
		humans = new bool[nrHumans + 1];
		for (int j = 0; j < nrAliens; j++) {
			cin >> start >> end;
			if (start != 0 && end != 0) {
				aliens.push_back(Interval(start, end, end-start));
			}
		}
		sort(aliens.begin(), aliens.end(), intervalCompare);

		while (aliens.size() > 0) {
			Interval current = aliens.back();
			aliens.pop_back();
			tryAddChampion(current,champions, aliens);
		}

/*		cout << champions.size() << "\n";*/
		if (!allHumansDown(nrHumans)) {
			cout << 0 << "\n";
		} else {
			cout << champions.size() << "\n";
		}

		delete [] humans;
	}
	return 0;
}

bool intervalCompare(Interval a, Interval b) {
	return ((a.distance == b.distance) && (a.start < b.start )) ||
			( a.distance < b.distance);
}

bool containedWithin(Interval candidate, vector<Interval>& champions) {
	bool contained = false;
	for (vector<Interval>::iterator it = champions.begin(); it != champions.end(); it++) {
		if (candidate.containedWithin(*it)) {
			contained = true;
			break;
		}
	}
	return contained;
}

void tryAddChampion(Interval candidate, vector<Interval>& champions, vector<Interval>& aliens) {

	if (!containedWithin(candidate,champions)) {
		killHumans(candidate);
		if (aliens.size() > 0 && aliens.back() == candidate) {
			removeDuplicates(aliens, candidate, champions);
		} else {
			champions.push_back((candidate));
			/*killHumans(candidate);*/
		}
	} else {
		removeDuplicates(aliens, candidate, champions);
	}
}

void killHumans(Interval interval) {
	for (int i = interval.start; i <= interval.end; i++) {
		humans[i] = true;
	}
}

bool allHumansDown(int humansNr) {
	bool allDown = true;
	for (int i = 1; i <= humansNr; i++) {
		allDown = allDown && humans[i];
	}
	return allDown;
}

void removeDuplicates(vector<Interval>& aliens, Interval duplicate, vector<Interval>& champions) {
	while (aliens.size() > 0  && aliens.back() == duplicate) {
		aliens.pop_back();
	}
}
