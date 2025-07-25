cmake_minimum_required (VERSION 3.10)

set(TARGET_NAME "mreapi")

add_library(${TARGET_NAME} STATIC "null.cpp")

set_target_properties(${TARGET_NAME} PROPERTIES FOLDER ${FOLDER_NAME})

target_include_directories(${TARGET_NAME} PUBLIC "${MRE_SDK}/include")

if(${CMAKE_SYSTEM_NAME} STREQUAL Generic) # For Phone
    target_link_libraries(${TARGET_NAME} -L"${MRE_SDK}"/lib/MRE30/armgcc/)

    target_link_libraries(${TARGET_NAME} 
        -l:percommon.a -l:pertcp.a -l:persensor.a -l:persmsper.a -l:perbitstream.a -l:percontact.a -l:permms.a 
        -l:persmsmng.a -l:peraudio.a -l:percallout.a -l:percam.a -l:perfile.a -l:perhttp.a -l:persim.a -l:perrecord.a 
        -l:persmssp.a -l:perlbs.a -l:perpro.a -l:pervideo.a -l:perxml.a -l:persec.a -l:persysstorage.a -l:perpayment.a 
        -l:perbt.a -l:perpn.a -l:perudp.a -l:persysfile.a -l:persso.a )
elseif(WIN32) # For MoDis
    target_link_libraries(${TARGET_NAME} ${MRE_SDK}/lib/mrewin32.lib)
else()
    message(FATAL_ERROR "Wrong target system")
endif()