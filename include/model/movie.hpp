/**
 * \file       movie.hpp
 * \author     Gioele Minardi <gioelem3@gmail.com>
 * \date       5/4/21
 */
#ifndef TURBAMOVIEBOT_MOVIE_HPP
#define TURBAMOVIEBOT_MOVIE_HPP
#include <string>
class movie {
public:
    int id;
    std::string title;
    std::string url;
    time_t timestamp;
    int user_id;
    int group_id;
};

#endif  // TURBAMOVIEBOT_MOVIE_HPP
