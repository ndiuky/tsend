#pragma once

#include <optional>
#include <string_view>

#include "httplib.h"

namespace telegram {
// TODO вынести в конфиг

enum ParseMod { MARKDOWN, MARKDOWN_V2, HTML };

enum FileType { FILE, VIDEO, PHOTO };

void init(httplib::Client client);

void sendMessage(std::string_view text, ParseMod format);

void sendFile(
  std::string_view                text,
  FileType                        sendType,
  std::optional<std::string_view> caption
);
} // namespace telegram
