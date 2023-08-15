# Module: nui::indexing
#
# Provides ability to define custom indices,
# iterate over them, and convert between them quickly.

add_library(
  nui_indexing
  indexing.h indexing.cc
  macro.h macro.cc
  conversion.h conversion.cc
)
add_library(nui::indexing ALIAS nui_indexing)
target_link_libraries(
  nui_indexing
  PUBLIC
  nui::basics
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
  Catch2::Catch2WithMain
  nui::indexing
)
catch_discover_tests(
  nui_core_indexing_macro_test
)

add_executable(
  nui_core_indexing_conversion_test
  conversion_test.cc
)
target_link_libraries(
  nui_core_indexing_conversion_test
  Catch2::Catch2WithMain
  nui::indexing
  nui::basics
)
catch_discover_tests(
  nui_core_indexing_conversion_test
)
