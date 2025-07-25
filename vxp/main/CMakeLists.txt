cmake_minimum_required (VERSION 3.10)

set(NAME "main")

set(TARGET_NAME "${FOLDER_NAME}_${NAME}")
set(TARGET_ALIAS "${FOLDER_NAME}::${NAME}")

set(COMMON_SOURCES
    main.cpp
)

if(${CMAKE_SYSTEM_NAME} STREQUAL Generic) # For Phone
    add_executable (${TARGET_NAME} ${COMMON_SOURCES} "${PROJECT_SOURCE_DIR}/common/core/gccmain.c")
    add_executable(${TARGET_ALIAS} ALIAS ${TARGET_NAME})

    target_link_libraries(${TARGET_NAME} "-T${PROJECT_SOURCE_DIR}/common/core/scat.ld")
    
    set_target_properties(${TARGET_NAME} PROPERTIES SUFFIX ".axf")
elseif(WIN32) # For MoDis
    add_library(${TARGET_NAME} SHARED ${COMMON_SOURCES} "${PROJECT_SOURCE_DIR}/common/core/dll.def")
    add_library(${TARGET_ALIAS} ALIAS ${TARGET_NAME})
else()
    message(FATAL_ERROR "Wrong target system")
endif()

target_link_libraries(${TARGET_NAME} mreapi)

set_target_properties(${TARGET_NAME} PROPERTIES FOLDER ${FOLDER_NAME})
