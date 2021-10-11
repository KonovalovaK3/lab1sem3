#ifndef LAB2VAR27_LISTSEQUENCE_H
#define LAB2VAR27_LISTSEQUENCE_H

#include <iostream>
#include "Sequence.h"
#include "LinkedList.h"

template<typename T>
class ListSequence : public Sequence<T>{

private:
    LinkedList<T> list;

public:
    ListSequence() : list() {} //Do we need "()" there?

    ListSequence (T* items, int count) : list(items, count) {}

    ListSequence (LinkedList <T> & list) : list(list){}

    T& GetFirst(){
        return this->list.GetFirst();
    }

    T& GetLast(){
        return this->list.GetLast();
    }

    T& operator[](int index) const {
        return this->list.Get(index);
    }

    Sequence<T>* GetSubSequence(int start_index, int end_index){
        LinkedList<T>* l = this->list.GetSubList(start_index, end_index);
        Sequence<T>* res = new ListSequence<T>(*l);
        delete l;
        return res;
    }

    int GetLength() const {
        return this->list.GetLength();
    }

    void Append(const T& item){
        this->list.Append(item);
    }

    void Prepend(const T& item){
        this->list.Prepend(item);
    }

    void InsertAt(const T& item, int index){
        this->list.InsertAt(item, index);
    }

    Sequence <T>* Concat(const Sequence <T>& seq){
        ListSequence<T> * res = new ListSequence<T>();
        for (int i = 0; i < this->GetLength(); i++){
            res->list.Append(this->list.Get(i));
        }
        for (int i = 0; i < seq.GetLength(); i++){
            res->list.Append(seq[i]);
        }
        return res;
    }

    void Print(){
        for(int i = 0; i < this->list.GetLength(); i++){
            std::cout << this->list.Get(i) << " ";
        }
        std::cout << std::endl;
    }

    void RemoveFirst(){
        this->list.RemoveFirst();
    }

    void RemoveLast(){
        this->list.RemoveLast();
    }

    void Remove(int index){
        this->list.Remove(index);
    }
};

#endif