
cmake_minimum_required( VERSION 2.8 )
project( Moonlight-Company-Maze-Solver )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

find_package( OpenCV REQUIRED )

## Include headers
include_directories( include )

## Sources
set(serial_SRCS
    src/serial.cc
    include/serial/serial.h
    include/serial/v8stdint.h
)

if(APPLE)
	# If OSX
	list(APPEND serial_SRCS src/impl/unix.cc)
	list(APPEND serial_SRCS src/impl/list_ports/list_ports_osx.cc)
elseif(UNIX)
    # If unix
    list(APPEND serial_SRCS src/impl/unix.cc)
    list(APPEND serial_SRCS src/impl/list_ports/list_ports_linux.cc)
else()
    # If windows
    list(APPEND serial_SRCS src/impl/win.cc)
    list(APPEND serial_SRCS src/impl/list_ports/list_ports_win.cc)
endif()

## Add serial library
add_library(serial ${serial_SRCS})
if(UNIX AND NOT APPLE)
    target_link_libraries(serial rt)
endif()

## Build your executable
add_executable( 
	mazeSolver
	"main.cpp"
	"src/CCHandler.cpp"
	"src/IPHandler.cpp"
	"src/PSMHandler.cpp"
	"src/LMHandler.cpp"
	"src/RPHandler.cpp"
	"src/DDHandler.cpp" ##
	"src/CUHandler.cpp"
	"src/CHandler.cpp"
	"src/Visualizer.cpp"
	)

## Link your executable against the library
target_link_libraries( 
	mazeSolver
	serial
	${OpenCV_LIBS}
	)