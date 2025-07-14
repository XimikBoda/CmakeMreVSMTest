cmake_minimum_required (VERSION 3.10)

set(FOLDER_NAME "run")

if(WIN32)
   add_subdirectory(run_in_MoDis)
endif()