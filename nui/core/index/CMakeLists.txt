add_library(
  nui_index
  index.h index.cc
  macro.h macro.cc
)
add_library(nui::index ALIAS nui_index)
target_link_libraries(
  nui_index
  PUBLIC
  fmt::fmt
)

target_include_directories(
  nui_index
  PUBLIC
  ${NUI_ROOT_DIR}
)

add_executable(
  nui_core_index_macro_test
  macro_test.cc
)
target_link_libraries(
  nui_core_index_macro_test
  nui::index
  Catch2::Catch2WithMain
  fmt::fmt
)
catch_discover_tests(
  nui_core_index_macro_test
)
