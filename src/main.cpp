// Copyright 2022 UNN-IASR

#include <string>
#include <iostream>
#include <clocale>

#include "fun.h"

int main() {
    std::string input_str;

    std::cout << "Введите строку:" << std::endl;

    std::getline(std::cin, input_str);

    std::cout << input_str << std::endl;

    std::cout << std::endl << "Результаты:" << std::endl;
    std::cout << "faStr1: " << faStr1(input_str.c_str()) << std::endl;
    std::cout << "faStr2: " << faStr2(input_str.c_str()) << std::endl;
    std::cout << "faStr3: " << faStr3(input_str.c_str()) << std::endl;

    return EXIT_SUCCESS;
}
