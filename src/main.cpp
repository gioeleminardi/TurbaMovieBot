/**
 * \file       main.cpp
 * \author     Gioele Minardi <gioelem3@gmail.com>
 * \date       5/3/21
 */

#include <iostream>

#include "bot.hpp"
#include "db_handler.hpp"

int main() {
//    std::string token = getenv("TOKEN");
//    std::cout << "Token: " << token << std::endl;
//
//    bot turbaBot(token);
//
//    turbaBot.init();
//
//    turbaBot.run();

    db_handler dbHandler;

    dbHandler.init_schema();

    return 0;
}