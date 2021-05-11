/**
 * \file       db_handler.cpp
 * \author     Gioele Minardi <gioelem3@gmail.com>
 * \date       5/4/21
 */
#include "db_handler.hpp"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>

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
        user_movies_map[user_id] =
            _storage.get_all<movie>(where(c(&movie::user_id) == user_id and c(&movie::group_id) == group_id), order_by(&movie::created_at));
    }

    return user_movies_map;
}

int db_handler::delete_user_movie(const int32_t& user_id, const int64_t& group_id, const int& movie_id) {
    using namespace model;
    using namespace sqlite_orm;

    // clang-format off
    auto db_movie = _storage.get_all<movie>(
        where(
            c(&movie::id) == movie_id and
            c(&movie::user_id) == user_id and
            c(&movie::group_id) == group_id and
            c(&movie::status) != movie_status::extracted)
    );
    // clang-format on

    if (db_movie.empty()) {
        return -1;
    }

    auto user_movie = db_movie[0];
    _storage.remove<movie>(user_movie.id);

    return 0;
}

std::vector<model::movie> db_handler::extract_movie(const std::int64_t& group_id) {
    // select tg_group_id, id, title, min(created_at) from movies where status == "idle" group by tg_user_id
    using namespace model;
    using namespace sqlite_orm;

    auto group_extractions_count = _storage.count<extraction>(where(c(&extraction::group_id) == group_id));
    if (group_extractions_count == 0) {
        // new extraction
        std::cout << "new extraction for group: " << group_id << std::endl;
        // clang-format off
        auto selected_movies_t =
            _storage.select(
                            columns(&movie::id, min(&movie::created_at)),
                            where(
                                c(&movie::group_id) == group_id and
                                c(&movie::status) == movie_status::idle
                            ),
                            group_by(&movie::user_id)
            );
        // clang-format on
        std::vector<int> movies_id;
        movies_id.reserve(selected_movies_t.size());

        for (const auto& t : selected_movies_t) {
            movies_id.push_back(std::get<0>(t));
        }

        std::shuffle(movies_id.begin(), movies_id.end(), std::mt19937(std::random_device()()));

        for (const auto& movie_id : movies_id) {
            _storage.insert(extraction{-1, group_id, movie_id});
        }

        _storage.update_all(set(c(&movie::status) = movie_status::extracted), where(in(&movie::id, movies_id)));
    }

    //    select movies.id, movies.tg_user_id from movies, extractions
    //    where movies.id == extractions.movie_id and extractions.tg_group_id == -582482617
    //    order by extractions.id

    // clang-format off
    auto user_movies = _storage.select(
        columns(&movie::id),
        where(
            c(&movie::id) == &extraction::movie_id and
            c(&extraction::group_id) == group_id
        ),
        order_by(&extraction::id)
        );
    // clang-format on

    std::vector<model::movie> movies;

    for (const auto& tuple : user_movies) {
        auto orderder_movie = _storage.get<movie>(std::get<0>(tuple));
        movies.push_back(orderder_movie);
    }

    return movies;
}

int db_handler::done_watch(const int32_t& user_id, const int64_t& group_id) {
    using namespace model;
    using namespace sqlite_orm;

    // clang-format off
    auto result = _storage.select(
        columns(&extraction::id, &movie::id),
        where(
            c(&movie::id) == &extraction::movie_id and
            c(&extraction::group_id) == group_id and
            c(&movie::user_id) == user_id
        ),
        order_by(&extraction::id)
    );
    // clang-format on

//    if (user_id == 112352414) {
//        // clang-format off
//        result = _storage.select(
//            columns(&extraction::id, &movie::id),
//            where(
//                c(&movie::id) == &extraction::movie_id and
//                c(&extraction::group_id) == group_id
//            ),
//            order_by(&extraction::id)
//        );
//        // clang-format on
//    }

    if (result.empty()) {
        return -1;
    }

    auto extraction_id = std::get<0>(result[0]);
    auto movie_id = std::get<1>(result[0]);

    _storage.remove<extraction>(extraction_id);

    auto _movie = _storage.get<movie>(movie_id);
    _movie.status = model::movie_status::watched;
    _storage.update(_movie);

    return 0;
}
int db_handler::swap_movies(const int32_t& user_id, const int64_t& group_id, const int& movie_id1, const int& movie_id2) {
    using namespace model;
    using namespace sqlite_orm;

    // clang-format off
    auto movies_to_swap = _storage.get_all<movie>(
        where(
                c(&movie::group_id) == group_id and
                c(&movie::user_id) == user_id and
                c(&movie::status) == movie_status::idle and
                in(&movie::id, {movie_id1, movie_id2})
            )
        );
    // clang-format on

    if (movies_to_swap.size() != 2) {
        return -1;
    }

    auto temp_created_at = movies_to_swap[0].created_at;
    movies_to_swap[0].created_at = movies_to_swap[1].created_at;
    movies_to_swap[1].created_at = temp_created_at;

    _storage.update(movies_to_swap[0]);
    _storage.update(movies_to_swap[1]);

    return 0;
}
