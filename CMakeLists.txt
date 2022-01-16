cmake_minimum_required(VERSION 3.5)

set(CMAKE_C_STANDARD 99)

project(gbcifx C)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

#FLAVOUR is the platform variant - currently only PI or LINUX
if (NOT DEFINED FLAVOUR)
    message(STATUS "GB: No -DFLAVOUR=\"blah\" was provided we will default to [LINUX]")
    set(FLAVOUR "LINUX")
elseif (FLAVOUR STREQUAL "PI")
    set(FLAVOUR "PI")
else ()
    message(STATUS "GB: We could not match the FLAVOUR you provided. We will default to [LINUX]")
    set(FLAVOUR "LINUX")
endif ()


add_compile_definitions(GB_APP_LINUX)


#Enables debug logging overall
add_compile_definitions(ENABLE_LOGGING=1)

#Sets the debug log level
#LOG_LVL_FATAL = 0
#LOG_LVL_ERROR = 1
#LOG_LVL_WARNING =  2
#LOG_LVL_INFO = 3
#LOG_LVL_DEBUG = 4
#LOG_LVL_TRACE = 5

add_compile_definitions(LOG_LEVEL=5)


#Enables user messages (standard messages that describe what is going on in GBEM output to console, log, syslog etc.)
add_compile_definitions(GBCIFX_UM_EN=1)


#Enables general gbnetx debig logging (general logging statements in key places)
add_compile_definitions(GBCIFX_GEN_LOG_EN=1)




find_package(BCM2835)

if (BCM2835_FOUND)
    message (STATUS "BCM2835 found")
else()
    message (STATUS "BCM2835 NOT found")
endif()

include_directories(${BCM2835_INCLUDE_DIRS} ${gbnetx_config_BINARY_DIR})


set(SOURCE_FILES main.c User/app.c SystemPackets/SystemPackets.c User/TKitUser_Custom.c Source/netX5x_hboot.c Source/netX5xx_hboot.c Source/netX90_netX4x00.c Source/cifXDownload.c Source/cifXEndianess.c Source/cifXFunctions.c Source/cifXHWFunctions.c Source/cifXInit.c Source/cifXInterrupt.c Source/Hilmd5.c SerialDPM/SerialDPMInterface.c OSAbstraction/OS_Custom.c OSAbstraction/OS_SPICustom.c EtherCAT/Src/PacketHandlerECS.c EtherCAT/Src/EventHandlerECS.c)

add_definitions(-DCIFX_TOOLKIT_HWIF=1)

include_directories(Source)
include_directories(SerialDPM)
include_directories(OSAbstraction)
include_directories(Common/cifXAPI)
include_directories(Common/HilscherDefinitions)
include_directories(SystemPackets)
include_directories(EtherCAT/Inc/EtherCAT)
include_directories(User)

add_executable(gbcifx ${SOURCE_FILES})

add_subdirectory("gclibs/logging")
add_subdirectory("gclibs/gberror")
add_subdirectory("gclibs/common-misc")
add_subdirectory("gclibs/linux-shm")
add_subdirectory("gclibs/pid")
add_subdirectory("gclibs/dpm")
add_subdirectory("libs/gbcifx_config")


target_link_libraries(gbcifx Logging gbcifx_config m rt ${BCM2835_LIBRARIES})



MESSAGE(STATUS "GB: [TARGET_GBCIFX_LINUX] is being used")
if (FLAVOUR STREQUAL "PI")
    MESSAGE(STATUS "GB: Loading [gbcifx_defs_pi.cmake]")
    include(cmake/gbcifx_defs_pi.cmake)
    if (EXISTS cmake/gbcifx_custom_defs_pi.cmake)
        MESSAGE(STATUS "GB: Loading [gbcifx_custom_defs_pi.cmake]")
        include(cmake/gbcifx_custom_defs_pi.cmake)
    else ()
        MESSAGE(STATUS "GB: [gbcifx_custom_def_pi.cmake] does NOT exist (no overrides for standard definitions will be used)")
    endif ()
else ()
    MESSAGE(STATUS "GB: Loading [gbcifx_defs_linux.cmake]")
    include(cmake/gbcifx_defs_linux.cmake)
    if (EXISTS cmake/gbcifx_custom_defs_linux.cmake)
        MESSAGE(STATUS "GB: Loading [gbcifx_custom_defs_linux.cmake]")
        include(cmake/gbcifx_custom_defs_linux.cmake)
    else ()
        MESSAGE(STATUS "GB: gbcifx_custom_defs_linux.cmake does NOT exist (no overrides for standard definitions will be used)")
    endif ()

endif ()
configure_file(cmake/gbcifx_config_autogen.h.in libs/gbcifx_config/gbcifx_config_autogen.h)
