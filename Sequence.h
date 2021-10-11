#ifndef LAB2VAR27_SEQUENCE_H
#define LAB2VAR27_SEQUENCE_H

template<typename T>
class Sequence {

public:
    //Decomposition
    virtual T& GetFirst() = 0;

    virtual T& GetLast() = 0;

    virtual T& operator[](int index) const = 0;

    virtual Sequence<T>* GetSubSequence(int start_index, int end_index)  = 0;

    virtual int GetLength() const = 0;

    //Operations
    virtual void Append(const T& item) = 0;

    virtual void Prepend(const T& item) = 0;

    virtual void InsertAt(const T& item, int index) = 0;

    virtual Sequence<T>* Concat(const Sequence<T>& Sequence) = 0;

    virtual void RemoveFirst() = 0;

    virtual void RemoveLast() = 0;

    virtual void Remove(int index) = 0;

    virtual void Print() = 0;

};

template<typename T>
void BubbleSort(Sequence<T>* seq, int (*cmp)(T,T)){
    for (int i = 0; i < seq->GetLength(); i++){
        for (int j = seq->GetLength() - 1; j > i; j--){
            if(cmp((*seq)[j], (*seq)[j-1]) < 0){
                T tmp = (*seq)[j];
                (*seq)[j] = (*seq)[j-1];
                (*seq)[j-1] = tmp;
            }
        }
    }
}

template<typename T>
void SelectionSort(Sequence<T>* seq, int (*cmp)(T,T)){
    for (int i = 0; i < seq->GetLength(); i++) {
        int k = -1; //индекс с чем менять надо, +маркер нужен ли обмен
        T tmp = (*seq)[i];
        for (int j = i; j < seq->GetLength(); j++) {
            //ищу минимум
            if (cmp(tmp, (*seq)[j]) > 0) {
                tmp = (*seq)[j];
                k = j;
            }
        }
        if (k>0){
            T tmp1 = (*seq)[k];
            (*seq)[k] = (*seq)[i];
            (*seq)[i] = tmp1;
        }

    }
}

template<typename T> //только для целых чисел
/* что делать, если подаются не корректные входные данные?
*/
void CountingSort(Sequence<T>* seq, int (*cmp)(T,T)) {
    int min, max;
    min = (*seq)[0];
    max = (*seq)[0];
    int size = seq->GetLength();
    for (int k = 1; k < size; k++){//ищу минимум и максимум
        if (cmp(min, (*seq)[k]) > 0)
            min = (*seq)[k];
        if (cmp((*seq)[k], max) > 0)
            max = (*seq)[k];
    }
    int r = max - min +1;
    T* output_seq = new T[size];
    int* count_array = new int[r];
    for (int i = 0; i < r; i++){
        count_array[i] = 0;
    }
    for (int i = 0; i < size; i++){
        ++count_array[(*seq)[i] - min]; //считаем количество
    }
    for (int i = 1; i < r; i++) { //высчитываем позицию
        count_array[i] = count_array[i]+count_array[i-1];
    }
    for (int i = 0; i < size; i++){
        output_seq[--count_array[(*seq)[i] - min]] = (*seq)[i];
        //для и-того члена последовательности находим cooтветствующий
        //член массива позиций последнего номера, предварительно уменьшая его на 1
        //(неустойчивая сортировка)
    }
    for (int i = 0; i < size; i++){
        (*seq)[i] = output_seq[i];
    }
}

#endif