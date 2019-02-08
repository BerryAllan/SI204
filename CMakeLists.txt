# CMakeList.txt : CMake project for SI204, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.

# TODO: Add tests and install targets if needed.

#projects
add_executable(PROJ01P1 PROJECTS/PROJ01/readppm.cpp)
add_executable(PROJ01P2 PROJECTS/PROJ01/gray.cpp)
add_executable(PROJ01P3 PROJECTS/PROJ01/green.cpp)
add_executable(PROJ01P4 PROJECTS/PROJ01/shift.cpp)

#labs
add_executable(LAB01 LABS/LAB01/lab01.cpp)

add_executable(LAB02P1 LABS/LAB02/lab02p1.cpp)
add_executable(LAB02P2 LABS/LAB02/lab02p2.cpp)
add_executable(LAB02P3 LABS/LAB02/lab02p3.cpp)

add_executable(LAB03P1 LABS/LAB03/part1.cpp)
add_executable(LAB03P2 LABS/LAB03/part2.cpp)

add_executable(LAB04P1 LABS/LAB04/part1.cpp)
add_executable(LAB04P2 LABS/LAB04/part2.cpp)
add_executable(LAB04P3 LABS/LAB04/part3.cpp)

add_executable(LAB05P1 LABS/LAB05/p1.cpp)
add_executable(LAB05P2 LABS/LAB05/p2.cpp)
add_executable(LAB05P3 LABS/LAB05/p3.cpp)


#homeworks
add_executable(HW03 HWS/HW03/hw.cpp)
add_executable(HW04 HWS/HW04/hw.cpp)
add_executable(HW05 HWS/HW05/hw.cpp)
add_executable(HW06 HWS/HW06/hw.cpp)
add_executable(HW08 HWS/HW08/hw.cpp)
add_executable(HW09 HWS/HW09/hw.cpp)
add_executable(HW11 HWS/HW12/hw.cpp)
