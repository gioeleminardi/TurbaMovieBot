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
std::unordered_map<std::int32_t, std::vector<model::movie>> db_handler::get_group_movies(const int64_t& group_id) {
    using namespace model;
    using namespace sqlite_orm;

    std::unordered_map<std::int32_t, std::vector<model::movie>> user_movies_map;

    auto user_list = _storage.select(&movie::user_id, where(c(&movie::group_id) == group_id));
    for (const auto& user_id : user_list) {
        user_movies_map[user_id] = _storage.get_all<movie>(where(c(&movie::user_id) == user_id), order_by(&movie::created_at));
    }

    return user_movies_map;
}
int db_handler::delete_user_movie(const int32_t& user_id, const int64_t& group_id, const int& movie_id) {
    using namespace model;
    using namespace sqlite_orm;
    auto db_movie =
        _storage.get_all<movie>(where(c(&movie::user_id) == user_id and c(&movie::group_id) == group_id and c(&movie::id) == movie_id));
    if (db_movie.empty()) {
        return -1;
    }

    auto user_movie = db_movie[0];
    _storage.remove<movie>(user_movie.id);

    return 0;
}

std::vector<std::pair<std::int32_t, model::movie>> db_handler::extract_movie(const std::int64_t& group_id) {
    // select tg_group_id, id, title, min(created_at) from movies where status == "idle" group by tg_user_id
    using namespace model;
    using namespace sqlite_orm;
    auto movies =
        _storage.select(columns(&movie::id, min(&movie::created_at)), where(c(&movie::group_id) == group_id), group_by(&movie::user_id));
    for (const auto& t : movies) {
        auto movie_id = std::get<0>(t);
        std::cout << "MovieID: " << movie_id << std::endl;
    }
    return {};
}
