#ifndef LINKED_LIST_FUNCTIONS_H
#define LINKED_LIST_FUNCTIONS_H
#include <iostream>
#include <iomanip>
#include <assert.h>
#include "../node/node.h"

using namespace std;

template <typename T>
node<T>* _search_list(node<T>* headptr, const T& key);

template <typename T>
node<T>* _insert_head(node<T>*& headptr, const T& insert_this);

template <typename T>
node<T>* _insert_after(node<T>*& headptr, node<T>* after_this, const T& insert_this);

template <typename T>
node<T>* _insert_before(node<T>*& headptr, node<T>* before_this, const T& insert_this);

template <typename T>
node<T>* _previous_node(node<T>* headptr, node<T>* prev_to_this);

template <typename T>
void _print_list(node<T>*& headptr);

template <typename T>
void _print_list_backwards(node<T>* headptr);

template <typename T>
T _delete_node(node<T>*& headptr, node<T>* delete_this);

template <typename T>
T _delete_head(node<T>*& headptr);

template <typename T>
node<T>* _copy_list(node<T>* head);

//duplicate list and return the last node of the copy
template <typename T>
node<T>* _copy_list(node<T>* &dest, node<T> *src);

template <typename T>
void _clear_list(node<T>*& headptr);

template <typename T>
T& _at(node<T>* headptr, int pos);

template <typename T>
node<T>* _insert_sorted(node<T>*& headptr, T item, bool ascending = true);

//insert or add if a dup
template <typename T>
node<T>* _insert_sorted_and_add(node<T>*& headptr, T item, bool ascending = true);

//node after which this item goes order: 0 ascending
template <typename T>
node<T>* _where_this_goes(node<T>* headptr, T item, bool ascending = true);




//DEFINITIONS
template <typename T>
node<T>* _search_list(node<T>* headptr, const T& key){
    node<T>* walker = nullptr;

    for(walker = headptr; walker; walker = walker ->_next){ //goes through whole list
        if(walker ->_item == key){ //checks object with key
            return walker; //returns the walker at the address where key has been found
        }
    }

    return walker;
}

template <typename T>
node<T>* _insert_head(node<T>*& headptr, const T& n){
    node<T>* newHead = new node<T>(n, headptr);
    headptr = newHead;
    return headptr;
}

template <typename T>
node<T>* _insert_after(node<T>*& headptr, node<T>* after_this, const T& insert_this){    
    node<T>* insert_me = new node<T>(insert_this);
    
    if(headptr == nullptr){
        _insert_head(headptr, insert_this);
    }

    insert_me ->_next = after_this ->_next;
    after_this ->_next = insert_me;
    
    return insert_me;
}

template <typename T>
node<T>* _insert_before(node<T>*& headptr, node<T>* before_this, const T& insert_this){
    node<T>* insert_me = new node<T>(insert_this);
    node<T>* prev = _previous_node(headptr, before_this);

    if(!prev){
        _insert_head(headptr, insert_this);
    }
    else{
        prev ->_next = insert_me;
        insert_me ->_next = before_this;
    }

    return insert_me;
}

template <typename T>
node<T>* _previous_node(node<T>* headptr, node<T>* prev_to_this){
    node<T>* walker = nullptr;
    if(headptr == prev_to_this){
        return nullptr;
    }
    if(!headptr){
        return nullptr;
    }

    for(walker = headptr; walker; walker = walker ->_next){
        if(walker ->_next == prev_to_this){ //walker's node points to the address of mark
            return walker; //return walker's node
        }
    }

    assert(walker != nullptr && "marker not on list");  // marker not on list
    return walker;
}

template <typename T>
void _print_list(const node<T>* headptr){
    const node<T>* walker = headptr;
    while(walker != nullptr){
        cout << "[" << *(walker -> _item) << "] -> ";
        walker = walker -> _next;
    } 
    cout << "|||" << endl;
}

template <typename T>
void _print_list_backwards(node<T>* headptr){
    node<T>* walker = nullptr;
    node<T>* walker2 = nullptr;
    
    for(walker = headptr; walker; walker = walker ->_next){
        if(walker ->_next == nullptr){ // walker's node points to null, walker is last node
            cout << "[" << (walker ->_item) << "] -> "; 
            node<T>* prev = walker; //initialize node to the lastoo

            for(walker2 = headptr ->_next; walker2; walker2 = walker2 ->_next){ //iterates list size - 1
                prev = _previous_node(headptr, prev); // assigns node to the previous of what it is/was
                cout << "[" << (prev ->_item) << "] -> ";
            }
        }
    }
    cout << "|||" << endl;
}

template <typename T>
T _delete_node(node<T>*& headptr, node<T>* delete_this){
    assert(delete_this != nullptr && "delete_this == nullptr");
    node<T>* temp = nullptr;
    node<T>* walker = nullptr;

    if(headptr == delete_this){
        temp = delete_this;
        headptr = temp ->_next;
        delete delete_this;
    }
    else{
        temp = delete_this;
        walker = _previous_node(headptr, temp);
        walker ->_next = temp ->_next;
        delete delete_this;
    }
    
    return temp ->_item;
}

template <typename T>
T _delete_head(node<T>*& headptr){
    node<T>* new_head = headptr;
    T item = new_head ->_item;
    headptr = headptr ->_next;
    delete new_head;
    return item;
}

template <typename T>
node<T> *_copy_list(node<T>* head){
    node<T>* dest = nullptr;
    _copy_list(dest, head);
    return dest;
}

//duplicate list and return the last node of the copy
template <typename T>
node<T> *_copy_list(node<T>* &dest, node<T> *src){
    _clear_list(dest);
    node<T>* end = nullptr;
    node<T>* walker = nullptr;

    if(!src){
        return nullptr;
    }

    for(walker = src; walker; walker = walker ->_next){
        node<T>* new_node = new node<T>(walker ->_item);

        if(dest == nullptr){
            dest = new_node;
            end = dest;
        }else{
            end ->_next = new_node;
            end = new_node;
        }
    }

    return end;
}

template <typename T>
void _clear_list(node<T>*& headptr){

    while(headptr != nullptr){ // headptr keeps going "forward" while temp stores and deletes
        node<T>* temp = headptr; // stores
        headptr = headptr ->_next; // goes down headptr
        delete temp; // deletes where headptr was
    }

}

template <typename T>
T& _at(node<T>* headptr, int pos){
    node<T>* walker = nullptr;
    int i = 0;

    for(walker = headptr; walker; walker = walker ->_next, i++){
        if(i == pos){
            return walker ->_item;
        }
    }
    
    assert(walker != nullptr);
    return walker ->_item;
}

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
//      Sorted List Routines. order: 0: ascending, order: other: descending
//                              Assume a Sorted List
//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

template <typename T>
node<T>* _insert_sorted(node<T>*& headptr, T item, bool ascending){
    node<T>* inserted = nullptr;

    node<T>* follower = _where_this_goes<T>(headptr, item, ascending);
    if(!follower){
        _insert_head(headptr, item);
    }
    else{
        inserted = _insert_after<T>(headptr, follower, item);
        return inserted;
    }
    
    return inserted;
}

//insert or add if a dup
template <typename T>
node<T>* _insert_sorted_and_add(node<T>*& headptr, T item, bool ascending){
    node<T>* walker = nullptr;
    node<T>* found = _search_list(headptr, item);

    if(found == nullptr){
        return nullptr;
    }

    walker = found;
    walker ->_item = (walker ->_item + item);
    return headptr;
}

//node after which this item goes order: 0 ascending
template <typename T>
node<T>* _where_this_goes(node<T>* headptr, T item, bool ascending){
    node<T>* lead_walker = nullptr;
    node<T>* follower = nullptr;

    if(!headptr){
        return nullptr;
    }

    for(lead_walker = headptr, follower = headptr; lead_walker; lead_walker = lead_walker ->_next){
        assert(lead_walker != nullptr && "lead_walker fell off");
        
        if((ascending && headptr ->_item >= item) || (!ascending && headptr ->_item <= item)){
            return nullptr;
        }
        
        if((ascending && lead_walker ->_item >= item) || (!ascending && lead_walker ->_item <= item)){
            return follower;
        }

        follower = lead_walker;
    }

    return follower;
}

#endif 
