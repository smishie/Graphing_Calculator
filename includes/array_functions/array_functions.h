#ifndef ARRAY_FUNCTIONS_H
#define ARRAY_FUNCTIONS_H

#include <iostream>
#include <string>
const int MINIMUM_CAPACITY = 3;
using namespace std;

template<class T>
T* allocate(int capacity = MINIMUM_CAPACITY);            //allocate 'capacity' 
                                                        //      elements. 
                                                        //  return array

template<class T>
T* reallocate(T* a, int size, int capacity);            //take array, resize it 
                                                        //  return new array. 
                                                        //  delete old array

template<class T>
void print_array(T* a, int size, int capacity = 0, ostream& outs = cout);    //prints 
                                                        //  (size/capacity)
                                                        //  for debugging

template <class T>
void print(T* a, unsigned int how_many);  //print array

template<class T>
T* search_entry(T* a, int size, const T& find_me);      //search for 'find me'

template <class T>
int search(T* a, int size, const T& find_me);           //search for 'find_me' 

template <class T>
void shift_left(T* a, int& size, int shift_here);       //shift left @ pos:
                                                        //    erases @ pos
template <class T>
void shift_left(T* a, int& size, T* shift_here);        //shift left @ pos: 
                                                        //    erases @ pos

template <class T>
void shift_right(T *a, int &size, int shift_here);      //shift right: 
                                                        //      make a hole

template <class T>
void shift_right(T *a, int &size, T* shift_here);       //shift right: 
                                                        //   make a hole

template<class T>
void copy_array(T *dest, const T* src, 
                                int many_to_copy);      //copy from src to dest

template <class T>
T* copy_array(const T *src, int size);                  //return a 
                                                        //  copy of src

template <class T>
string array_string(const T *a, int size);              //return array 
                                                        //  as a string


//DEFINITIONS

template<class T>
T* allocate(int capacity){  //allocate 'capacity' 
    T* a = new T[capacity]; // elements. 
    return a; // return array
} 

template<class T>
T* reallocate(T* a, int size, int capacity){ //take array, resize it 
    T* b = new T[capacity]; // new space in memory

    copy_array(b, a, capacity);

    delete[] a; // delete old array
    return b;
}

template<class T>
void print_array(T* a, int size, int capacity, ostream& outs){ //prints 
    outs << "(" << size << "/" << capacity << ")[ "; 
    T* walker = a;
    for(int i = 0; i < size; i++){ 
        outs << *walker << " "; //element walker points to prints
        walker++; //iterate walker once
    }
    outs << "]";
}

template <class T>
void print(T* a, unsigned int how_many){ //print array
    T* walker = a;
    for(int i = 0; i < how_many; i++){
        cout << walker << " ";
        walker++;
    }
}

template<class T>
T* search_entry(T* a, int size, const T& find_me){ //search for 'find me'
    T* walker = a;
    for(int i = 0; i < size; i++){
        if(*walker == find_me){ //checks if element matches value
            return walker; // returns the pointer to location
        }
        walker++;
    }
    return nullptr; //returns if value is not found in array
}

template <class T>
int search(T* a, int size, const T& find_me){ //search for 'find_me' 
    T* walker = a;
    for(int i = 0; i < size; i++){
        if(*walker == find_me){
            return i; // returns the index
        }
        walker++;
    }
    return -1; //returns if value is not found in array
}

template <class T>
void shift_left(T* a, int& size, int shift_here){ //shift left @ pos:
    T* start = a + shift_here; //points at where shift is wanted
    T* walker = start + 1; //points to index after

    for(int i = shift_here; i < size - 1; i++){ // loop continues from the index until size of array
        *start = *walker; //value after the start index is copied to the start
        start++;
        walker++;
    }
    size--; //decrease size because a value is "deleted"
}

template <class T>
void shift_left(T* a, int& size, T* shift_here){ //shift left @ pos: 
    int index = (shift_here - a); // finds index of value shift
    assert(index < size);

    shift_left(a, size, index);
}

template <class T>
void shift_right(T *a, int &size, int shift_here){ //shift right: 
    assert(shift_here < size);
    size++; // increases the size of interesting elements
    T* end = a + (size - 1); // sets a pointer to the end of array
    T* walker = end - 1; // another pointer to element before the end

    for(int i = size; i > shift_here + 1; i--){
        *end = *walker; // the value at the end gets the value before it
        end--;      // both pointers decrease one
        walker--;
    } 
}

template <class T>
void shift_right(T *a, int &size, T* shift_here){ //shift right: 
    int index = (shift_here - a); // finds the index of value finding   

    shift_right(a, size, index);
}

template<class T>
void copy_array(T *dest, const T* src, int many_to_copy){ //copy from src to dest
    const T* walker = src; 
    for(int i = 0; i < many_to_copy; i++){
        *dest = *walker; //puts the elements from src into the dest
        walker++;
        dest++;
    }
}

template <class T>
T* copy_array(const T *src, int size){ //return a 
    T* a = new T[size]; //creates new array
    const T* walker = src; //points at array being copied
    T* dest = a; //points at new array
    
    for(int i = 0; i < size; i++){ 
        *dest = *walker; //  copy of src into dest
        walker++;
        dest++;
   }
   return a; //keeps the values copied into new array
   delete[] a; //deletes allocated space
}

template <class T>
string array_string(const T *a, int size){ //return string 
    const T* walker = a;
    string str = ""; //initialize empty string

    for(int i = 0; i < size; i++){
        str += to_string(*walker); //changes the int into string
        str += " "; //space between index
        walker++;
    }

    return str;
}

#endif