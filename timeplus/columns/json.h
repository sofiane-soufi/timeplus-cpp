#pragma once

#include "column.h"
#include "string.h"

#include <cstdint>
#include <string_view>

namespace timeplus {

/**
 * Represents column of JSON documents.
 * Leverages the same underlying wire format as strings until
 * native JSON serialization support is available server-side.
 */
class ColumnJson : public Column {
public:
    using ValueType = std::string_view;

    ColumnJson();
    explicit ColumnJson(ColumnRef data);

    /// Appends one element to the end of column.
    void Append(std::string_view value);
    void Append(std::string&& value);

    /// Returns element at given row number.
    std::string_view At(size_t n) const;

    inline std::string_view operator[](size_t n) const { return At(n); }

    void Reserve(size_t new_cap) override;
    void Append(ColumnRef column) override;
    bool LoadPrefix(InputStream* input, size_t rows) override;
    bool LoadBody(InputStream* input, size_t rows) override;
    void SavePrefix(OutputStream* output) override;
    void SaveBody(OutputStream* output) override;
    void Clear() override;
    size_t Size() const override;
    ColumnRef Slice(size_t begin, size_t len) const override;
    ColumnRef CloneEmpty() const override;
    void Swap(Column& other) override;
    ItemView GetItem(size_t index) const override;

private:
    std::shared_ptr<ColumnString> data_;
    uint64_t serialization_version_;
};

} // namespace timeplus
