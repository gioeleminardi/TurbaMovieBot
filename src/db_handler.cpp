/**
 * \file       db_handler.cpp
 * \author     Gioele Minardi <gioelem3@gmail.com>
 * \date       5/4/21
 */
#include "db_handler.hpp"

#include <iostream>

db_handler::db_handler()
    : _storage{make_storage_query()} {}

db_handler::~db_handler() = default;

void db_handler::init_schema() { _storage.sync_schema(); }

void db_handler::save_movie(const model::movie& movie) { _storage.insert(movie); }

std::vector<model::movie> db_handler::get_user_movies(const int32_t& user_id, const int64_t& group_id) {
    using namespace model;
    using namespace sqlite_orm;
    return _storage.get_all<model::movie>(where(c(&movie::user_id) == user_id and c(&movie::group_id) == group_id),
                                          order_by(&movie::created_at));
}
