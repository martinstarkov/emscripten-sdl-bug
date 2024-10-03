cmake_minimum_required(VERSION 3.21)

project(EmscriptenDemo)

add_executable(main src/main.cpp)

if (EMSCRIPTEN)
    set(SHELL_HTML_FILE "../emscripten/shell.html")
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    set(ECXXFLAGS "-O3 -std=c++17 -Werror --use-port=sdl2")
    set_target_properties(main PROPERTIES LINK_FLAGS "${ECXXFLAGS} --shell-file ${SHELL_HTML_FILE} -s FULL_ES3=1 -s ALLOW_MEMORY_GROWTH=1 -s WARN_ON_UNDEFINED_SYMBOLS=1 -s NO_EXIT_RUNTIME=1 -s AGGRESSIVE_VARIABLE_ELIMINATION=1")
    set_target_properties(main PROPERTIES COMPILE_FLAGS "${ECXXFLAGS}")
    set_target_properties(main PROPERTIES OUTPUT_NAME "index")
endif()