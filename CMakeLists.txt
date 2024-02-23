cmake_minimum_required(VERSION 3.25)
project(chemical_preference_system)

set(CMAKE_CXX_STANDARD 17)

add_executable(chemical_preference_system main.cpp
        Libraries/socket-server/SocketServer.cpp
        Libraries/socket-server/SocketServer.h
        Libraries/hardware-control/HardwareControl.cpp
        Libraries/hardware-control/HardwareControl.h
        Libraries/socket-server/Serializer.cpp
        Libraries/socket-server/Serializer.h
        Libraries/hardware-control/enums.h
        Libraries/hardware-control/ValveHandler.cpp
        Libraries/hardware-control/ValveHandler.h
        Libraries/hardware-control/MotorHandler.cpp
        Libraries/hardware-control/MotorHandler.h)

target_link_libraries(chemical_preference_system pigpio)
