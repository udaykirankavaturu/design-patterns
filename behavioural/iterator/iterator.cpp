#include <iostream>
#include <string>
using namespace std;

// Abstract Iterator interface first
class Iterator {
public:
    virtual bool hasNext() = 0;
    virtual int next() = 0;
    virtual ~Iterator() = default;
};

// Collection class next - since iterators will need to reference it
class NumberCollection {
private:
    int numbers[10];
    int size;
    
public:
    // Constructor
    NumberCollection() : size(0) {}
    
    // Add number to collection
    void addNumber(int num) {
        if (size < 10) {
            numbers[size] = num;
            size++;
        }
    }
    
    // Getter methods
    int getSize() const {
        return size;
    }
    
    int getNumber(int index) const {
        if (index >= 0 && index < size) {
            return numbers[index];
        }
        return -1;
    }
    
    // Iterator creation methods - will be defined after iterator classes
    Iterator* createForwardIterator();
    Iterator* createReverseIterator();
};

// Forward Iterator implementation
class ForwardIterator : public Iterator {
private:
    const NumberCollection* collection;
    int currentIndex;
    
public:
    // Constructor
    ForwardIterator(const NumberCollection* nc) : 
        collection(nc), currentIndex(0) {}
    
    // Check if there are more elements
    bool hasNext() override {
        return currentIndex < collection->getSize();
    }
    
    // Get next element
    int next() override {
        if (hasNext()) {
            return collection->getNumber(currentIndex++);
        }
        return -1;
    }
};

// Reverse Iterator implementation
class ReverseIterator : public Iterator {
private:
    const NumberCollection* collection;
    int currentIndex;
    
public:
    // Constructor
    ReverseIterator(const NumberCollection* nc) : 
        collection(nc), currentIndex(nc->getSize() - 1) {}
    
    // Check if there are more elements
    bool hasNext() override {
        return currentIndex >= 0;
    }
    
    // Get next element
    int next() override {
        if (hasNext()) {
            return collection->getNumber(currentIndex--);
        }
        return -1;
    }
};

// Now define the iterator creation methods for NumberCollection
Iterator* NumberCollection::createForwardIterator() {
    return new ForwardIterator(this);
}

Iterator* NumberCollection::createReverseIterator() {
    return new ReverseIterator(this);
}

int main() {
    // Create a collection and add some numbers
    NumberCollection numbers;
    numbers.addNumber(1);
    numbers.addNumber(2);
    numbers.addNumber(3);
    numbers.addNumber(4);
    numbers.addNumber(5);
    
    // Demonstrate forward iteration
    cout << "Forward iteration: ";
    Iterator* forwardIt = numbers.createForwardIterator();
    while (forwardIt->hasNext()) {
        cout << forwardIt->next() << " ";
    }
    cout << endl;
    
    // Demonstrate reverse iteration
    cout << "Reverse iteration: ";
    Iterator* reverseIt = numbers.createReverseIterator();
    while (reverseIt->hasNext()) {
        cout << reverseIt->next() << " ";
    }
    cout << endl;
    
    // Clean up
    delete forwardIt;
    delete reverseIt;
    
    return 0;
}