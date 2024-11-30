#include <iostream>
#include <stdexcept>

template<typename T>
class GenericArray {
private:
    T* data;
    int currentSize;

    void copyArray(T* source, T* dest, int size) const {
        for (int i = 0; i < size; i++) {
            dest[i] = source[i];
        }
    }

public:
    GenericArray() : data(nullptr), currentSize(0) {}
    
    ~GenericArray() {
        delete[] data;
    }

    // Add element to the end of array
    void addElement(T element) {
        T* newData = new T[currentSize + 1];
        
        if (data != nullptr) {
            copyArray(data, newData, currentSize);
            delete[] data;
        }
        
        newData[currentSize] = element;
        data = newData;
        currentSize++;
    }

    // Get element at specific index
    T at(int index) const {
        if (index < 0 || index >= currentSize) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[index];
    }

    // Get current size of array
    int size() const {
        return currentSize;
    }

    // Calculate sum of all elements
    T sum() const {
        if (currentSize == 0) {
            throw std::runtime_error("Cannot calculate sum of empty array");
        }
        
        T total = data[0];
        for (int i = 1; i < currentSize; i++) {
            total += data[i];
        }
        return total;
    }

    // Find maximum element
    T max() const {
        if (currentSize == 0) {
            throw std::runtime_error("Cannot find maximum of empty array");
        }
        
        T maxVal = data[0];
        for (int i = 1; i < currentSize; i++) {
            if (data[i] > maxVal) {
                maxVal = data[i];
            }
        }
        return maxVal;
    }

    // Find minimum element
    T min() const {
        if (currentSize == 0) {
            throw std::runtime_error("Cannot find minimum of empty array");
        }
        
        T minVal = data[0];
        for (int i = 1; i < currentSize; i++) {
            if (data[i] < minVal) {
                minVal = data[i];
            }
        }
        return minVal;
    }

    // Get slice of array from begin to end (inclusive)
    T* slice(int begin, int end) const {
        if (begin < 0 || begin >= currentSize || 
            end < 0 || end >= currentSize || 
            begin > end) {
            throw std::out_of_range("Invalid slice range");
        }

        int sliceSize = end - begin + 1;
        T* slicedArray = new T[sliceSize];
        copyArray(data + begin, slicedArray, sliceSize);
        return slicedArray;
    }
};

// Example usage in main function
int main() {
    GenericArray<int> int_array;
    
    // Add some elements
    int_array.addElement(10);
    int_array.addElement(5);
    int_array.addElement(8);
    int_array.addElement(15);
    int_array.addElement(3);
    int_array.addElement(12);
    int_array.addElement(7);
    int_array.addElement(9);
    int_array.addElement(4);
    int_array.addElement(6);
    
    // Test basic operations
    std::cout << "Size of array: " << int_array.size() << std::endl;
    std::cout << "Sum of array: " << int_array.sum() << std::endl;
    std::cout << "Maximum: " << int_array.max() << std::endl;
    std::cout << "Minimum: " << int_array.min() << std::endl;
    
    // Test at() function
    std::cout << "Element at index 3: " << int_array.at(3) << std::endl;
    
    // Test slice function
    try {
        int* sliced_array = int_array.slice(5, 8);
        std::cout << "Sliced array elements: ";
        for (int i = 0; i <= (8-5); i++) {
            std::cout << sliced_array[i] << " ";
        }
        std::cout << std::endl;
        
        // Don't forget to delete the dynamically allocated slice
        delete[] sliced_array;
    }
    catch (const std::out_of_range& e) {
        std::cout << "Slice error: " << e.what() << std::endl;
    }
    
    return 0;
}
