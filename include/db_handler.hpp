/**
 * \file       db_handler.hpp.h
 * \author     Gioele Minardi <gioelem3@gmail.com>
 * \date       5/4/21
 */
#ifndef TURBAMOVIEBOT_DB_HANDLER_HPP
#define TURBAMOVIEBOT_DB_HANDLER_HPP

#include <sqlite_orm/sqlite_orm.h>

#include <unordered_map>

#include "model/extraction.hpp"
#include "model/movie.hpp"

template <typename... Args>
auto make_storage_query() {
    using namespace sqlite_orm;
    using namespace model;
    // clang-format off
    return make_storage(
        "db_test.sqlite",
        make_unique_index("idx_movie", &movie::user_id, &movie::group_id, &movie::title),
        make_unique_index("idx_extraction", &extraction::group_id, &extraction::movie_id),
        make_table("movies",
                   make_column("id", &movie::id, primary_key(), autoincrement()),
                   make_column("tg_user_id", &movie::user_id),
                   make_column("tg_group_id", &movie::group_id),
                   make_column("title", &movie::title),
                   make_column("url", &movie::url),
                   make_column("created_at", &movie::created_at),
                   make_column("status", &movie::status)),
        make_table("extractions",
                   make_column("id", &extraction::id, primary_key(), autoincrement()),
                   make_column("tg_group_id", &extraction::group_id),
                   make_column("movie_id", &extraction::movie_id))
        );
    // clang-format on
}

class db_handler {
public:
    db_handler();
    ~db_handler();

    void init_schema();

    void save_movie(const model::movie& movie);
    std::vector<model::movie> get_user_movies(const std::int32_t& user_id, const std::int64_t& group_id);
    std::unordered_map<std::int32_t, std::vector<model::movie>> get_group_movies(const std::int64_t& group_id);
    int delete_user_movie(const std::int32_t& user_id, const std::int64_t& group_id, const int& movie_id);
    std::vector<model::movie> extract_movie(const std::int64_t& group_id);
    int done_watch(const std::int32_t& user_id, const std::int64_t& group_id);

private:
    decltype(make_storage_query()) _storage;
};

#endif  // TURBAMOVIEBOT_DB_HANDLER_HPP
