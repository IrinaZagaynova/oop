// HTMLDecode.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "DecodeString.h"

int main()
{
    std::string inputStr;

    while (getline(std::cin, inputStr))
    {
        std::cout << DecodeString(inputStr) << "\n";
    }
    
    return 0;
}
