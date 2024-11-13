/*Develop a program to implement concurrent quick sort using divide and conquer approach*/
#include <iostream>
#include <vector>
#include <thread>
#include <algorithm> // For std::swap

using namespace std;

// Class to perform Concurrent Quick Sort
class ConcurrentQuickSort {
public:
    // Constructor to initialize the array
    ConcurrentQuickSort(vector<int>& arr) : arr(arr) {}

    // Public method to start concurrent quick sort
    void sort() {
        concurrentQuickSort(0, arr.size() - 1);
    }

    // Method to display the sorted array
    void display() const {
        for (int num : arr) {
            cout << num << " ";
        }
        cout << endl;
    }

private:
    vector<int>& arr; // Reference to the array to be sorted

    // Partition function used in quick sort
    int partition(int low, int high) {
        int pivot = arr[high]; // Choose the last element as the pivot
        int i = low - 1; // Index of smaller element

        for (int j = low; j < high; j++) {
            if (arr[j] < pivot) {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        return i + 1; // Return the partition index
    }

    // Recursive concurrent quick sort function
    void concurrentQuickSort(int low, int high) {
        if (low < high) {
            int pi = partition(low, high); // Partition index

            // Calculate the left and right limits for each partition
            int leftHigh = pi - 1;
            int rightLow = pi + 1;

            // Launch two threads to sort the left and right subarrays concurrently
            thread leftThread([this, low, leftHigh]() { concurrentQuickSort(low, leftHigh); });
            thread rightThread([this, rightLow, high]() { concurrentQuickSort(rightLow, high); });

            // Wait for both threads to complete
            leftThread.join();
            rightThread.join();
        }
    }
};

int main() {
    int n;

    // Input: number of elements
    cout << "Enter the number of elements: ";
    cin >> n;

    vector<int> arr(n);

    // Input: elements of the array
    cout << "Enter the elements: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    // Instantiate the ConcurrentQuickSort class with the input array
    ConcurrentQuickSort sorter(arr);

    // Perform concurrent quick sort
    sorter.sort();

    // Output: sorted array
    cout << "Sorted array: ";
    sorter.display();

    return 0;
}
/*OUTPUT:
Enter the number of elements: 7
Enter the elements: 0
9
5
7
6
3
1
Sorted array: 0 1 3 5 6 7 9 */
