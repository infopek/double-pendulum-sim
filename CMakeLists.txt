cmake_minimum_required(VERSION 3.0)

add_executable(DoublePendulum "Application.cpp" "Application.h")

target_sources(${PROJECT_NAME}
	PUBLIC
	main.cpp
)

target_link_libraries(DoublePendulum ${CMAKE_SOURCE_DIR}/sfml/lib/sfml-graphics.lib)
target_link_libraries(DoublePendulum ${CMAKE_SOURCE_DIR}/sfml/lib/sfml-audio.lib)
target_link_libraries(DoublePendulum ${CMAKE_SOURCE_DIR}/sfml/lib/sfml-network.lib)
target_link_libraries(DoublePendulum ${CMAKE_SOURCE_DIR}/sfml/lib/sfml-system.lib)
target_link_libraries(DoublePendulum ${CMAKE_SOURCE_DIR}/sfml/lib/sfml-window.lib)

include_directories(${CMAKE_SOURCE_DIR}/sfml/include)

set_property(TARGET DoublePendulum PROPERTY CXX_STANDARD 20)
set_property(TARGET DoublePendulum PROPERTY CXX_STANDARD_REQUIRED ON)	