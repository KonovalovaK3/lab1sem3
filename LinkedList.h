#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

template<class T>
class LinkedList {
private:
    class Node {
    public:
        T data;
        Node* pNext, * pPrev;

        Node(T data = T(), Node* pNext = nullptr, Node* pPrev = nullptr) {
            this->data = data;
            this->pNext = pNext;
            this->pPrev = pPrev;
        }
    };

    Node* tail;
    Node* head;
    int size;

public:
    //Constructors
    LinkedList() {
        this->size = 0;
        this->head = this->tail = nullptr;
    }

    LinkedList(T* data, int count) {
        this->size = 0;
        for (int i = 0; i < count; i++) {
            this->Append(data[i]);
        }
    }

    LinkedList(const LinkedList<T>& list) {
        this->size = 0;
        for (int i = 0; i < list.size; i++) {
            this->Append(list.Get(i));
        }
    }

    T& GetFirst() {
        if (this->size <= 0)
            throw std::out_of_range("Index out of range"); //
        return this->head->data;
    }

    T& GetLast() {
        if (size <= 0)
            throw std::out_of_range("Index out of range"); //
        return this->tail->data;
    }

    T& Get(int index) const {
        if (index < 0 || index >= this->size)
            throw std::out_of_range("Index out of range");
        if (index < this->size / 2) {
            Node* nodeA = this->head;
            for (int i = 1; i <= index; i++) {
                nodeA = nodeA->pNext;
            }
            return nodeA->data;
        } else {
            Node* nodeB = this->tail;
            for (int i = this->size -1 ; i > index; i--) {
                nodeB = nodeB->pPrev;
            }
            return nodeB->data;
        }
    }

    LinkedList<T>* GetSubList(int startIndex, int endIndex) {
        if (startIndex < 0 || endIndex <= 0 || startIndex >= endIndex || endIndex >= this->size)
            throw std::out_of_range("Index out of range");
        LinkedList<T>* Res = new LinkedList();
        for (int i = startIndex; i < endIndex; i++) {
            Res->Append(this->Get(i));
        }
        return Res;
    }

    int GetLength() const {
        return this->size;
    }

    void Append(T item) {
        Node* nodeA = new Node(item);
        if (this->size == 0) {
            this->head = this->tail = nodeA;
        } else {
            nodeA->pPrev = this->tail;
            this->tail->pNext = nodeA;
            this->tail = nodeA;
        }
        this->size++;
    }

    void Prepend(T item) {
        Node* nodeA = new Node(item);
        if (this->size == 0) {
            this->head = this->tail = nodeA;
        } else {
            nodeA->pNext = this->head;
            this->head = nodeA;
        }
        this->size++;
    }

    void InsertAt(T item, int index){
        if (index < 0 || index > this->size)
            throw std::out_of_range("Index out of range");
        if(index == 0){
            this->Prepend(item);
            return;
        }
        if(index == this->size){
            this->Append(item);
            return;
        }

        Node* tmp = this->head;
        for(int i = 1; i < this->size; i++){
            if(i == index){
                Node* newNode = new Node(item, tmp->pNext, tmp);
                tmp->pNext->pPrev = newNode;
                tmp->pNext = newNode;
                this->size++;
                return;
            }
            tmp = tmp->pNext;
        }
    }

    LinkedList<T>* Concat(const LinkedList<T>* list) {
        LinkedList<T>* Res = new LinkedList();
        for (int i = 0; i < this->size; i++) {
            Res->Append(this->Get(i));
        }
        for (int j = 0; j < list->size; j++) {
            Res->Append(list->Get(j));
        }
        return Res;
    }

    void print() {
        Node* nodeA = this->head;
        for (int i = 0; i < this->size; i++) {
            std::cout << nodeA->data << std::endl;
            nodeA = nodeA->pNext;
        }
    }

    void RemoveFirst(){
        this->head = this->head->pNext;
        delete this->head->pPrev;
        this->head->pPrev = nullptr;
        this->size--;
    }

    void RemoveLast(){
        this->tail = this->tail->pPrev;
        delete this->tail->pNext;
        this->tail->pNext = nullptr;
        this->size--;
    }

    void Remove(int index){
        /*for (int i = 0; i < index; i++)*/
    }

    ~LinkedList() {
        if (this->head != nullptr) {
            int a = this->size;
            for (int i = 0; i < a; i++) {
                Node* old_head = this->head;
                if (this->size == 1) {
                    this->head = nullptr;
                    this->tail = nullptr;
                } else {
                    this->head = this->head->pNext;
                }
                delete old_head;
            }
        }
    }
};

#endif
