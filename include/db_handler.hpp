/**
 * \file       db_handler.hpp.h
 * \author     Gioele Minardi <gioelem3@gmail.com>
 * \date       5/4/21
 */
#ifndef TURBAMOVIEBOT_DB_HANDLER_HPP
#define TURBAMOVIEBOT_DB_HANDLER_HPP

#include <sqlite_orm/sqlite_orm.h>

class db_handler {
public:
    db_handler();
    ~db_handler();

    void test();
};

#endif  // TURBAMOVIEBOT_DB_HANDLER_HPP
