cmake_minimum_required(VERSION 2.8)

# Uncomment for debug output
#add_definitions(-DOUTPUT_DEBUG)

add_subdirectory(error)

# For convenience
set(MFAPI_APP_ID "" CACHE STRING "The app ID assigned to you by MediaFire. Can be left blank if MFAPI_OVERRIDE_APP_ID is defined in the build environment.")
if ( NOT "${MFAPI_APP_ID}" STREQUAL "" )
    add_definitions(-DMFAPI_APP_ID="${MFAPI_APP_ID}")
endif( NOT "${MFAPI_APP_ID}" STREQUAL "" )

set(MFAPI_APP_KEY "" CACHE STRING "The app key assigned to you by MediaFire. Can be left blank if MFAPI_OVERRIDE_APP_KEY is defined in the build environment.")
if ( NOT "${MFAPI_APP_KEY}" STREQUAL "" )
    add_definitions(-DMFAPI_APP_KEY="${MFAPI_APP_KEY}")
endif( NOT "${MFAPI_APP_KEY}" STREQUAL "" )

# -- API by path ---------------
project (mf_api_sdk CXX)

set(API_SOURCES
    detail/session_maintainer_locker.cpp
    detail/session_token_api_base_static.cpp
    detail/tokenless_api_base_static.cpp

    # Non template generated APIs
    user/get_login_token.cpp
    user/get_session_token.cpp
    user/renew_session_token.cpp

    app_constants.cpp
    connection_state.cpp
    credentials.cpp
    error.cpp
    ptree_helpers.cpp
    response_base.cpp
    session_maintainer.cpp
    session_state.cpp
    type_helpers.cpp
)
set(API_HEADERS
    detail/api_base.hpp
    detail/request_interface.hpp
    detail/requester_impl.hpp
    detail/session_maintainer_locker.hpp
    detail/session_maintainer_request.hpp
    detail/session_token_api_base_static.hpp
    detail/tokenless_api_base_static.hpp

    # Non template generated APIs
    user/get_login_token.hpp
    user/get_session_token.hpp
    user/renew_session_token.hpp

    app_constants.hpp
    connection_state.hpp
    credentials.hpp
    error.hpp
    ptree_helpers.hpp
    requester.hpp
    response_base.hpp
    session_maintainer.hpp
    session_state.hpp
    session_token_api_base.hpp
    tokenless_api_base.hpp
    types.hpp
    type_helpers.hpp
)
set(GENERATED_API_DIRECTORIES
    billing
    contact
    device
    file
    folder
    notifications
    system
    templates
    upload
    user
)
foreach( dir ${GENERATED_API_DIRECTORIES} )
    file(GLOB_RECURSE contained_files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${dir}/*.hpp)
    set(GENERATED_API_HEADERS ${GENERATED_API_HEADERS} ${contained_files})
endforeach()
set(FULL_API_HEADERS
    ${API_HEADERS}
    ${GENERATED_API_HEADERS}
)
foreach( file ${FULL_API_HEADERS} )
    get_filename_component( dir ${file} DIRECTORY )
    install(FILES ${file} DESTINATION include/mediafire_sdk/api/${dir} )
endforeach()

include(GeneratedList.txt)

add_library(mf_api_sdk STATIC
    ${API_HEADERS}
    ${API_SOURCES}
    ${API_TEMPLATE_GENERATED_SOURCES}
    ${API_TEMPLATE_GENERATED_HEADERS}
    $<TARGET_OBJECTS:api_error>
)
install(TARGETS mf_api_sdk DESTINATION lib)

TARGET_LINK_LIBRARIES(mf_api_sdk
    ${MFAPI_APP_CONSTANTS_LIBRARY}
    mf_sdk_utils
    mf_http_sdk
)

add_subdirectory(unit_tests)
