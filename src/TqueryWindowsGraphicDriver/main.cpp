#include "TqueryWindowsGraphicDriver.h"
#include <iostream>
#include <string>

int main()
{
    if (query() == 1)
        std::cerr << "Failed to query graphic driver version!\n";

    std::cout << "Success to query graphic driver version!\n";
    return 0;
}
