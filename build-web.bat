@echo off
rem Builds the Emscripten implementation (on Windows)
rem TODO: CMake...
rem 

set COMPUTE=false

if "%~1"=="/d" (
  set DEBUG=true
  if "%~2"=="/c" (
    set COMPUTE=true
  )
) else (
  set DEBUG=false
  if "%~1"=="/c" (
    set COMPUTE=true
  )
)

set CPP_FLAGS=-std=c++11 -Wall -Wextra -Werror -Wno-nonportable-include-path -fno-exceptions -fno-rtti -Wno-missing-field-initializers -Wno-unused-function
set EMS_FLAGS=-s ENVIRONMENT=web -s WASM=1 -s USE_WEBGPU=1 -s NO_EXIT_RUNTIME=1 -s STRICT=1 --shell-file src/ems/shell.html
set OPT_FLAGS=

if %DEBUG%==true (
  set CPP_FLAGS=%CPP_FLAGS% -g3 -D_DEBUG=1 -Wno-unused
  set EMS_FLAGS=%EMS_FLAGS% -s ASSERTIONS=2 -s DEMANGLE_SUPPORT=1 -s SAFE_HEAP=1 -s STACK_OVERFLOW_CHECK=2
  set OPT_FLAGS=%OPT_FLAGS% -O0
) else (
  set CPP_FLAGS=%CPP_FLAGS% -g0 -DNDEBUG=1 -flto
  set EMS_FLAGS=%EMS_FLAGS% -s ASSERTIONS=0 -s DISABLE_EXCEPTION_CATCHING=1 -s EVAL_CTORS=1 --closure 1
  set OPT_FLAGS=%OPT_FLAGS% -O3
)

if %COMPUTE%==true (
  set CPP_FLAGS=%CPP_FLAGS% -DHELLO_COMPUTE
)

set SRC=
for %%f in (src/ems/*.cpp) do call set SRC=%%SRC%%src/ems/%%f 
for %%f in (src/*.cpp) do call set SRC=%%SRC%%src/%%f 

set INC=-Iinc

set OUT=out/web/index
if not exist out\web mkdir out\web

rem Grab the Binaryen path from the ".emscripten" file (which needs to have
rem been set). We then swap the Unix-style slashes.
rem 
for /f "tokens=*" %%t in ('em-config BINARYEN_ROOT') do (set BINARYEN_ROOT=%%t)
set "BINARYEN_ROOT=%BINARYEN_ROOT:/=\%"

cmd /c "emcc %CPP_FLAGS% %OPT_FLAGS% %EMS_FLAGS% %INC% %SRC% -o %OUT%.html"
set EMCC_ERR=%errorlevel%
if %DEBUG%==false (
  if %EMCC_ERR%==0 (
    cmd /c "%BINARYEN_ROOT%\bin\wasm-opt %OPT_FLAGS% --converge %OUT%.wasm -o %OUT%.wasm"
    set EMCC_ERR=%errorlevel%
  )
)

if %EMCC_ERR%==0 (
  echo Success!
)
exit /b %EMCC_ERR%
