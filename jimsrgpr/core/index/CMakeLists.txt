add_library(
  jimsrgpr_index
  index.h index.cc
  macro.h macro.cc
)
add_library(jimsrgpr::index ALIAS jimsrgpr_index)
target_link_libraries(
  jimsrgpr_index
  PUBLIC
  fmt::fmt
)

target_include_directories(
  jimsrgpr_index
  PUBLIC
  ${JIMSRGPR_ROOT_DIR}
)

add_executable(
  jimsrgpr_core_index_macro_test
  macro_test.cc
)
target_link_libraries(
  jimsrgpr_core_index_macro_test
  jimsrgpr::index
  Catch2::Catch2WithMain
  fmt::fmt
)
catch_discover_tests(
  jimsrgpr_core_index_macro_test
)
