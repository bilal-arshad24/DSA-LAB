#include<iostream>
using namespace std;
template <typename T,int N>
void printarray(T(&arr)[N]) {
	for (int i = 0; i < N; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}
template<typename T,int N>
void selectionSort(T(&A)[N]) {
	for (int i = 0; i + 1< N; i++) {
		int smallsub = i;
		for (int j = i + 1; j < N; j++) {
			if (A[j] < A[smallsub])
				smallsub = j;
		}
		T temp = A[i];
		A[i] = A[smallsub];
		A[smallsub] = temp;
	}
}
int main() {
	int intarray[5] = { 64,25,12,22,11 };
	cout << "original integer array = ";
	printarray(intarray);
	selectionSort(intarray);
	cout << "sorted integer array = ";
	printarray(intarray);
	cout << endl;
	string stringarray[4] = { "apple","orange","banana","grape" };
	cout << "original string array = ";
	printarray(stringarray);
	selectionSort(stringarray);
	cout << "sorted string array = ";
	printarray(stringarray);
	cout << endl;
	return 0;
}