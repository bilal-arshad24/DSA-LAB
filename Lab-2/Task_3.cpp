#include<iostream>
using namespace std;
template <typename T, int N>
int linearSearch(T(&arr)[N],T value) {
	for (int i = 0; i < N; i++) {
		if (arr[i] == value)
			return (int) i ;
	}
	return -1;
}
template<typename T>
void printSearchResult(int index, T key) {
	if (index == -1)
		cout << key << " not found in the array. " << endl;
	else
		cout << key << " found at index " << index << endl;
}

int main() {
	int intarray[5] = { 64,25,12,22,11 };
	int intkey = 12;
	int intindex = linearSearch(intarray, intkey); 
	printSearchResult(intindex, intkey);

	float floatarray[4] = { 3.14, 2.71, 1.62, 0.57 };
	float floatkey = 1.62;
	float floatindex = linearSearch(floatarray, floatkey);
	printSearchResult(floatindex, floatkey);

	string stringArray[4] = { "apple", "orange", "banana", "grape" };
	string stringKey = "banana";
	int stringIndex = linearSearch(stringArray, stringKey);
	printSearchResult(stringIndex, stringKey);

	return 0;

}