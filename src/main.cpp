/**
 * \file       main.cpp
 * \author     Gioele Minardi <gioelem3@gmail.com>
 * \date       5/3/21
 */

#include <iostream>
#include "turba_bot.hpp"

int main() {
    std::string token = getenv("TOKEN");
    std::cout << "Token: " << token << std::endl;

    turba_bot turbaBot(token);

    turbaBot.init();

    turbaBot.run();

    return 0;
}