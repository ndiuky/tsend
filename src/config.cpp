#include "config.hpp"

#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <stdexcept>

#include <toml++/impl/parser.hpp>
#include <toml++/impl/table.hpp>
#include <toml++/toml.hpp>

namespace config {
auto init() -> std::unique_ptr<config const> {
  auto cfg               = std::make_unique<config>();
  cfg->state             = RunState::CLI;

  auto const cfgFilePath = getConfigFilePath();

  if (!std::filesystem::exists(*cfgFilePath)) {
    // TODO добавить создание фалйа и промт юзера для ввода токена
    std::filesystem::create_directories(cfgFilePath->parent_path());

    throw std::runtime_error("config file not found");
  };

  auto const cfgFile   = readConfig();

  auto const BOT_TOKEN = (*cfgFile)["token"].value<std::string>();
  auto const CHAT_ID   = (*cfgFile)["chat_id"].value<std::string>();

  if (!BOT_TOKEN || !CHAT_ID) {
    // TODO: вызвать tui визард
    throw std::runtime_error("config file not valid");
  }

  cfg->token   = *BOT_TOKEN;
  cfg->chat_id = *CHAT_ID;

  return cfg;
}

auto readConfig() -> std::unique_ptr<toml::table const> {
  auto const path = getConfigFilePath();

  try {
    auto config = std::make_unique<toml::table const>(
      toml::parse_file(path->string())
    );

    return config;
  } catch (toml::parse_error const &err) {
    std::cerr << "Error parsing file '" << err.source().path << "':\n"
              << err.description() << "\n (" << err.source().begin << ")\n";
    return nullptr;
  }
}

auto getConfigFilePath() -> std::unique_ptr<std::filesystem::path const> {
  auto const path_target = std::filesystem::path(APP_NAME) / CONFIG_FILE_NAME;

#ifdef _WIN32
  char const *appdata = std::getenv("APPDATA");

  if (!appdata) { throw std::runtime_error("APPDATA is not set"); };

  auto path = std::make_unique<std::filesystem::path const>(
    fs::path(appdata) / path_target
  );

  return path;

#elif defined(__APPLE__)
  char const *home = std::getenv("HOME");

  if (!home) { throw std::runtime_error("HOME is not set"); };

  auto path = std::make_unique<std::filesystem::path const>(
    fs::path(home) / "Library" / "Application Support" / path_target
  );

  return path;

#else
  if (char const *xdg = std::getenv("XDG_CONFIG_HOME")) {
    auto path = std::make_unique<std::filesystem::path const>(
      std::filesystem::path(xdg) / path_target
    );

    return path;
  }

  char const *home = std::getenv("HOME");

  if (!home) { throw std::runtime_error("HOME is not set"); };

  auto path = std::make_unique<std::filesystem::path const>(
    std::filesystem::path(home) / ".config" / path_target
  );

  return path;
#endif
}
}; // namespace config
