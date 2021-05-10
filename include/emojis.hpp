//
// Created by varkrid on 5/10/21.
//

#ifndef TURBAMOVIEBOT_EMOJIS_HPP
#define TURBAMOVIEBOT_EMOJIS_HPP

// clang-format off
enum class emoji {
    clapper_board,
    eye,
    stop_sign,
    film_frames,
    movie_camera,
    heavy_check_mark
};

static std::unordered_map<emoji, std::string> emoji_map = {
    {emoji::clapper_board,      "\xF0\x9F\x8E\xAC"},
    {emoji::eye,                "\xF0\x9F\x91\x81"},
    {emoji::stop_sign,          "\xF0\x9F\x9B\x91"},
    {emoji::film_frames,        "\xF0\x9F\x8E\x9E"},
    {emoji::movie_camera,       "\xF0\x9F\x8E\xA5"},
    {emoji::heavy_check_mark,   "\xE2\x9C\x94"}
};
// clang-format on

#endif  // TURBAMOVIEBOT_EMOJIS_HPP
