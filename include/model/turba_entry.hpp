/**
 * \file       turba_entry.hpp
 * \author     Gioele Minardi <gioelem3@gmail.com>
 * \date       5/4/21
 */
#ifndef TURBAMOVIEBOT_TURBA_ENTRY_HPP
#define TURBAMOVIEBOT_TURBA_ENTRY_HPP

class turba_entry {
public:
    std::string user_name;
    std::string group_name;
    std::string movie_title;
    std::string movie_url;
    time_t created_at;
    bool watched;
};

#endif  // TURBAMOVIEBOT_TURBA_ENTRY_HPP
