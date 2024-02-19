#ifndef ERRORCODE_H
#define ERRORCODE_H

struct errorCode{
    int error_code = 0;
    
/*
* 1: popped empty stack
* 2: more than 2 subtractions in a row
* 3: dividing by 0
* 4: missing parentheses
* 5: negation being applied to smthg other than int
* 6:
* 7: extra left parentheses
*/

    void setCode(int num){
        error_code = num;
    }

    errorCode(){ error_code = 0; }
    errorCode(int num): error_code(num){}
};

#endif 