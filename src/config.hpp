#pragma once

#include <filesystem>
#include <memory>

#include <toml++/toml.hpp>

namespace config {
// TODO сделать импорт из симейка
constexpr auto APP_NAME         = "tsend";
constexpr auto CONFIG_FILE_NAME = "config.toml";

enum RunState { CLI, TUI };

struct config {
  std::string token;
  std::string chat_id;
  RunState    state;
};

std::unique_ptr<config const> init();

std::unique_ptr<std::filesystem::path const> getConfigFilePath();

std::unique_ptr<toml::table const> readConfig();

void createConfigFile();
} // namespace config
