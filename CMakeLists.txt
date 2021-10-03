cmake_minimum_required(VERSION 2.8)

project(hello-webgpu)

# Note: until the debug/release linker flags are split -Wno-unused-command-line-argument is required
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wno-nonportable-include-path -Wno-unused-command-line-argument -fno-exceptions -fno-rtti")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g3 -D_DEBUG=1 -Wno-unused -O0")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -g0 -DNDEBUG=1 -flto -O3")

file(GLOB sources src/*.cpp)
file(GLOB_RECURSE headers src/*.h)

if (EMSCRIPTEN)
	file(GLOB_RECURSE platform_sources src/ems/*.cpp)
	set(CMAKE_EXECUTABLE_SUFFIX ".html")
	
	# TODO: all the debug flags are link only
	#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -s DEMANGLE_SUPPORT=1 -s SAFE_HEAP=1 -s STACK_OVERFLOW_CHECK=2")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -s DISABLE_EXCEPTION_CATCHING=1 --closure 1")

	set(CMAKE_EXE_LINKER_FLAGS "-s ASSERTIONS=0 -s EVAL_CTORS=1 -s WASM=1 -s USE_WEBGPU=1 -s NO_EXIT_RUNTIME=1 -s STRICT=1 --shell-file ${CMAKE_CURRENT_LIST_DIR}/src/ems/shell.html")

	# Linker flags to optimize for smallest output code size
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s ENVIRONMENT=web -s MINIMAL_RUNTIME=2 -s TEXTDECODER=2 -s ABORTING_MALLOC=0 -s ALLOW_MEMORY_GROWTH=0 -s SUPPORT_ERRNO=0 -s MALLOC=emmalloc -s NO_FILESYSTEM=1 --output_eol=linux")
elseif (WIN32)
	file(GLOB_RECURSE platform_sources src/win/*)
elseif (APPLE)
	file(GLOB_RECURSE platform_sources src/mac/*)
endif()

add_executable(hello-webgpu ${sources} ${platform_sources} ${headers})

target_include_directories(hello-webgpu PRIVATE "${CMAKE_CURRENT_LIST_DIR}/inc")
