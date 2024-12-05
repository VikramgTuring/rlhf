#include <iostream>
#include <vector>

using namespace std;

template <typename BidirectionalIterator>
void bidirectionalTraversal(BidirectionalIterator first, BidirectionalIterator last) {
    cout << "Forward Traversal: " << endl;
    while (first != last) {
        cout << *first << " -> ";
        ++first;
    }
    cout << "<end>" << endl;

    cout << "Backward Traversal: " << endl;
    while (first != last--) {
        cout << *first << " <- ";
    }
    cout << *first << " <start>" << endl;
}

int main() {
    vector<int> data = { 1, 2, 3, 4, 5 };

    auto it = data.begin();
    bidirectionalTraversal(it, data.end());

    return 0;
}