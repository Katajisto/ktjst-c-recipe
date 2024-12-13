cmake_minimum_required(VERSION 3.21)

project({{ .Variables.PROJECT_NAME }} C)

set(CMAKE_C_STANDARD {{ .Variables.C_STANDARD}})
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Base includes for the project.
include_directories(
  include
  {{if .Variables.INCLUDE_LIBS | has "ktjst"}}vendor/ktjst{{end}}
  {{if .Variables.INCLUDE_LIBS | has "microui"}}vendor/microui{{end}}
)
file(GLOB_RECURSE SOURCES
  "src/*.c"
  {{if .Variables.INCLUDE_LIBS | has "ktjst"}}"vendor/ktjst/*.c"{{end}}
  {{if .Variables.INCLUDE_LIBS | has "microui"}}"vendor/microui/*.c"{{end}}
)


add_executable(${PROJECT_NAME} ${SOURCES})
# link math
target_link_libraries(${PROJECT_NAME} m)

{{if .Variables.INCLUDE_LIBS | has "raylib"}}
add_subdirectory("./vendor/raylib" raylib EXCLUDE_FROM_ALL)
target_link_libraries(${PROJECT_NAME} raylib)
{{end}}

if(CMAKE_BUILD_TYPE MATCHES Debug)
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -O0 -Wall -Wextra")
endif()

if(CMAKE_BUILD_TYPE MATCHES Release)
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3 -DNDEBUG")
endif()

