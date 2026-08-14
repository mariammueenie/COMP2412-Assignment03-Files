#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

class MinHeap {
private:
    // Leave position 0 unused so heap math is simple:
    // parent = i/2
    // left child = 2*i
    // right child = 2*i+1
    std::vector<int> heap;

    int parent(int i) {
        return i / 2;
    }

    int left(int i) {
        return 2 * i;
    }

    int right(int i) {
        return 2 * i + 1;
    }

    // Fix heap order going downward after removing root
    void heapifyDown(int i) {
        while (true) {
            int l = left(i);
            int r = right(i);
            int smallest = i;

            if (l < static_cast<int>(heap.size())
                && heap[l] < heap[smallest]) {
                smallest = l;
            }

            if (r < static_cast<int>(heap.size())
                && heap[r] < heap[smallest]) {
                smallest = r;
            }

            // Already in correct position
            if (smallest == i) {
                break;
            }

            std::swap(heap[i], heap[smallest]);
            i = smallest;
        }
    }

public:
    MinHeap() {
        // unused location so root is heap[1]
        heap.push_back(0);
    }

    bool empty() const {
        return heap.size() == 1;
    }

    // Insert at end then bubble up if needed
    void insert(int value) {
        heap.push_back(value);

        int i = static_cast<int>(heap.size()) - 1;

        while (i > 1 && heap[i] < heap[parent(i)]) {
            std::swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

    // Smallest val is always at root of min heap
    int getMin() const {
        if (empty()) {
            return -1;
        }

        return heap[1];
    }

    // Remove minimum/root
    int extractMin() {
        if (empty()) {
            return -1;
        }

        int minValue = heap[1];

        // Move last element to root
        heap[1] = heap.back();
        heap.pop_back();

        // Fix heap going downward
        if (!empty()) {
            heapifyDown(1);
        }

        return minValue;
    }
};


// Just printing first 30 so output isnt 1000 nums long
void printFirst(const std::vector<int>& values, int amount) {
    int limit = static_cast<int>(values.size());

    if (amount < limit) {
        limit = amount;
    }

    for (int i = 0; i < limit; i++) {
        std::cout << values[i] << " ";
    }

    std::cout << "\n";
}


// Check result really is in ascending order
bool isSorted(const std::vector<int>& values) {
    for (int i = 1;
         i < static_cast<int>(values.size());
         i++) {

        if (values[i - 1] > values[i]) {
            return false;
        }
    }

    return true;
}


int main() {
    const int SIZE = 1000;

    std::vector<int> numbers;

    std::srand(std::time(nullptr));

    // Assignment asks for array of 1000 random vals
    for (int i = 0; i < SIZE; i++) {
        numbers.push_back(std::rand() % 10000);
    }

    std::cout << "Generated "
              << SIZE
              << " random values.\n";

    std::cout << "First 30 before sorting: ";

    printFirst(numbers, 30);

    MinHeap heap;

    // Add all 1000 nums to min heap
    for (int value : numbers) {
        heap.insert(value);
    }

    // Test getMin
    std::cout << "Minimum value in heap: "
              << heap.getMin()
              << "\n";

    // extractMin repeatedly gives us vals smallest -> largest
    std::vector<int> sorted;

    while (!heap.empty()) {
        sorted.push_back(heap.extractMin());
    }

    std::cout << "First 30 after sorting:  ";

    printFirst(sorted, 30);

    std::cout << "Sorted correctly: "
              << (isSorted(sorted) ? "yes" : "no")
              << "\n";

    return 0;
}
