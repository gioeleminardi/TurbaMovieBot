//
// Created by varkrid on 5/3/21.
//

#ifndef TURBAMOVIEBOT_ICOMMANDER_HPP
#define TURBAMOVIEBOT_ICOMMANDER_HPP

#include <string>

class icommander {
    virtual void add_movie(std::string title, std::string resource_url) = 0;

    virtual void delete_movie(std::string title) = 0;

    virtual std::string extract_movie() = 0;

    virtual void my_movies() = 0;

    virtual void all_movies() = 0;
};

#endif //TURBAMOVIEBOT_ICOMMANDER_HPP
