cmake_minimum_required(VERSION 3.2)

project(ProciusEngine)

file(GLOB SOURCES src/*.cpp)
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${SOURCES})

#add_subdirectory(vendor/SDL)

target_include_directories(${PROJECT_NAME}
    PUBLIC vendor/SDL/include
    PUBLIC include
)

target_link_directories(${PROJECT_NAME}
    PUBLIC vendor/SDL/lib/mac
    PUBLIC vendor/SDL/lib/win
)

target_link_libraries(${PROJECT_NAME} 
    ${SDL2_LIBRARIES}  
)