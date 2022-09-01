link_compile_commands()

file(GLOB_RECURSE SOURCE_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE HEADER_FILES "${CMAKE_SOURCE_DIR}/src/*.hpp")

add_executable(${EXE_NAME} ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(${EXE_NAME} PRIVATE "${CMAKE_BINARY_DIR}/project_config/include")

find_package(fmt CONFIG REQUIRED)
target_link_libraries(${EXE_NAME} PRIVATE fmt::fmt)


find_package(raylib CONFIG REQUIRED)
target_link_libraries(${EXE_NAME} PRIVATE raylib)


enable_sanitizers(${EXE_NAME})
set_target_warnings(${EXE_NAME})
