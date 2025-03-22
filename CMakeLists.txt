cmake_minimum_required(VERSION 3.10)
project(MiniMayhem VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable warnings
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Find SFML
find_package(SFML 2.6.1 COMPONENTS system window graphics audio network REQUIRED)

# Collect source files
file(GLOB_RECURSE SOURCES 
    "src/*.cpp"
    "src/core/*.cpp"
    "src/entities/*.cpp"
    "src/server/*.cpp"
    "src/physics/*.cpp"
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link SFML
target_link_libraries(${PROJECT_NAME} PRIVATE
    sfml-system
    sfml-window
    sfml-graphics
    sfml-audio
    sfml-network
)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core
    ${CMAKE_CURRENT_SOURCE_DIR}/src/entities
    ${CMAKE_CURRENT_SOURCE_DIR}/src/physics
    ${CMAKE_CURRENT_SOURCE_DIR}/src/server
)

# Copy assets to build directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    ${CMAKE_BINARY_DIR}/assets
)

# Install rules
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)
install(DIRECTORY assets/
    DESTINATION bin/assets
) 