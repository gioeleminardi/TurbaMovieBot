//
// Created by varkrid on 5/4/21.
//

#ifndef TURBAMOVIEBOT_MOVIE_STATUS_HPP
#define TURBAMOVIEBOT_MOVIE_STATUS_HPP

#include <sqlite_orm/sqlite_orm.h>

namespace model {
    enum class movie_status { idle, extracted, watched };
    static std::string movie_status_to_string(movie_status status) {
        switch (status) {
        case movie_status::idle:
            return "idle";
        case movie_status::extracted:
            return "extracted";
        case movie_status::watched:
            return "watched";
        }
        return "idle";
    }
    static movie_status movie_status_from_string(const std::string& status) {
        if (status == "idle") {
            return movie_status::idle;
        } else if (status == "extracted") {
            return movie_status::extracted;
        } else if (status == "watched") {
            return movie_status::watched;
        }
        return movie_status::idle;
    }
}  // namespace model

namespace sqlite_orm {
    template <>
    struct type_printer<model::movie_status> : public text_printer {};

    template <>
    struct statement_binder<model::movie_status> {
        int bind(sqlite3_stmt* stmt, int index, const model::movie_status& value) {
            return statement_binder<std::string>().bind(stmt, index, model::movie_status_to_string(value));
        }
    };

    template <>
    struct field_printer<model::movie_status> {
        std::string operator()(const model::movie_status& t) const { return model::movie_status_to_string(t); }
    };

    template <>
    struct row_extractor<model::movie_status> {
        model::movie_status extract(const char* row_value) { return model::movie_status_from_string(row_value); }

        model::movie_status extract(sqlite3_stmt* stmt, int columnIndex) {
            auto str = sqlite3_column_text(stmt, columnIndex);
            return this->extract((const char*)str);
        }
    };
}  // namespace sqlite_orm

#endif  // TURBAMOVIEBOT_MOVIE_STATUS_HPP
