cmake_minimum_required (VERSION 3.10)

set(NAME "resourses")

set(TARGET_NAME "${FOLDER_NAME}_${NAME}")
set(TARGET_ALIAS "${FOLDER_NAME}::${NAME}")

set(RESOURSES_FILES
      demo.png
      demo.txt
)

add_custom_command( # repack triger 
   OUTPUT null.cpp
   COMMAND ${CMAKE_COMMAND} -E touch null.cpp
   DEPENDS ${RESOURSES_FILES}
)

add_library(${TARGET_NAME} STATIC "null.cpp")
add_library(${TARGET_ALIAS} ALIAS ${TARGET_NAME})

set_target_properties(${TARGET_NAME} PROPERTIES FOLDER ${FOLDER_NAME})

set_target_properties(${TARGET_NAME} PROPERTIES SUFFIX ".res")
set_target_properties(${TARGET_NAME} PROPERTIES PREFIX "")

add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
   WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
   COMMAND "${TinyMRESDK}/bin/PackRes" 
               -o "$<TARGET_FILE:${TARGET_NAME}>"
               -f ${RESOURSES_FILES}
               --empty-logo
)