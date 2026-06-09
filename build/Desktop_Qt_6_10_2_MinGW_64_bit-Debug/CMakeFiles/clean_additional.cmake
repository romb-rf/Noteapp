# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\NoteApp_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\NoteApp_autogen.dir\\ParseCache.txt"
  "CMakeFiles\\notecore_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\notecore_autogen.dir\\ParseCache.txt"
  "NoteApp_autogen"
  "notecore_autogen"
  "tests\\CMakeFiles\\test_noteapp_autogen.dir\\AutogenUsed.txt"
  "tests\\CMakeFiles\\test_noteapp_autogen.dir\\ParseCache.txt"
  "tests\\test_noteapp_autogen"
  )
endif()
