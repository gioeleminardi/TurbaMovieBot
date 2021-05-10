//
// Created by varkrid on 5/10/21.
//

#ifndef TURBAMOVIEBOT_EMOJIS_HPP
#define TURBAMOVIEBOT_EMOJIS_HPP

enum class emoji { clapper_board, eye, stop_sign, film_frames, movie_camera };

static std::unordered_map<emoji, std::string> emoji_map = {{emoji::clapper_board, "\xF0\x9F\x8E\xAC"},
                                                           {emoji::eye, "\xF0\x9F\x91\x81"},
                                                           {emoji::stop_sign, "\xF0\x9F\x9B\x91"},
                                                           {emoji::film_frames, "\xF0\x9F\x8E\x9E"},
                                                           {emoji::movie_camera, "\xF0\x9F\x8E\xA5"}};

#endif  // TURBAMOVIEBOT_EMOJIS_HPP
