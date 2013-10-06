#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <set>
#include <climits>

#define MAX_SIZE 10000

using namespace std;

set<int>* edges;

void diameter(int root, int parent, int& diameter, int& height);

int longest_path(void) {
/*int main(int argc, char **argv) {*/

	int cases, nrEdges, a, b, d,h;
	cin >> cases;

	for (int i = 0; i < cases; i++) {

		cin >> nrEdges;
		edges = new set<int>[nrEdges];
		for (int j = 0; j < nrEdges - 1; j++) {
			cin >> a >> b;
			pair<int, int> edge(a,b);
			edges[a].insert(b);
			edges[b].insert(a);
		}

		int j;
		for (j = 0; j < nrEdges && edges[j].size() < 2; j++);
		diameter(j, -1, d, h);
		cout << d << "\n";

	}

	return 0;
}

void diameter(int root, int parent, int& diam, int& height) {

	int maxDiameter,maxHeight, secondMaxHeight;
	maxDiameter = 1;
	maxHeight = secondMaxHeight = 0;

	int currentDiameter, currentHeight;
	for (set<int>::iterator it = edges[root].begin(); it != edges[root].end(); ++it) {
		if (*it != parent) {
			diameter(*it, root, currentDiameter, currentHeight);
			maxDiameter = max(maxDiameter, currentDiameter);
			if (currentHeight > maxHeight) {
				secondMaxHeight = maxHeight;
				maxHeight = currentHeight;
			} else if (currentHeight > secondMaxHeight) {
				secondMaxHeight = currentHeight;
			}
		}

	}

	diam = max(maxDiameter, maxHeight + secondMaxHeight + 1);
	height = maxHeight + 1;
}

