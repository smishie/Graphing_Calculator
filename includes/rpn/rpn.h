#ifndef RPN_H
#define RPN_H
#include <iostream>
#include <iomanip>
#include "../errorCode/errorCode.h"
#include "../queue/MyQueue.h"
#include "../stack/MyStack.h"
#include "../token/token.h"
#include "../token/integer.h"
#include "../token/function.h"
#include "../token/operator.h"

class RPN{
public:
    RPN(){ }
    RPN(const Queue<Token*>& postfix): _postfix(postfix){}

    double operator ()(double x = 0){
        return evaluate(x);
    }
    double evaluate(double x);
    void set_input(const Queue<Token*>& postfix){ _postfix = postfix; }

private:
    errorCode* _error;
    Queue<Token*> _postfix;
};

#endif 