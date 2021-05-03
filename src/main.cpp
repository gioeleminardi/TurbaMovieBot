/**
 * \file       main.cpp
 * \author     Gioele Minardi <gioelem3@gmail.com>
 * \copyright  (C) 2021
 * \license    see LICENSE.txt
 */

#include <iostream>
#include "turba_bot.hpp"

int main() {
    std::string token = getenv("TOKEN");
    std::cout << "Token: " << token << std::endl;
    turba_bot turbaBot(token);


    return 0;
}