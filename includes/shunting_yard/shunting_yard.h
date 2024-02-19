#ifndef SHUNTING_YARD_H
#define SHUNTING_YARD_H
#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include "../errorCode/errorCode.h"
#include "../queue/MyQueue.h"
#include "../stack/MyStack.h"
#include "../token/token.h"
#include "../token/integer.h"
#include "../token/operator.h"
#include "../token/leftparen.h"
#include "../token/rightparen.h"
#include "../token/function.h"

using namespace std;

class ShuntingYard{
public:
  ShuntingYard(){}
  ShuntingYard(const string& str);
  ShuntingYard(const Queue<Token*>& infix): _infix(infix){}

  Queue<Token*> postfix();
  Queue<Token*> postfix(const Queue<Token*>& infix){ _infix = infix; return postfix(); }
  void infix(const Queue<Token*>& infix){ _infix = infix; }


private:
  errorCode* _error;
  Queue<Token*> _infix;
};

#endif 
/*string 1+2
-------^
 take a single char '1'

input string convert and push to queue
1, go through every string and compare, using for (char ch : string)
    if it int push into the interger, 
            using stoi
                -> because using for (char ch : string) so it will go throught every
                variable, like 12, it will go 1 push into int, 2 push into int
                    ->creat a string_temp += char;
                        if(char in rang 1-9)
                        -> 12, 1 in range
                            string temp='1'
                            2 in range
                            string temp= '12'
                        else{ // '+' is not in the rang
                            if(!string_temp.empty()) // make sure the string_temp have smth befor push
                            push new(interger(stoi(string_temp)))
                        }

    if it was op, push it into the op
    if(ch==+-*)
    push new(operator(string(1,ch)));
    -------------------^
                        covert char in to string*/