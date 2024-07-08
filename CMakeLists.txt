cmake_minimum_required(VERSION 3.20)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

file(GLOB src_code CONFIGURE_DEPENDS "include/*.h" "src/*.cpp" "include/*/*.h" "src/*/*.cpp")

project(ValheimRelay)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME}
        ${src_code}
        src/config.cpp
        include/config.h
)

set_target_properties(${PROJECT_NAME} PROPERTIES LINK_SEARCH_START_STATIC 1)
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_SEARCH_END_STATIC 1)

set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

target_link_libraries(${PROJECT_NAME} libdpp.a)

target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
