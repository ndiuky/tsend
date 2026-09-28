#include <cstdlib>
#include <format>
#include <stdexcept>

#include "config.hpp"
#include "httplib.h"
#include "static.hpp"

int main(int argc, char *argv[]) {
  auto const cfg    = config::init();
  auto const prefix = std::format("{}{}", "/bot", cfg->token);

  httplib::Client cli(std::string{ telegram::API_HOST });

  auto res = cli.Get(prefix + "/getMe");
  if (!res || res->status != 200) {
    throw new std::runtime_error("bot token is invalid");
  }

  std::vector<std::string> all_args(argv, argv + argc);

  for (auto const &arg : all_args) {
    auto const msg = std::format(
      R"({{
          "chat_id": {},
          "text": "{}",
        }})",
      cfg->chat_id,
      arg
    );

    res = cli.Post(prefix + "/sendMessage", msg, "application/json");
  }

  return EXIT_SUCCESS;
}
