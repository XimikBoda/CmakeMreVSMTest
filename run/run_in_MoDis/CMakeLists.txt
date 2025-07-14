cmake_minimum_required (VERSION 3.10)

set(NAME "in_MoDis")

set(TARGET_NAME "${FOLDER_NAME}_${NAME}")
set(TARGET_ALIAS "${FOLDER_NAME}::${NAME}")

add_custom_command( # repack triger 
   OUTPUT null.cpp
   COMMAND ${CMAKE_COMMAND} -E touch null.cpp
   DEPENDS vxp vsm
)

add_library(${TARGET_NAME} STATIC "null.cpp")
add_library(${TARGET_ALIAS} ALIAS ${TARGET_NAME})

set_target_properties(${TARGET_NAME} PROPERTIES FOLDER ${FOLDER_NAME})

set_target_properties(${TARGET_NAME} PROPERTIES SUFFIX ".bat")
set_target_properties(${TARGET_NAME} PROPERTIES PREFIX "")

set(MODIS_PATH "${MRE_SDK}/models/Model01_QVGA_MRE3.0/")

add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "$<TARGET_FILE:vxp>" "${MODIS_PATH}/WIN32FS/DRIVE_E/mre/${APP_NAME}.vc.vxp"
   COMMAND ${CMAKE_COMMAND} -E copy "$<TARGET_FILE:vsm>" "${MODIS_PATH}/WIN32FS/DRIVE_E/mre/${LIB_NAME}.dlm"
   COMMAND echo "${MODIS_PATH}/MoDIS/Release/MoDIS.exe" > "$<TARGET_FILE:${TARGET_NAME}>" 
)