# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/Editor_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/Editor_autogen.dir/ParseCache.txt"
  "Editor_autogen"
  )
endif()
