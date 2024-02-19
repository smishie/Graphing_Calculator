#ifndef MYQUEUE_H
#define MYQUEUE_H
#include <iostream>
#include <iomanip>
#include "../../includes/linked_list_functions/linked_list_functions.h"

using namespace std;

template <typename T>
class Queue{
public:
    class Iterator{
    public:
        friend class Queue; //give access to list to access _ptr

        Iterator(){_ptr = NULL;} //default ctor
        Iterator(node<T>* p): _ptr(p){}; 

        T &operator *(){ //dereference operator
            return (_ptr ->_item);
        }

        T *operator ->(){ //member access operator
            T* ptr = &(_ptr ->_item);
            return ptr;
        }

        bool is_null(){ //true if _ptr is NULL
            return (!_ptr);
        }

        friend bool operator !=(const Iterator &left, const Iterator &right){ //true if left != right
            if(left._ptr != right._ptr){
                return true;
            }
            return false;
        }

        friend bool operator ==(const Iterator &left, const Iterator &right){ //true if left == right
            if(left._ptr == right._ptr){
                return true;
            }
            return false;
        }

        Iterator &operator ++(){ // member operator: // ++it; or ++it = new_value
            _ptr = _ptr ->_next;
            return _ptr;
        }

        friend Iterator operator ++(Iterator &it, int unused){ //friend operator: it++
            it._ptr = it._ptr ->_next;
            return it._ptr;
        }
 
    private:
        node<T>* _ptr;               //pointer being encapsulated
    }; // class Iterator

// default CTOR
// big 3
    Queue();
    Queue(const Queue<T>& copyMe);
    ~Queue();
    Queue& operator =(const Queue<T>& RHS);

    bool empty(){return (!_front); }

    void push(T item);
    T pop();
    void print_pointers();


    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~PUBLIC ITERATOR~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    Iterator begin() const{return Iterator(_front); } //Iterator to the head node
    Iterator end() const{return nullptr; } //Iterator to NULL

    int size() const{ return _size; }
    T front(){ return _front ->_item; }
    T back(){ return _rear ->_item;}

    friend ostream& operator <<(ostream& outs, const Queue<T>& printMe){
        _print_list<T>(printMe._front);
        return outs;
    }

private:
    node<T>* _front;
    node<T>* _rear;
    int _size;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~PRIVATE SIMPLE~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // void Print() const;
    node<T>* insert_head_(T i); //inset i at the head of list

};

    /*------------------------------------------------------------------*/
    /*--------------------------OUT OF CLASSES--------------------------*/
    /*------------------------------------------------------------------*/

// default CTOR
// big 3
template <class T>
Queue<T>::Queue(){
    _front = nullptr;
    _rear = nullptr;
    _size = 0;
}

template <class T>
Queue<T>::Queue(const Queue<T>& copyMe){
    _front = nullptr;
    _rear = _copy_list<T>(_front, copyMe._front);
    _size = copyMe._size;
}

template <class T>
Queue<T>::~Queue(){
    _clear_list<T>(_front);
    _front = nullptr;
    _rear = nullptr;
    _size = 0;
}

template <class T>
Queue<T>& Queue<T>::operator =(const Queue<T>& RHS){
    if(this != &RHS){
        _clear_list<T>(_front);
        _rear = _copy_list<T>(_front, RHS._front);
        _size = RHS._size;
    }
    return *this;
}

template <class T>
void Queue<T>::push(T item){
    if(_front == nullptr && _rear == nullptr){
        node<T>* inserted = _insert_head<T>(_front, item);
        _rear = inserted;
    }
    else{
        node<T>* inserted = _insert_after<T>(_front, _rear, item);
        _rear = inserted;
    }
    _size++;
}

template <class T>
T Queue<T>::pop(){
    assert(_front != nullptr);
    T removed = _delete_head<T>(_front);
    if(_front == _rear){
        _rear = nullptr;
    }
    _size--;
    return removed;
}

template <class T>
void Queue<T>::print_pointers(){
    _print_list<T>(_front);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~SIMPLE~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// template <class T>
// void Queue<T>::Print() const{
//     node<T>* walker = _front;
//     while(walker != nullptr){
//         cout << "[" << (*walker -> _item) << "] -> ";
//         walker = walker -> _next;
//     }
//     cout << "|||" << endl;
// }

template <class T>
node<T>* Queue<T>::insert_head_(T i){ //inset i at the head of list
    node<T> *inserted =_insert_head<T>(_front, i);
    _size++;
    return inserted;
}           

#endif 