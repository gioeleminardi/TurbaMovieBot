/**
 * \file       movie.hpp
 * \author     Gioele Minardi <gioelem3@gmail.com>
 * \date       5/4/21
 */
#ifndef TURBAMOVIEBOT_MOVIE_HPP
#define TURBAMOVIEBOT_MOVIE_HPP

namespace model {
    struct movie {
        int id;
        std::int32_t user_id;
        std::int64_t group_id;
        std::string title;
        std::string url;
        time_t created_at;
        bool watched;
    };
}  // namespace model
#endif  // TURBAMOVIEBOT_MOVIE_HPP
