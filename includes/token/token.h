#ifndef TOKEN_H
#define TOKEN_H
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class Token{
public:
    Token(){ _str = ""; }
    Token(const string& str): _str(str){}

    virtual int get_type(){ return 9999; }
    virtual int get_precedence(){ return 9999; }
    virtual double get_var(){ return 9999; }
    virtual double get_value(){ return 9999; }
    virtual string get_op(){ return "TOKEN"; }

    virtual void print() const{};
    friend ostream& operator <<(ostream& outs, const Token& t){
        t.print();
        return outs;
    }


private:
    string _str;

};

#endif 