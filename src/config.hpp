#pragma once

#include <filesystem>
#include <memory>

#include <toml++/toml.hpp>

namespace config {
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
