
include_directories("..")

# Boost json parser relies on boost spirit, which needs a define to be thread
# safe.
add_definitions(-DBOOST_SPIRIT_THREADSAFE)

IF (NOT MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
ENDIF (NOT MSVC)
IF (APPLE)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
ENDIF (APPLE)

if(CMAKE_SYSTEM_NAME STREQUAL Windows)
    # We support down to Windows XP
    add_definitions(-DWINVER=0x0502 -D_WIN32_WINNT=0x0502)

    # Path to Windows Sockets
    find_library(WINSOCK_LIBRARY NAMES ws2_32 DOC "Path to WinSock library (WS2_32.lib)")
    if( NOT WINSOCK_LIBRARY STREQUAL "WINSOCK_LIBRARY-NOTFOUND" )
        mark_as_advanced(WINSOCK_LIBRARY)
    endif()

    # Path to mswsock
    find_library(MSWSOCK_LIBRARY NAMES mswsock DOC "Path to other winsock library? (mswsock.dll)")
        if( NOT MSWSOCK_LIBRARY STREQUAL "MSWSOCK_LIBRARY-NOTFOUND" )
        mark_as_advanced(MSWSOCK_LIBRARY)
    endif()

    find_library(LIPHLAPI_LIBRARY NAMES IPHLPAPI DOC "Path to IPHLPAPI library (liphlpapi)")
    if( NOT LIPHLAPI_LIBRARY STREQUAL "LIPHLAPI_LIBRARY-NOTFOUND" )
        mark_as_advanced(LIPHLAPI_LIBRARY)
    endif()

    # PTHREADS
    SET(PTHREADS_INCLUDE_DIR  "" CACHE PATH "Path to pthread includes (Optional).")
    SET(PTHREADS_LIBRARY_DIR  "" CACHE PATH "Path to pthread library (Optional).")

    # MINGW
    if(MINGW)
        add_definitions(-DMINGW32_LIMITED_ERRC)
    endif(MINGW)

    if(MSVC)
        # Asio uses a lot of deprecated functions internall
        add_definitions(-D_WINSOCK_DEPRECATED_NO_WARNINGS)
        
        # Static linking against runtime
        option(USE_MSVC_STATIC_RUNTIME "Use MSVC static runtime switch /MT" OFF)
        if( USE_MSVC_STATIC_RUNTIME )
            foreach(flag_var
                    CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG
                    CMAKE_CXX_FLAGS_RELEASE
                    CMAKE_CXX_FLAGS_MINSIZEREL
                    CMAKE_CXX_FLAGS_RELWITHDEBINFO
                )
                if(${flag_var} MATCHES "/MD")
                    string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
                endif(${flag_var} MATCHES "/MD")
            endforeach(flag_var)
        endif( USE_MSVC_STATIC_RUNTIME )
    endif()
endif()

# Boost asio SSL depends on OpenSSL
find_package(OpenSSL REQUIRED)

# Boost library
set(Boost_USE_MULTITHREADING "ON")
set(Boost_USE_STATIC_LIBS "ON")
if( BOOST_ROOT OR Boost_INCLUDE_DIR )
    set(Boost_NO_SYSTEM_PATHS "ON")
else()
    set(Boost_NO_SYSTEM_PATHS "OFF")
endif()

#Link zlib from manual built source (if you use distro package)
if (WIN32)
    option(USE_SYSTEM_ZLIB "Use the system provided zlib" OFF)
else(WIN32)
    option(USE_SYSTEM_ZLIB "Use the system provided zlib" ON)
endif()

if(USE_SYSTEM_ZLIB)
    set(BOOST_ZLIB_NAME)
    find_package(ZLIB)
else(USE_SYSTEM_ZLIB)
    set(BOOST_ZLIB_NAME zlib)
endif(USE_SYSTEM_ZLIB)

find_package(Boost 1.50 REQUIRED
    chrono
    date_time
    filesystem
    iostreams
    locale
    regex
    random
    system
    thread
    unit_test_framework
    program_options
    ${BOOST_ZLIB_NAME}
    )

######### Include some directories ##########
include_directories(${OPENSSL_INCLUDE_DIR})
include_directories(SYSTEM ${Boost_INCLUDE_DIRS})

add_subdirectory(utils)
add_subdirectory(http)
add_subdirectory(api)
add_subdirectory(uploader)
