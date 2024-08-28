project(EnetServerTest LANGUAGES CXX)

file(GLOB INCLUDE_FILES
    *.h
    **/*.h
    **/**/*.h
    **/**/**/*.h
    **/**/**/**/*.h)

file(GLOB SOURCE_FILES
    *.cpp
    **/*.cpp
    **/**/*.cpp
    **/**/**/*.cpp
    **/**/**/**/*.cpp)

add_executable(${PROJECT_NAME}
    ${INCLUDE_FILES}
    ${SOURCE_FILES}
)

if (MSVC)
    add_definitions(/EHsc)
else ()
    add_definitions(-fexceptions)
endif ()

if (CONAN_EXPORTED)
    include(${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
else ()
    include(${CMAKE_CURRENT_SOURCE_DIR}/conan.cmake)
    conan_cmake_configure(REQUIRES
            fmt/10.2.1
            spdlog/1.14.1
        GENERATORS CMakeDeps CMakeToolchain
        IMPORTS "bin, *.dll -> ./bin"
        OPTIONS
            fmt/*:shared=True
            spdlog/*:shared=True)

    conan_cmake_autodetect(settings)
    conan_cmake_install(PATH_OR_REFERENCE .
        BUILD missing
        REMOTE conancenter
        SETTINGS ${settings})
endif ()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_BINARY_DIR}")

find_package(fmt REQUIRED)
if (fmt_FOUND)
    message(STATUS "Found fmt: ${fmt_VERSION}, at ${fmt_INCLUDE_DIRS}, ${fmt_LIBRARIES}")
    target_link_libraries(${PROJECT_NAME} PUBLIC fmt::fmt)
    target_include_directories(${PROJECT_NAME} PUBLIC ${fmt_INCLUDE_DIRS})
else ()
    message(FATAL_ERROR "Could not find fmt")
endif ()

find_package(spdlog REQUIRED)
if (spdlog_FOUND)
    message(STATUS "Found spdlog: ${spdlog_VERSION}, at ${spdlog_INCLUDE_DIRS}, ${spdlog_LIBRARIES}")
    target_link_libraries(${PROJECT_NAME} PUBLIC spdlog::spdlog)
    target_include_directories(${PROJECT_NAME} PUBLIC ${fmt_INCLUDE_DIRS})
else ()
    message(FATAL_ERROR "Could not find spdlog")
endif ()

set_target_properties(${PROJECT_NAME} PROPERTIES
    C_STANDARD 11
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED ON
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
    NOMINMAX
    WIN32_LEAN_AND_MEAN
    # CPPHTTPLIB_OPENSSL_SUPPORT
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../vendor/enet/include
    # ${CMAKE_CURRENT_SOURCE_DIR}/../vendor/httplib
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    enet
)
