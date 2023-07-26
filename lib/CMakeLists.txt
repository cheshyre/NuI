add_subdirectory(Catch2)
add_subdirectory(fmt)
set(SPDLOG_FMT_EXTERNAL ON CACHE BOOL "Force spdlog to use external fmt" FORCE)
add_subdirectory(spdlog)
