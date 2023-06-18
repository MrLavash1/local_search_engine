# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\lib_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\lib_autogen.dir\\ParseCache.txt"
  "CMakeFiles\\localSearchEngine_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\localSearchEngine_autogen.dir\\ParseCache.txt"
  "lib_autogen"
  "localSearchEngine_autogen"
  )
endif()
