#ifndef LAB2_DYNAMICARRAY_H
#define LAB2_DYNAMICARRAY_H
#include <iostream>

template<class T>
class DynamicArray{
    //указатель на массив
    T* mass;
    //полный размер массива
    int size;
    //реальное количество элементов в массиве
    //и индекс вновь вставляемого элемента
    //int index;
public:
    DynamicArray(int size){
        if(size < 0)
            throw std::invalid_argument("Size < 0");
        this->size = size;
        //this->index = 0;
        this->mass = new T[size];
    }

    DynamicArray(T* items, int count) {
        if(count <= 0)
            throw std::invalid_argument("Size <= 0");
        this->size = count;
        //this->index = count;
        this->mass = new T[this->size];
        memcpy(this->mass, items, sizeof(T) * count);
    }


    DynamicArray(const DynamicArray<T>& dynamicArray) {
        this->size = dynamicArray.size;
        //this->index = dynamicArray.index;
        this->mass = new T[this->size];
        memcpy(this->mass, dynamicArray.mass, sizeof(T) * this->size);
    }

    void Print() {
        for (int i = 0; i < this->size; i++) {
            std::cout << this->mass[i] << " ";
        }
    }

    T& operator[](int n) const {
        if (n < 0 || n >= this->size)
            throw std::out_of_range("n out of range");
        return this->mass[n];
    }

    int GetSize() const{
        return this->size;
    }

    void Set(int n, T value) {
        if (n<0 || n >= this->size)
            throw std::out_of_range("N out of range");
        this->mass[n] = value;
    }

    void Resize(int newSize){
        if (newSize <= 0)
            throw std::invalid_argument("Size <= 0");
        //this->index = this->index < newSize ? this->index : newSize;
        T* a = new T[newSize];
        //memcpy(a, this->mass, this->size * sizeof(T));
        for (int i = 0; i < this->size; ++i) {
            a[i] = this->mass[i];
        }
        delete[] this->mass;
        this->mass = a;
        this->size = newSize;
    }

    void RemoveFirst(){
        for(int i = 0; i < this->size - 1; i++){
            this->mass[i] = this->mass[i+1];
        }
        this->size--;
    }

    void RemoveLast(){
        this->size--;
    }

    void Remove(int index){
        for (int i = index; i < this->size -1; i++){
            this->mass[i] = this->mass[i+1];
        }
        this->size--;
    }

    ~DynamicArray(){
        delete[] this->mass;
        this->size = 0;
        //this->index = 0;
    }
};


#endif