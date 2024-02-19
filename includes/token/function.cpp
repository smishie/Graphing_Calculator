#include "function.h"

double Function::evaluate_func(double x){
    if(_func == "sin"){
        return sin(x);
    }
    if(_func == "cos"){
        return cos(x);
    }
    if(_func == "tan"){
        return tan(x);
    }
    if(_func == "asin"){
        return asin(x);
    }
    if(_func == "acos"){
        return acos(x);
    }
    if(_func == "atan"){
        return atan(x);
    }
    if(_func == "log"){
        return log(x);
    }
    if(_func == "@"){
        return -(x);
    }
    if(_func.length() == 1){
        return x;
    }
    return 9999;
}