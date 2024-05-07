#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool comparePairs(vector<int>& arr1, vector<int>& arr2) {
    return arr1[1] < arr2[1];
}

int main() {
    vector<vector<int>> arrs = {{2, 5}, {1, 3}, {3, 7}, {2, 1}, {4, 9}};

    sort(arrs.begin(), arrs.end(), comparePairs);

    cout << "Sorted pairs based on the first element:" << endl;
    for (auto& arr : arrs) {
        cout << arr[0] << ", " << arr[1] << endl;
    }

    return 0;
}
