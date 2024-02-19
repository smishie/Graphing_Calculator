#ifndef MYSTACK_H
#define MYSTACK_H
#include <iostream>
#include <iomanip>
#include "../../includes/linked_list_functions/linked_list_functions.h"

using namespace std;

template <typename T>
class Stack{
public:
    class Iterator{
    public:
        friend class Stack; //give access to list to access _ptr

        Iterator(){_ptr = NULL;} //default ctor
        Iterator(node<T>* p): _ptr(p){}; 

        T &operator*(){ //dereference operator
            return (_ptr ->_item);
        }

        T *operator->(){ //member access operator
            T* ptr = &(_ptr ->_item);
            return ptr;
        }

        bool is_null(){ //true if _ptr is NULL
            return (!_ptr);
        }

        friend bool operator!=(const Iterator &left, const Iterator &right){ //true if left != right
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

        Iterator &operator++(){ // member operator: // ++it; or ++it = new_value
            _ptr = _ptr ->_next;
            return _ptr;
        }

        friend Iterator operator++(Iterator &it, int unused){ //friend operator: it++
            it._ptr = it._ptr ->_next;
            return it._ptr;
        }

    private:
        node<T>* _ptr; //pointer being encapsulated
    };

// default CTOR
// big three
    Stack();
    Stack(const Stack<T>& copyMe);
    ~Stack();

    Stack<T>& operator =(const Stack<T>& RHS);
    T top(){return(_top ->_item); }
    bool empty(){return (!_top); }
    void push(T item);
    T pop();

    int size() const{ return _size; }
    Iterator begin() const{return Iterator(_top); } //Iterator to the head node
    Iterator end() const{return nullptr; } //Iterator to NULL

    friend ostream& operator <<(ostream& outs, const Stack<T>& printMe){
        _print_list<T>(printMe._top);
        // printMe.Print();
        return outs;
    }

private:
    node<T>* _top;
    int _size;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~PRIVATE SIMPLE~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // void Print() const;
    node<T>* insert_head_(T i); //inset i at the head of list
};

    /*------------------------------------------------------------------*/
    /*--------------------------OUT OF CLASSES--------------------------*/
    /*------------------------------------------------------------------*/

// default CTOR
// big three
template <class T>
Stack<T>::Stack(){
    _top = nullptr;
    _size = 0;
}

template <class T>
Stack<T>::Stack(const Stack<T>& copyMe){
    _top = _copy_list<T>(copyMe._top);
    _size = copyMe._size;
}

template <class T>
Stack<T>::~Stack(){
    _clear_list<T>(_top);
    _top = nullptr;
    _size = 0;
}

template <class T>
Stack<T>& Stack<T>::operator =(const Stack<T>& RHS){
    if(this == &RHS){
        return *this;
    }

    _clear_list<T>(_top);
    _top = _copy_list<T>(RHS._top);
    _size = RHS._size;
    return *this;
}

template <class T>
void Stack<T>::push(T item){
    insert_head_(item);
}

template <class T>
T Stack<T>::pop(){
    assert(_top != nullptr && "cannot pop an empty stack");
    T deleted = _delete_head<T>(_top);
    _size--;
    return deleted;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~SIMPLE~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// template <class T>
// void Stack<T>::Print() const{
//     //  _print_list(_top);
//     node<T>* walker = _top;
//     while(walker != nullptr){
//         cout << "[" << (walker -> _item) << "] -> ";
//         walker = walker -> _next;
//     }
//     cout << "|||" << endl;
// }

template <class T>
node<T>* Stack<T>::insert_head_(T i){ //inset i at the head of Stack
    node<T> *inserted =_insert_head<T>(_top, i);
    _size++;
    return inserted;
}           

#endif