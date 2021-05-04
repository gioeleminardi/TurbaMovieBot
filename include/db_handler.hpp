/**
 * \file       db_handler.hpp.h
 * \author     Gioele Minardi <gioelem3@gmail.com>
 * \date       5/4/21
 */
#ifndef TURBAMOVIEBOT_DB_HANDLER_HPP
#define TURBAMOVIEBOT_DB_HANDLER_HPP

#include <sqlite_orm/sqlite_orm.h>

#include "model/movie.hpp"

template <typename... Args>
auto make_storage_query() {
    using namespace sqlite_orm;
    using namespace model;
    return make_storage("db_test.sqlite", make_unique_index("idx_movie", &movie::user_id, &movie::group_id, &movie::title),
                        make_table("movies", make_column("id", &movie::id, primary_key(), autoincrement()),
                                   make_column("tg_user_id", &movie::user_id), make_column("tg_group_id", &movie::group_id),
                                   make_column("title", &movie::title), make_column("url", &movie::url),
                                   make_column("created_at", &movie::created_at), make_column("watched", &movie::watched)));
}

class db_handler {
public:
    db_handler();
    ~db_handler();

    void init_schema();

    void save_movie(const model::movie& movie);

private:
    decltype(make_storage_query()) _storage;
};

#endif  // TURBAMOVIEBOT_DB_HANDLER_HPP
