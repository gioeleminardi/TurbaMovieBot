/**
 * \file       db_handler.hpp.h
 * \author     Gioele Minardi <gioelem3@gmail.com>
 * \date       5/4/21
 */
#ifndef TURBAMOVIEBOT_DB_HANDLER_HPP
#define TURBAMOVIEBOT_DB_HANDLER_HPP

#include <sqlite_orm/sqlite_orm.h>

#include "model/turba_entry.hpp"

template <typename... Args>
auto make_storage_query() {
    using namespace sqlite_orm;
    return make_storage(
        "db_test.sqlite",
        make_table("turba_entry", make_column("user_name", &turba_entry::user_name), make_column("group_name", &turba_entry::group_name),
                   make_column("movie_title", &turba_entry::movie_title), make_column("movie_url", &turba_entry::movie_url),
                   make_column("created_at", &turba_entry::created_at), make_column("watched", &turba_entry::watched),
                   primary_key(&turba_entry::user_name, &turba_entry::group_name, &turba_entry::movie_title)));
}

class db_handler {
public:
    db_handler();
    ~db_handler();

    void init_schema();

    void save_entry(const turba_entry& entry);

private:
    decltype(make_storage_query()) _storage;
};

#endif  // TURBAMOVIEBOT_DB_HANDLER_HPP
