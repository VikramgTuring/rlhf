#include <iostream>
#include <vector>
#include <set>

using namespace std;

void findCommonElements(const vector<int>& arr1, const vector<int>& arr2) {
    set<int> set2(arr2.begin(), arr2.end());

    for (int value : arr1) {
        if (set2.find(value) != set2.end()) {
            cout << value << " ";
        }
    }
}

int32_t main() {
    vector<int> arr1 = {1, 2, 3, 4, 5};
    vector<int> arr2 = {3, 4, 5, 6, 7};

    cout << "Common elements between arr1 and arr2: ";
    findCommonElements(arr1, arr2);
    cout << endl;

    return 0;
}
