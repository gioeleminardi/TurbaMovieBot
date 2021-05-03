/**
 * \file       turba_commands.hpp
 * \author     Gioele Minardi <gioelem3@gmail.com>
 * \date       5/3/21
 */
#ifndef TURBAMOVIEBOT_TURBA_COMMANDS_HPP
#define TURBAMOVIEBOT_TURBA_COMMANDS_HPP

namespace turba_v1 {
    static const std::map<std::string, std::string> commands = {
            {"addmovie",     "Add a movie. Usage: /add <movie_name> [<resource_url>]"},
            {"delmovie",     "Remove a movie. Usage: /del <movie_name>"},
            {"extractmovie", "Get a random movie to watch"},
            {"moviedone",    "Remove the extracted movie"},
            {"mymovies",     "Get user channel's movies"},
            {"allmovies",    "Get all channel's movies"}
    };
}

#endif //TURBAMOVIEBOT_TURBA_COMMANDS_HPP
