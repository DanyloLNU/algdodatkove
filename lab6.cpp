#include <iostream>
#include <vector>
#include <random>
#include <chrono>

using namespace std;

void swap(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
}

int partition(vector<int>& arr, int l, int h)
{
    int pivot = arr[h]; // pivot
    int i = (l - 1);
    for (int j = l; j <= h - 1; j++) {

        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[h]);
    return (i + 1);
}

int RandomizedPartition(vector<int>& arr, int l, int h)
{
    int i = (rand() % (h - l + 1)) + l;
    swap(arr[h], arr[i]);
    return partition(arr, l, h);
}

int RandomizedSelect(vector<int>& arr, int l, int h, int k)
{
    if (l == h) {
        return arr[l];
    }

    int q = RandomizedPartition(arr, l, h);
    int leftSize = q - l + 1;

    if (k == leftSize) {
        return arr[q];
    }
    else if (k < leftSize) {
        return RandomizedSelect(arr, l, q - 1, k);
    }
    else {
        return RandomizedSelect(arr, q + 1, h, k - leftSize);
    }
}

void QuickSort(vector<int>& arr, int l, int h)
{
    if (l < h) {

        int p = partition(arr, l, h);

        QuickSort(arr, l, p - 1);
        QuickSort(arr, p + 1, h);
    }
}

int main()
{
    vector<int> arr;
    int n, x;
    cout << "Enter the number of elements: ";
    cin >> n;
    cout << "Enter " << n << " elements:\n";
    for (int i = 0; i < n; i++)
    {
        std::cin >> x;
        arr.push_back(x);
    }

    auto start = chrono::high_resolution_clock::now();
    int k = (n + 1) / 2;
    int median = RandomizedSelect(arr, 0, n - 1, k);
    auto end = chrono::high_resolution_clock::now();
    cout << "Median: " << median << endl;
    cout << "Time taken: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " microseconds" << endl;

    QuickSort(arr, 0, n - 1);
    cout << "Sorted array:\n";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << "\n";
    return 0;
}
