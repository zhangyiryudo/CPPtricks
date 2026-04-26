#include <iostream>
#include <string_view>
#include <vector>
#include <charconv> // Required for std::from_chars
using namespace std;

struct FIXField {
    int tag;
    std::string_view value;
};

std::vector<FIXField> parse_fix_string_view(std::string_view message) {
    std::vector<FIXField> fields;
    size_t pos = 0;

    while (pos < message.size()) {
        size_t equals_pos = message.find('=', pos);
        if (equals_pos == std::string_view::npos) break;

        #if 0
            // --- THE ORIGINAL PART ---
            int tag = std::stoi(std::string(message.substr(pos, equals_pos - pos)));
        #else 
            // --- THE OPTIMIZED PART ---
            int tag = 0;
            // std::from_chars takes a pointer range [first, last)
            auto [ptr, ec] = std::from_chars(message.data() + pos, message.data() + equals_pos, tag);
            if (ec != std::errc()) {
                cerr << "Error parsing tag: " << std::make_error_code(ec).message() << endl;
                break; // Exit the loop on error
            }
        #endif

        pos = equals_pos + 1;
        size_t soh_pos = message.find('\001', pos);
        if (soh_pos == std::string_view::npos) break;

        std::string_view value = message.substr(pos, soh_pos - pos);
        fields.push_back({tag, value});
        pos = soh_pos + 1;
    }
    return fields;
}

void printParsedFIXFields()
{
    std::string_view message = "8=FIX.4.2\0019=100\00135=D\00149=SENDER\00156=RECEIVER\00134=1\00152=20230101-12:00:00\001";
    auto fields = parse_fix_string_view(message);
    for (const auto& field : fields) {
        cout << "Tag: " << field.tag << ", Value: " << field.value << endl;
    }
}