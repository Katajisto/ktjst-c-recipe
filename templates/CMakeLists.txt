cmake_minimum_required(VERSION 3.21)

project({{ .Variables.PROJECT_NAME }} C)

set(CMAKE_C_STANDARD {{ .Variables.C_STANDARD}})
set(CMAKE_C_STANDARD_REQUIRED ON)

# Base includes for the project.
include_directories(
  include
  {{if .Variables.INCLUDE_LIBS | has "ktjst"}}vendor/ktjst{{end}}
)
file(GLOB_RECURSE SOURCES
  "src/*.c"
  {{if .Variables.INCLUDE_LIBS | has "ktjst"}}"vendor/ktjst/*.c"{{end}}
)


add_executable(${PROJECT_NAME} ${SOURCES})
# link math
target_link_libraries(${PROJECT_NAME} m)

{{if .Variables.INCLUDE_LIBS | has "raylib"}}
add_subdirectory("./vendor/raylib" raylib EXCLUDE_FROM_ALL)
target_link_libraries(${PROJECT_NAME} raylib)
{{end}}
