#pragma once

#include <cctype>
#include <string>
#include <vector>

#if __has_include("esphome/core/component.h")
#include "esphome/core/component.h"
#define SPEAKER_GROUP_HELPERS_HAS_COMPONENT 1
#endif

namespace esphome {
namespace speaker_group {

inline void trim_chars(std::string &value, const std::string &chars) {
  while (!value.empty() && chars.find(value.front()) != std::string::npos) {
    value.erase(0, 1);
  }
  while (!value.empty() && chars.find(value.back()) != std::string::npos) {
    value.pop_back();
  }
}

inline std::string to_lower_ascii(std::string value) {
  for (char &c : value) {
    c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
  }
  return value;
}

inline std::vector<std::string> parse_group_members(std::string raw) {
  trim_chars(raw, "[]'\" ");
  std::string lowered = to_lower_ascii(raw);
  if (raw.empty() || lowered == "none" || lowered == "unknown" || lowered == "unavailable") {
    return {};
  }

  std::vector<std::string> members;
  size_t start = 0;
  size_t end = std::string::npos;
  while ((end = raw.find(',', start)) != std::string::npos) {
    std::string token = raw.substr(start, end - start);
    trim_chars(token, "'\" ");
    if (!token.empty()) {
      members.push_back(token);
    }
    start = end + 1;
  }

  if (start < raw.size()) {
    std::string token = raw.substr(start);
    trim_chars(token, "'\" ");
    if (!token.empty()) {
      members.push_back(token);
    }
  }

  return members;
}

}  // namespace speaker_group

namespace speaker_group_helpers {

#ifdef SPEAKER_GROUP_HELPERS_HAS_COMPONENT
class SpeakerGroupHelpers : public Component {
 public:
  void trim_chars(std::string &value, const std::string &chars) { speaker_group::trim_chars(value, chars); }

  std::string to_lower_ascii(std::string value) { return speaker_group::to_lower_ascii(value); }

  std::vector<std::string> parse_group_members(std::string raw) { return speaker_group::parse_group_members(raw); }
};
#endif

}  // namespace speaker_group_helpers
}  // namespace esphome
