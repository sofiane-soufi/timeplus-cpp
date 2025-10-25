#include "query.h"

namespace timeplus {

const std::string Query::default_query_id = {};

Query::Query()
{
    InitializeDefaultSettings();
}

Query::Query(const char* query, const char* query_id)
    : query_(query)
    , query_id_(query_id ? std::string(query_id): default_query_id)
{
    InitializeDefaultSettings();
}

Query::Query(std::string query, std::string query_id)
    : query_(std::move(query))
    , query_id_(std::move(query_id))
{
    InitializeDefaultSettings();
}

Query::~Query()
{ }

void Query::InitializeDefaultSettings() {
    auto emplace_if_absent = [this](std::string key, std::string value) {
        if (query_settings_.find(key) == query_settings_.end()) {
            query_settings_.emplace(
                std::move(key),
                QuerySettingsField{std::move(value), static_cast<uint64_t>(QuerySettingsField::Flags::CUSTOM)});
        }
    };

    emplace_if_absent("enable_json_type", "1");
    emplace_if_absent("output_format_native_write_json_as_string", "1");
    emplace_if_absent("input_format_native_read_json_as_string", "1");
}

}
