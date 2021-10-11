#ifndef LAB2VAR27_ARRAYSEQUENCE_H
#define LAB2VAR27_ARRAYSEQUENCE_H

#include <iostream>
#include "Sequence.h"
#include "DynamicArray.h"
using namespace std;

template<typename T>
class ArraySequence : public Sequence<T> {

private:
    DynamicArray<T> mass;

public:
    //Constructors
    ArraySequence() : mass(0) {}

    ArraySequence(T* data, int count) : mass(data, count) {}

    ArraySequence(DynamicArray<T>& mass) : mass(mass) {}


    //Decomposition
    T& GetFirst() {
        return this->mass[0];
    }

    T& GetLast() {
        return this->mass[this->mass.GetSize() - 1];
    }

    T& operator[](int index) const {
        return this->mass[index];
    }

    Sequence<T>* GetSubSequence(int start_index, int end_index) {
        ArraySequence<T>* res = new ArraySequence<T>();
        for (int i = start_index; i < end_index; i++) {
            res->Append(mass[i]);
        }
        return res;
    }

    int GetLength() const {
        return this->mass.GetSize();
    }

    //Operations
    void Append(const T& value) {
        int size = this->mass.GetSize();
        this->mass.Resize(size + 1);
        this->mass[size] = value;
    }

    void Prepend(const T& value) {
        this->InsertAt(value, 0);
    }

    void InsertAt(const T& value, int index) {
        int size = this->mass.GetSize();
        if (index < 0 || index > size)
            throw std::out_of_range("Index out of range");
        this->mass.Resize(size + 1);
        for (int i = size; i > index; i--)
            this->mass[i] = this->mass[i - 1];
        this->mass[index] = value;
    }

    Sequence<T>* Concat(const Sequence<T>& seq) {
        ArraySequence<T>* res = new ArraySequence<T>(this->mass);
        for (int i = 0; i < seq.GetLength(); i++) {
            res->Append(seq[i]);
        }
        return res;
    }

    void Print() {
        for (int i = 0; i < this->GetLength(); ++i) {
            std::cout << this->mass[i] << " ";
        }
        std::cout << std::endl;
    }

    void RemoveFirst() {
        this->mass.RemoveFirst();
    }

    void RemoveLast() {
        this->mass.RemoveLast();
    }

    void Remove(int index) {
        this->mass.Remove(index);
    }
};


#endif
