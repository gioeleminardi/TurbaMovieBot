/**
 * \file       commands.hpp
 * \author     Gioele Minardi <gioelem3@gmail.com>
 * \date       5/3/21
 */

#ifndef TURBAMOVIEBOT_COMMANDS_HPP
#define TURBAMOVIEBOT_COMMANDS_HPP

#include <tgbot/EventBroadcaster.h>

namespace turba_bot {
    class command {
        using DelegateFunc = TgBot::EventBroadcaster::MessageListener;

    public:
        command() = default;

        command(std::string&& _cmd, std::string&& _description, DelegateFunc _callback)
            : cmd{std::move(_cmd)}
            , description(std::move(_description))
            , callback(std::move(_callback)) {}

        std::string cmd;
        std::string description;
        DelegateFunc callback;
    };
}  // namespace turba_bot

#endif  // TURBAMOVIEBOT_COMMANDS_HPP
