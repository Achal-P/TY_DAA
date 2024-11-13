/*Develop a program to design a function for a Binary Search using Divide & Conquer strategies. Also compute its time complexity*/
#include <iostream>
using namespace std;

// Function to perform bubble sort on the array
void bubbleSort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap if the element is greater than the next element
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Function to perform binary search
int binarySearch(int arr[], int size, int target) {
    int left = 0;                     // Start index
    int right = size - 1;            // End index

    while (left <= right) {           // Continue while the range is valid
        int mid = left + (right - left) / 2;  // Calculate the middle index

        // Check if the middle element is the target
        if (arr[mid] == target) {
            return mid;               // Target found
        }
        else if (arr[mid] < target) {
            left = mid + 1;           // Search in the right half
        }
        else {
            right = mid - 1;          // Search in the left half
        }
    }
    return -1;                         // Target not found
}

int main() {
    const int MAX_SIZE = 100;         // Define the maximum size of the array
    int arr[MAX_SIZE];                // Array to hold the numbers
    int size = 0;                     // Actual number of elements in the array

    cout << "Enter the number of elements: ";
    cin >> size;                      // Get the number of elements

    cout << "Enter " << size << " unsorted numbers: ";
    for (int i = 0; i < size; i++) {
        cin >> arr[i];                // Read elements into the array
    }

    // Sort the array
    bubbleSort(arr, size);
    cout << "Sorted array: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";        // Print the sorted array
    }
    cout << endl;

    int target;
    cout << "Enter the number to search for: ";
    cin >> target;                    // Get the target number

    // Perform binary search
    int result = binarySearch(arr, size, target);

    // Output the result
    if (result != -1) {
        cout << "Number " << target << " found at index " << result << "." << endl;
    } else {
        cout << "Number " << target << " not found in the array." << endl;
    }

    return 0;
}
/*OUTPUT:
kkw@kkw-HP-Pro-Tower-280-G9-PCI-Desktop-PC:~/Desktop/TY_CSD_73$ g++ daaauto1.cpp
kkw@kkw-HP-Pro-Tower-280-G9-PCI-Desktop-PC:~/Desktop/TY_CSD_73$ ./a.out
Enter the number of elements: 5
Enter 5 unsorted numbers: 7
1
6
9
2
Sorted array: 1 2 6 7 9 
Enter the number to search for: 6
Number 6 found at index 2. */
