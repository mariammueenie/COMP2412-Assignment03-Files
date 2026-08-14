#include <iostream>
#include <vector>

void insertionSort(std::vector<int>& arr) {
    for (int i = 1; i < arr.size(); i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && key < arr[j]) {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}

int main() {
    std::vector<int> arr = {5, 2, 4, 6, 1, 3};

    std::cout << "Before sorting: ";
    for (int value : arr) {
        std::cout << value << " ";
    }

    insertionSort(arr);

    std::cout << "\nAfter sorting: ";

    for (int value : arr) {
        std::cout << value << " ";
    }

    std::cout << std::endl;

    return 0;
}
