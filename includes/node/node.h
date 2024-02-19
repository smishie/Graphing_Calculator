#ifndef Node_H
#define Node_H
#include <iostream>
#include <iomanip>

using namespace std;

template <typename T>
struct node{
    T _item;
    node<T>* _next;

    node(const T& item = T(), node<T>* next = nullptr): _item(item), _next(next){
            bool debug = false;
            // if(debug){
            //     cout << "node( " << _item << " ) CTOR" << endl;
            // }
        }
    
    friend ostream& operator<<(ostream& outs, const node<T>& n){
        outs << "[" << n._item << "]";
        return outs;
    }
};


#endif
