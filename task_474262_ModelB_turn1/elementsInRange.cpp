#include <iostream>
#include <vector>
#include <set>

using namespace std;

void findElementsInRange(const vector<int>& arr1, const vector<int>& arr2, int low, int high) {
    set<int> rangeSet(arr2.begin(), arr2.end());

    for (int value : arr1) {
        if (rangeSet.lower_bound(low) <= rangeSet.upper_bound(high)) {
            cout << value << " ";
        }
    }
}

int32_t main() {
    vector<int> arr1 = {1, 3, 5, 7, 9};
    vector<int> arr2 = {2, 5, 6, 8, 10, 12};
    int low = 5;
    int high = 8;

    cout << "Elements in arr1 present in the range [" << low << ", " << high << "] from arr2: ";
    findElementsInRange(arr1, arr2, low, high);
    cout << endl;

    return 0;
}
