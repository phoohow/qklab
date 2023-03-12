#include "Ltemplate.h"
#include <iostream>
#include <string>

/*
A learnning project: to learn basic template
*/
int main()
{
    std::cout << myFun<std::string>("Hello\n", "quick\n", "c/cpp\n"
                                                          "lab\n");
    return 0;
}