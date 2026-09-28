set(_libs)
set(BUILD_STATIC_LIBS ON)

# --- OpenSSL ---
find_package(OpenSSL REQUIRED)
list(APPEND _libs OpenSSL::SSL OpenSSL::Crypto)

# --- toml++ ---
add_subdirectory(tomlplusplus)
list(APPEND _libs tomlplusplus)

# --- httplib ---
add_subdirectory(httplib)
list(APPEND _libs httplib)

# --- tui ---
add_subdirectory(cpp-tui)
list(APPEND _libs cpptui::cpptui)

# --- target ---
add_library(tb_libs INTERFACE)
add_library(tb::libs ALIAS tb_libs)
target_link_libraries(tb_libs INTERFACE ${_libs})

message(STATUS "Libraries:")
foreach(lib IN LISTS _libs)
	message(STATUS "-> ${lib}")
endforeach()

unset(_libs)
