cmake_minimum_required (VERSION 3.10)

set(FOLDER_NAME "vxp")

add_subdirectory(resourses)
add_subdirectory(main)


set(TARGET_NAME "vxp")
set(TARGET_ALIAS "${FOLDER_NAME}::${TARGET_NAME}")

add_custom_command( # repack triger 
   OUTPUT null.cpp
   COMMAND ${CMAKE_COMMAND} -E touch null.cpp
   DEPENDS vxp::main vxp::resourses
)

add_library(${TARGET_NAME} STATIC "null.cpp")
add_library(${TARGET_ALIAS} ALIAS ${TARGET_NAME})

set_target_properties(${TARGET_NAME} PROPERTIES FOLDER ${FOLDER_NAME})

set_target_properties(${TARGET_NAME} PROPERTIES OUTPUT_NAME "${APP_NAME}")
set_target_properties(${TARGET_NAME} PROPERTIES SUFFIX ".vxp")
set_target_properties(${TARGET_NAME} PROPERTIES PREFIX "")

if(${CMAKE_SYSTEM_NAME} STREQUAL Generic) # For Phone
   set_target_properties(${TARGET_NAME} PROPERTIES SUFFIX ".vxp")
elseif(WIN32) # For MoDis
   set_target_properties(${TARGET_NAME} PROPERTIES SUFFIX ".vc.vxp")
else()
    message(FATAL_ERROR "Wrong target system")
endif()


if(BACKGROUND)
   set(TB 1)
else()
   set(TB 0)
endif()

add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
   COMMAND "${TinyMRESDK}/bin/PackApp" 
               -a "$<TARGET_FILE:vxp::main>" 
               -r "$<TARGET_FILE:vxp::resourses>" 
               -o "$<TARGET_FILE:${TARGET_NAME}>" 
               -tr "${RAM}" 
               -tn "${APP_NAME}"
               -tdn "${DEVELOPER_NAME}"
               -tb "${TB}"
               -ti "${IMSI}"
               -tapi "${API}"
)
