cmake_minimum_required(VERSION 3.25)
project(chemical_preference_system)

set(CMAKE_CXX_STANDARD 17)

add_executable(chemical_preference_system main.cpp
        Libraries/socket-server/SocketServer.cpp
        Libraries/socket-server/SocketServer.h
        Libraries/hardware-control/HardwareControl.cpp
        Libraries/hardware-control/HardwareControl.h)
