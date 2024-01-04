# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/ColourSpaceTransformation_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/ColourSpaceTransformation_autogen.dir/ParseCache.txt"
  "ColourSpaceTransformation_autogen"
  )
endif()
