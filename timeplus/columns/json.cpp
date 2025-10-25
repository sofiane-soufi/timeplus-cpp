#include "json.h"

namespace timeplus {

ColumnJson::ColumnJson()
    : Column(Type::CreateJson())
    , data_(std::make_shared<ColumnString>()) {}

ColumnJson::ColumnJson(ColumnRef data)
    : Column(Type::CreateJson())
    , data_(data->AsStrict<ColumnString>()) {}

void ColumnJson::Append(std::string_view value) {
    data_->Append(value);
}

void ColumnJson::Append(std::string&& value) {
    data_->Append(std::move(value));
}

std::string_view ColumnJson::At(size_t n) const {
    return data_->At(n);
}

void ColumnJson::Reserve(size_t new_cap) {
    data_->Reserve(new_cap);
}

void ColumnJson::Append(ColumnRef column) {
    if (auto col = column->As<ColumnJson>()) {
        data_->Append(col->data_);
    } else if (auto col_string = column->As<ColumnString>()) {
        data_->Append(col_string);
    }
}

bool ColumnJson::LoadBody(InputStream* input, size_t rows) {
    return data_->LoadBody(input, rows);
}

void ColumnJson::SaveBody(OutputStream* output) {
    data_->SaveBody(output);
}

void ColumnJson::Clear() {
    data_->Clear();
}

size_t ColumnJson::Size() const {
    return data_->Size();
}

ColumnRef ColumnJson::Slice(size_t begin, size_t len) const {
    return std::make_shared<ColumnJson>(data_->Slice(begin, len));
}

ColumnRef ColumnJson::CloneEmpty() const {
    return std::make_shared<ColumnJson>();
}

void ColumnJson::Swap(Column& other) {
    auto& col = dynamic_cast<ColumnJson&>(other);
    data_.swap(col.data_);
}

ItemView ColumnJson::GetItem(size_t index) const {
    return ItemView{Type::Json, data_->At(index)};
}

} // namespace timeplus
