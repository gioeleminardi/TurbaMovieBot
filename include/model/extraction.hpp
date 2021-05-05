/**
 * \file       extraction.hpp
 * \author     Gioele Minardi <gioelem3@gmail.com>
 * \date       5/5/21
 */
#ifndef TURBAMOVIEBOT_EXTRACTION_HPP
#define TURBAMOVIEBOT_EXTRACTION_HPP

namespace model {
    struct extraction {
        int id;
        std::int64_t group_id;
        int movie_id;
    };
}  // namespace model

#endif  // TURBAMOVIEBOT_EXTRACTION_HPP
