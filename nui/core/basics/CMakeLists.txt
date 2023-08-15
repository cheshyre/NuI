# Module: nui::basics
#
# Exports interfaces from the STL and external libraries
# that many modules will need.

add_library(
  nui_basics
  basics.h basics.cc
  version.h version.cc
  vector_tricks.h vector_tricks.cc
)
add_library(nui::basics ALIAS nui_basics)
target_link_libraries(
  nui_basics
  PUBLIC
  fmt::fmt
)
target_include_directories(
  nui_basics
  PUBLIC
  ${NUI_ROOT_DIR}
)

# This is a good target for PCH, but we will delay this for now
# target_precompile_headers(
# nui_basics
# PRIVATE
# basics.h
# )
