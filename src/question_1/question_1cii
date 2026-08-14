#include <iostream>
#include <vector>

// Merge two already-sorted parts of the array
void merge(std::vector<int>& arr, int left, int middle, int right) {
    // Temporary array used to hold the merged values
    std::vector<int> temp(right - left + 1);

    int i = left;         // index for the left half
    int j = middle + 1;   // index for the right half
    int k = 0;            // index for temp

    // Compare the current values from each half
    while (i <= middle && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k] = arr[i];
            i++;
        } else {
            temp[k] = arr[j];
            j++;
        }

        k++;
    }

    // Copy anything remaining from the left half
    while (i <= middle) {
        temp[k] = arr[i];
        i++;
        k++;
    }

    // Copy anything remaining from the right half
    while (j <= right) {
        temp[k] = arr[j];
        j++;
        k++;
    }

    // Copy the merged values back into the original array
    for (int x = 0; x < temp.size(); x++) {
        arr[left + x] = temp[x];
    }
}


// Merge Sort
void mergeSort(std::vector<int>& arr, int left, int right) {
    // Base case: one element or no elements
    if (left >= right) {
        return;
    }

    int middle = (left + right) / 2;

    // Sort the left half
    mergeSort(arr, left, middle);

    // Sort the right half
    mergeSort(arr, middle + 1, right);

    // Merge the two sorted halves
    merge(arr, left, middle, right);
}


int main() {
    std::vector<int> arr = {5, 2, 4, 6, 1, 3};

    std::cout << "Before sorting: ";

    for (int value : arr) {
        std::cout << value << " ";
    }

    // Sort the complete array
    mergeSort(arr, 0, arr.size() - 1);

    std::cout << "\nAfter sorting: ";

    for (int value : arr) {
        std::cout << value << " ";
    }

    std::cout << std::endl;

    return 0;
}
