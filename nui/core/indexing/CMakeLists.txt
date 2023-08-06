# Module: nui::indexing
#
# Provides ability to define custom indices,
# iterate over them, and convert between them quickly.

add_library(
  nui_indexing
  indexing.h indexing.cc
  macro.h macro.cc
)
add_library(nui::indexing ALIAS nui_indexing)
target_link_libraries(
  nui_indexing
  PUBLIC
  fmt::fmt
)
target_include_directories(
  nui_indexing
  PUBLIC
  ${NUI_ROOT_DIR}
)

add_executable(
  nui_core_indexing_macro_test
  macro_test.cc
)
target_link_libraries(
  nui_core_indexing_macro_test
  nui::indexing
  Catch2::Catch2WithMain
  fmt::fmt
)
catch_discover_tests(
  nui_core_indexing_macro_test
)
