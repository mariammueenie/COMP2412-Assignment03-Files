#include <iostream>
#include <string>

class HashTable {
private:

    // Node used for separate chaining
    struct Node {
        std::string key;
        int value;
        Node* next;

        Node(const std::string& k, int v)
            : key(k), value(v), next(nullptr) {
        }
    };

    Node** table;

    int capacity;
    int numItems;

    const int MIN_CAPACITY = 4;


    // Custom hash func
    // Assignment keys = strings, so turn string into numeric key by adding  character vals
    // Then use modulo: hash = numericKey mod tableSize
    int hashFunction(
        const std::string& key,
        int tableSize
    ) const {

        unsigned long numericKey = 0;

        for (char c : key) {
            numericKey +=
                static_cast<unsigned char>(c);
        }

        return numericKey % tableSize;
    }


    // load factor = number of items / number of slots
    double loadFactor() const {
        return static_cast<double>(numItems)
               / capacity;
    }


    // Change table size, rehash everything
    void resize(int newCapacity) {
        if (newCapacity < MIN_CAPACITY) {
            newCapacity = MIN_CAPACITY;
        }

        Node** newTable =
            new Node*[newCapacity];

        for (int i = 0;
             i < newCapacity;
             i++) {

            newTable[i] = nullptr;
        }

        // Move all old node into NEW hash slot
        for (int i = 0;
             i < capacity;
             i++) {

            Node* current = table[i];

            while (current != nullptr) {

                // Save old node before changing pointer
                Node* nextNode =
                    current->next;

                int newIndex =
                    hashFunction(
                        current->key,
                        newCapacity
                    );

                // Add node to front of new chain
                current->next =
                    newTable[newIndex];

                newTable[newIndex] =
                    current;

                current = nextNode;
            }
        }

        delete[] table;

        table = newTable;
        capacity = newCapacity;

        std::cout
            << "Resized table to "
            << capacity
            << " slots.\n";
    }


public:

    HashTable() {
        capacity = MIN_CAPACITY;
        numItems = 0;

        table = new Node*[capacity];

        for (int i = 0;
             i < capacity;
             i++) {

            table[i] = nullptr;
        }
    }


    // Clean up linked nodes
    ~HashTable() {
        for (int i = 0;
             i < capacity;
             i++) {

            Node* current = table[i];

            while (current != nullptr) {

                Node* nextNode =
                    current->next;

                delete current;

                current = nextNode;
            }
        }

        delete[] table;
    }


    // Insert key/value pair
    void insert(
        const std::string& key,
        int value
    ) {

        int index =
            hashFunction(key, capacity);

        Node* current =
            table[index];

        // If key already exists just update value
        while (current != nullptr) {

            if (current->key == key) {
                current->value = value;

                return;
            }

            current = current->next;
        }

        // Otherwise make new node for chain
        Node* newNode =
            new Node(key, value);

        // Put new node at front of linked list
        newNode->next =
            table[index];

        table[index] =
            newNode;

        numItems++;

        // double if load > 0.75
        if (loadFactor() > 0.75) {
            resize(capacity * 2);
        }
    }


    // Search only linked list for hash
    bool search(
        const std::string& key,
        int& value
    ) const {

        int index =
            hashFunction(key, capacity);

        Node* current =
            table[index];

        while (current != nullptr) {

            if (current->key == key) {

                value =
                    current->value;

                return true;
            }

            current =
                current->next;
        }

        return false;
    }


    // "delete" is C++ keyword
    // so named function removeKey instead
    bool removeKey(
        const std::string& key
    ) {

        int index =
            hashFunction(key, capacity);

        Node* current =
            table[index];

        Node* previous =
            nullptr;

        while (current != nullptr) {

            if (current->key == key) {

                // Node first in chain
                if (previous == nullptr) {

                    table[index] =
                        current->next;
                }

                // Node somewhere after first
                else {

                    previous->next =
                        current->next;
                }

                delete current;

                numItems--;

                // half when load < 0.25
                while (
                    capacity > MIN_CAPACITY
                    && loadFactor() < 0.25
                ) {

                    resize(capacity / 2);
                }

                return true;
            }

            previous = current;
            current = current->next;
        }

        return false;
    }


    // Show all slots + linked list
    void display() const {

        std::cout
            << "\nHash table (capacity "
            << capacity
            << ", items "
            << numItems
            << "):\n";

        for (int i = 0;
             i < capacity;
             i++) {

            std::cout
                << "Slot "
                << i
                << ": ";

            Node* current =
                table[i];

            while (current != nullptr) {

                std::cout
                    << "("
                    << current->key
                    << ", "
                    << current->value
                    << ") -> ";

                current =
                    current->next;
            }

            std::cout << "NULL\n";
        }
    }
};


int main() {

    HashTable ht;

    // input sequence 
    ht.insert("Toyota", 300);
    ht.insert("Ford", 450);
    ht.insert("BMW", 400);
    ht.insert("Honda", 280);
    ht.insert("Chevrolet", 500);
    ht.insert("Tesla", 670);
    ht.insert("Porsche", 620);
    ht.insert("Lamborghini", 770);
    ht.insert("Ferrari", 800);
    ht.insert("McLaren", 750);
    ht.insert("Bugatti", 1500);
    ht.insert("AstonMartin", 630);

    ht.display();


    // Test search
    int value = 0;

    std::cout
        << "\nSearching for Tesla...\n";

    if (ht.search("Tesla", value)) {

        std::cout
            << "Tesla found with value "
            << value
            << "\n";
    }
    else {

        std::cout
            << "Tesla not found.\n";
    }


    // Test delete
    std::cout
        << "\nDeleting BMW...\n";

    ht.removeKey("BMW");

    ht.display();


    // Delete enough vals to show shrink working
    std::cout
        << "\nDeleting more values to test shrinking...\n";

    ht.removeKey("Toyota");
    ht.removeKey("Ford");
    ht.removeKey("Honda");
    ht.removeKey("Chevrolet");
    ht.removeKey("Tesla");
    ht.removeKey("Porsche");
    ht.removeKey("Lamborghini");
    ht.removeKey("Ferrari");

    ht.display();

    return 0;
}
