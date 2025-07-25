cmake_minimum_required (VERSION 3.10)

set(FOLDER_NAME "vsm")

add_subdirectory(resourses)
add_subdirectory(main)


set(TARGET_NAME "vsm")
set(TARGET_ALIAS "${FOLDER_NAME}::${TARGET_NAME}")

add_custom_command( # repack triger 
   OUTPUT null.cpp
   COMMAND ${CMAKE_COMMAND} -E touch null.cpp
   DEPENDS vsm::main vsm::resourses
)

add_library(${TARGET_NAME} STATIC "null.cpp")
add_library(${TARGET_ALIAS} ALIAS ${TARGET_NAME})

set_target_properties(${TARGET_NAME} PROPERTIES FOLDER ${FOLDER_NAME})

set_target_properties(${TARGET_NAME} PROPERTIES OUTPUT_NAME "${LIB_NAME}")
set_target_properties(${TARGET_NAME} PROPERTIES PREFIX "")

if(${CMAKE_SYSTEM_NAME} STREQUAL Generic) # For Phone
   set_target_properties(${TARGET_NAME} PROPERTIES SUFFIX ".vsm")
elseif(WIN32) # For MoDis
   set_target_properties(${TARGET_NAME} PROPERTIES SUFFIX ".dlm")
else()
    message(FATAL_ERROR "Wrong target system")
endif()

add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
   COMMAND "${TinyMRESDK}/bin/PackApp" 
               -a "$<TARGET_FILE:vsm::main>" 
               -r "$<TARGET_FILE:vsm::resourses>" 
               -o "$<TARGET_FILE:${TARGET_NAME}>" 
               -tr "${RAM}" 
               -tn "${LIB_NAME}"
               -tdn "${DEVELOPER_NAME}"
               -ti "${IMSI}"
               -tapi "${API}"
               -ty "vsm"
)
