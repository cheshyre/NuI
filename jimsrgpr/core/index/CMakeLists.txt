add_library(
  jimsrgpr_index
  index.h index.cc
  macro.h macro.cc
)
add_library(jimsrgpr::index ALIAS jimsrgpr_index)
target_link_libraries(
  jimsrgpr_index
)

target_include_directories(
  jimsrgpr_index
  PUBLIC
  ${JIMSRGPR_ROOT_DIR}
)