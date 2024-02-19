#include "shunting_yard.h"
ShuntingYard::ShuntingYard(const string& str){
    // cout << "ShuntingYard CTOR..." << endl;
    // cout << "string: " << str << endl;
    
    int length = str.length();
    char* _str = new char[length + 1]; // add one for null termination

    strcpy(_str, str.c_str()); // copies cstring of str into _str

    // try{
    for(int i = 0; i < length; i++){ // checks the elements within the char array
        if(_str[i] != ' '){ // skips spaces
            if(_str[i] == '('){
                _infix.push(new LeftParen());
            }
            if(_str[i] == ')'){
                // cout << "RIGHT PAREN ACTIVATED" << endl;
                _infix.push(new RightParen());
            }

            // if(!isalpha(_str[i]) && isdigit(_str[i]) && _str[i] != ')' && _str[i] != '('){ // integer
            if(isdigit(_str[i])){
                string number = "";
                int j = i;
                // while(!isalpha(_str[j]) && isdigit(_str[j]) && _str[_str[j]] != ')' && _str[_str[j]] != '('){ 
                while(isdigit(_str[j])){
                    number += _str[j];
                    j++;
                }
                i = j - 1;
                // double value = stod(number);
                _infix.push(new Integer(stod(number)));
                number.clear();
            }

            /*if(!isalpha(_str[i]) && !isdigit(_str[i]) && _str[i] != ')' && _str[i] != '('){ // operator
                if(_str[i] == '-' && _infix.empty()){ // first item in strintg is -
                    _infix.push(new Function("@"));
                }
                else if(_str[i] == '-' && !_infix.empty()){ // changes numbers to negative
                    Token* before = _infix.back(); // what if null (first item in list)... -x^2
                    int type = before->get_type();
                    int j = i + 1;
                    if((type == 2 && before->get_precedence() != 999) || type == 4 || type == 5 && _str[i] == '-' || i == 0){ // prior is also an operator
                        string number = "";
                        while(isdigit(_str[j])){
                                number += _str[j];
                                // cout << "number: " << number << endl;
                                j++;
                            }
                        i = j - 1;
                        double value = stod(number);
                        value = -(value);
                        _infix.push(new Integer(value));
                    }
                    else if(isalpha(_str[j])){ // next token is char
                        _infix.push(new Function( "@"));
                        string function = "";
                        int j = i;
                        // while(isalpha(_str[j]) && _str[j] != ')' && _str[j] != '('){
                        while(isalpha(_str[j])){
                            function += _str[j];
                            j++;
                        }
                                        // cout << "function: " << function << endl;
                        _infix.push(new Function(function));
                        function.clear();
                        i = j - 1;
                    }
                } 
                else{
                    _infix.push(new Operator(_str[i]));
                }
            
            }*/

            if(!isalpha(_str[i]) && !isdigit(_str[i]) && _str[i] != ')' && _str[i] != '('){ // operator
                Token* before = _infix.back(); // what if null (first item in list)... -x^2
                int type = before->get_type();
                // type(operator), precedence(not function), before is either parentheses, current op is -
                if((type == 2 && before->get_precedence() != 999) || type == 4 || type == 5 && _str[i] == '-' || i == 0){ // prior is also an operator
                    string number = "";
                    int j = i + 1;
                    if(_str[j + 1] == '-'){
                        throw errorCode(2); // more than 2 subtractions in a row
                    }
                    if(isdigit(_str[i])){
                        throw errorCode(5);
                    }
                        // assert(isdigit(_str[j]) && "the negation is being applied to something other than an Integer");-------------------------------------------
                        while(isdigit(_str[j])){
                            number += _str[j];
                            // cout << "number: " << number << endl;
                            j++;
                        }
                    i = j - 1;
                    double value = stod(number);
                    value = -(value);
                    _infix.push(new Integer(value));
                }
                else{ // prior is not an operator
                    // cout << "_infix: " << _infix << endl;
                    _infix.push(new Operator(_str[i]));
                }
            }

            // if(isalpha(_str[i]) && _str[_str[i]] != ')' && _str[_str[i]] != '('){ // function
                if(isalpha(_str[i])){
                string function = "";
                int j = i;
                // while(isalpha(_str[j]) && _str[j] != ')' && _str[j] != '('){
                while(isalpha(_str[j])){
                    function += _str[j];
                    j++;
                }
                                // cout << "function: " << function << endl;
                _infix.push(new Function(function));
                function.clear();
                i = j - 1;
            }
        }
        // cout << "infix: " << _infix << endl;
        // cout << "end i: " << i << endl;
    }
    // } // end of try
    // catch(int error_code){
    //     cout << "SY: error_code [" << error_code << "]" << endl;
    //     _error->setCode(error_code);

    // }

    // cout << "\nstring to _infix gives: " << _infix << endl; 

}

Queue<Token*> ShuntingYard::postfix(){
    // cout << "\nShuntingYard::postfix():";
    // cout << "\ninput queue: " << _infix << endl;

    Queue<Token*> _output;
    Stack<Token*> _stack;

    double value;
    string op;
    int infix_precedence, stack_precedence;
    Queue<Token*>::Iterator q_it = _infix.begin();
    Stack<Token*>::Iterator s_it = _stack.begin();
    Token* stack_it;

    for(q_it; q_it != _infix.end(); q_it++){
        Token* in_it = *q_it;
        s_it = _stack.begin();
        int type = in_it->get_type();
        
        // cout << "output size: " << _output.size() << endl;

        switch(type){
            case 1:
                value = in_it->get_value();
                _output.push(new Integer(value));
            break;

            case 2:
                if(!_stack.empty()){
                    stack_it = *(s_it = _stack.begin());
                    infix_precedence = in_it->get_precedence();
                    stack_precedence = stack_it->get_precedence();
                    
                    // cout << "infix: " << in_it->get_op() << endl;
                    // cout << "infix_precedence: " << infix_precedence << endl;

                    // cout << "stack: " << stack_it->get_op() << endl; 
                    // cout << "stack_precedence: " << stack_precedence << endl;

                    if(infix_precedence == 999){ // function
                        op = in_it->get_op();
                        _stack.push(new Function(op));
                        break;                      
                    }
                    while(stack_precedence >= infix_precedence && stack_it->get_type() != 4 && !_stack.empty()){ // stack is bigger or equal AND stack isnt leftparen
                        op = stack_it->get_op();
                        stack_precedence = stack_it->get_precedence();
                        if(stack_precedence == 999){
                            _output.push(new Function(op));
                        }else{
                            _output.push(new Operator(op));
                        }
                        _stack.pop();
                        if(!_stack.empty()){
                            stack_it = *(s_it = _stack.begin());
                            stack_precedence = stack_it->get_precedence();
                        }
                    }
                }
                op = in_it->get_op();
                infix_precedence = in_it->get_precedence();
                if(infix_precedence == 999){
                    _stack.push(new Function(op));
                }else{
                    _stack.push(new Operator(op));
                }
                // cout << "output after pushing: " << _output << endl;
                // cout << "stack after pushing: " << _stack << endl;
            break;

            case 4:
                _stack.push(new LeftParen());
            break;

            case 5:
                while(type != 4){
                    // cout << "stack: " << _stack << endl;
                    stack_it = *(s_it = _stack.begin());
                    op = stack_it->get_op();
                    if(op == "("){
                        type = stack_it->get_type();
                        // cout << "stack: " << _stack << endl;
                    }else{
                        stack_precedence = stack_it->get_precedence();
                        if(stack_precedence == 999){
                            _output.push(new Function(op));
                        }else{
                            _output.push(new Operator(op));
                        }
                                            // cout << "just pushed " << op << " into the output after seeing ) " << endl;
                        _stack.pop();
                        // cout << "stack: " << _stack << endl;
                        stack_it = *(s_it = _stack.begin());
                        type = stack_it->get_type();
                    }
                }
                if(stack_it->get_type() != 4)
                {
                    cout << "op: " << op << endl;
                    assert(false &&  "did not pop a parentheses!!!!");
                }
                _stack.pop(); 
            break;
        }
    }
    while(!_stack.empty()){
        stack_it = *(s_it = _stack.begin());
        if(stack_it->get_type() == 4){
            throw errorCode(7);
        }
        // assert(stack_it->get_type() != 4 && "cannot have left parantheses left in stack...");
        op = stack_it->get_op();
        stack_precedence = stack_it->get_precedence();
        if(stack_precedence == 999){
            _output.push(new Function(op));
        }else{
            _output.push(new Operator(op));
        }
        _stack.pop();
    }

    // cout << "final output queue: " << _output << endl;

    return _output;
  }