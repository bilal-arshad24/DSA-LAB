#include <iostream>
#include <string>
using namespace std;

template <typename T>
int search(T A[], int size, T key) {

    int low = 0;
    int high = size - 1;

    while (low <= high) {

        int mid = (low + high) / 2;

        if (A[mid] == key) {
            return mid;
        }
        else if (A[mid] < key) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }

    return -1;
}

template <typename T>
void result(int index, T key) {

    if (index != -1) {
        cout << "Found " << key << " at index: "
             << index << endl;
    }
    else {
        cout << key << " not found" << endl;
    }
}

int main() {

    int intArray[5] = {11, 12, 22, 25, 64};
    int intKey = 22;

    int intIndex = search(intArray, 5, intKey);
    result(intIndex, intKey);


    float floatArray[4] = {0.57, 1.62, 2.71, 3.14};
    float floatKey = 2.71;

    int floatIndex = search(floatArray, 4, floatKey);
    result(floatIndex, floatKey);


    string stringArray[4] = {
        "apple",
        "banana",
        "grape",
        "orange"
    };

    string stringKey = "grape";

    int stringIndex = search(stringArray, 4, stringKey);
    result(stringIndex, stringKey);

    return 0;
}