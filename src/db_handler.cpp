/**
 * \file       db_handler.cpp
 * \author     Gioele Minardi <gioelem3@gmail.com>
 * \date       5/4/21
 */
#include "db_handler.hpp"
db_handler::db_handler() {}

db_handler::~db_handler() {}

void db_handler::test() {
    using namespace sqlite_orm;
    auto storage = make_storage("db_test.sqlite", make_table("users", ))
}
