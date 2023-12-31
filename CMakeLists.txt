
cmake_minimum_required (VERSION 3.22)

project (localSearchEngine VERSION 1.0.1)

set(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Widgets REQUIRED)
qt_standard_project_setup()


configure_file(
        version.h.in
        ${CMAKE_CURRENT_BINARY_DIR}/version.h
)

add_subdirectory(test)

include(FetchContent)
FetchContent_Declare(
        json URL https://github.com/nlohmann/json/releases/download/v3.10.5/json.tar.xz
)
FetchContent_MakeAvailable(
        json
)

set(Headers
        header/ConvertJSON.h
        header/InvertedIndex.h
        header/SearchEngine.h
        )

set(Sources
        src/ConvertJSON.cpp
        src/InvertedIndex.cpp
        src/SearchEngine.cpp
        )

add_library(lib ${Headers} ${Sources})

add_executable (localSearchEngine main.cpp)

if (CMAKE_VERSION VERSION_GREATER 3.23)
    set_property(TARGET localSearchEngine PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
target_link_libraries(lib
        nlohmann_json::nlohmann_json
        Qt6::Widgets
        Qt6::Core)

target_link_libraries(localSearchEngine lib)
target_include_directories(lib PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(localSearchEngine PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
