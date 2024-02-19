#include <iostream>
#include <iomanip>
#include "rpn.h"
#include <cassert>

double RPN::evaluate(double x){
    Stack<Token*> _stack;

    // cout << "\nRPN::evaluate(double x): ";
    // cout << "\npostfix(): " << _postfix << endl;

    double value;
    int in_precedence;
    double above, under;
    Queue<Token*>::Iterator q_it = _postfix.begin();
    Stack<Token*>::Iterator s_it = _stack.begin();
    Token* stack_ptr;

    // try{
    for(q_it; q_it != _postfix.end(); q_it++){
        Token* in_ptr = *q_it;
        s_it = _stack.begin();
        int type = in_ptr->get_type();
        assert(type == 1 || type == 2 && "infix is not just operator and integers...");

        switch(type){
            case 1:
                value = in_ptr->get_value();
                _stack.push(new Integer(value));
            break;

            case 2:
                in_precedence = in_ptr->get_precedence();

                if(in_precedence == 999){
                    // cout << "stack: " << _stack << endl;
                    // cout << "_postfix: " << _postfix << endl;
                    // cout << "in_ptr: " << in_ptr->get_op() << endl;   
                    bool is_var = static_cast<Function*>(in_ptr)->is_variable();
                    if(is_var){
                    value = static_cast<Function*>(in_ptr)->evaluate_func(x);
                    }
                    else{
                        stack_ptr = *(s_it = _stack.begin());
                        x = stack_ptr->get_value();
                        // cout << "changing x to... " << x << endl;
                        // cout << "stack before popping: " << _stack << endl;
                        _stack.pop();
                        value = static_cast<Function*>(in_ptr)->evaluate_func(x);
                    }
                    // cout << "new value being pushed: " << value << endl;
                    _stack.push(new Integer(value));
                    break;
                }
                    // cout << "stack before popping: " << _stack << endl;
                    stack_ptr = *(s_it = _stack.begin());
                    above = stack_ptr->get_value();
                    if(above == 0){
                        throw errorCode(3); // dividing by 0
                    }
                    _stack.pop();
                    if(_stack.empty()){
                        throw errorCode(1);
                    }
                    // assert(!_stack.empty() && "tryng to do an operation on only one value in stack...");--------------------------------
                    stack_ptr = *(s_it = _stack.begin());
                    under = stack_ptr->get_value();
                    _stack.pop();
                    value = static_cast<Operator*>(in_ptr)->evaluate(under, above);
                    _stack.push(new Integer(value));
            break;
        }
    }
    // cout << "\nRPN: _stack at end: " << _stack << endl;
    if(_stack.empty()){
        throw errorCode(1);
    }
    // assert(!_stack.empty() && "end of RPN has empty stack...");---------------------------------
    stack_ptr = *(s_it = _stack.begin());
    double result = stack_ptr->get_value();
    _stack.pop();
    // cout << "_stack after last pop: " << _stack << endl;
    if(!_stack.empty()){
        throw errorCode(1);
    }
    // assert(_stack.empty() && "stack at end of rpn had more than one value...");----------------------------------
    return result;
    // } // end of try
    // catch(int error_code){
    //     cout << "RPN: error_code [" << error_code << "]" << endl;
    //     _error->setCode(error_code);
    //     if(error_code == 3){
    //         return 9999;
    //     }
    // }
}
