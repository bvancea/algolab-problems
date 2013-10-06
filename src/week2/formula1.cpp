#include <iostream>
#include <queue>

using namespace std;
int inversions = 0;

int* mergeSort(int*, int, int);
int* combine(int*, int, int*, int);
void printArray(int* array, int size);

/*int main(void) {*/
int formula1(void) {
	int cases;
	cin >> cases;

	for (int i = 0; i < cases; i++) {
		int racers;
		cin >> racers;
		int *position = new int[racers];
		for (int j = 0; j < racers; j++) {
			cin >> position[j];
		}
		inversions = 0;
		mergeSort(position, 0, racers-1);
		//printArray(awesome, racers);
		cout << inversions << "\n";
	}
	return 0;
}

int* mergeSort(int* array, int start, int end) {
	if (start == end) {
		int* result =  new int[1];
		result[0] = array[start];
		return result;
	}
	int pivot = start + (end - start) / 2;
	int* left = mergeSort(array, start, pivot);
	int* right = mergeSort(array, pivot + 1, end);
	return combine(left, pivot - start + 1, right, end-pivot);
}

int* combine(int* left, int sizeLeft, int* right, int sizeRight) {
	int* result = new int[sizeLeft + sizeRight];
	int j = 0;

	for (int i = 0 ; i < sizeLeft; i++) {
		while (left[i] > right[j] && j < sizeRight) {
			inversions += sizeLeft - i;
			result[i + j] = right[j];
			j++;
		}
		result[i + j] = left[i];
	}

	while(j < sizeRight) {
		result[sizeLeft + j] = right[j];
		j++;
	}

	inversions = inversions % 10000;
	return result;
}

void printArray(int* array, int size) {
	cout << "\n Array: ";
	for (int i = 0; i < size; i++) {
		cout << array[i] << " ";
	}
	cout << "\n";
}
