cmake_minimum_required (VERSION 3.10)

project ("Demo")

set(APP_NAME "Demo")
set(LIB_NAME "DemoLib")
set(DEVELOPER_NAME "YouName")
set(RAM "500" CACHE STRING "Ram requirement (in kb)")
set(IMSI "1234567890" CACHE STRING "Imsi of first SIM-card")
set(API "File SIM card ProMng" CACHE STRING "Api for app")
option(BACKGROUND "App can work background" OFF)

set(MRE_SDK "$ENV{MRE_SDK}" CACHE STRING "MRE SDK dir")
set(TinyMRESDK "$ENV{TinyMRESDK}" CACHE STRING "TinyMRESDK dir")

if(BACKGROUND)
    add_definitions(-DSUPPORT_BG)
endif()

add_definitions(-DLIBNAME="${LIB_NAME}")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory(common)
add_subdirectory(vxp)
add_subdirectory(vsm)
add_subdirectory(run)