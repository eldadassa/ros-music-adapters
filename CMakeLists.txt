cmake_minimum_required(VERSION 2.8)

project(ros-music-adapter)

# add modules for finding JSONCPP, ZMQ and MUSIC
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)
# generates catkin_INCLUDE_DIRS and catkin_LIBRARIES for all components

find_package(catkin REQUIRED
    COMPONENTS
    roscpp
    roscpp_serialization
    rosconsole
    rostime
)

find_package(MUSIC REQUIRED)
find_package(JSONCPP REQUIRED)
find_package(MPI REQUIRED)
find_package(ZMQ REQUIRED)
find_package(MUSICADAPTER REQUIRED)
 
catkin_package(
    CATKIN_DEPENDS
        roscpp
        roscpp_serialization
        rosconsole
        rostime
    DEPENDS
        MUSIC
        MPI
        JSONCPP
)

include_directories(
    include
    ${MUSIC_INCLUDE_DIRS}
    ${JSONCPP_INCLUDE_DIRS}
    ${MPI_INCLUDE_PATH}
    ${ZMQ_INCLUDE_DIRS}
    ${MUSICADAPTER_INCLUDE_DIRS}
    ${catkin_INCLUDE_DIRS}
)



set(CMAKE_CXX_COMPILE_FLAGS ${CMAKE_CXX_COMPILE_FLAGS} ${MPI_COMPILE_FLAGS})
set(CMAKE_CXX_LINK_FLAGS ${CMAKE_CXX_LINK_FLAGS} ${MPI_LINK_FLAGS})
set(CMAKE_CXX_FLAGS "-O3 -g -Wall")

find_library(GSL gsl REQUIRED)
find_library(BLAS gslcblas REQUIRED)
find_library(PTHREAD pthread REQUIRED)

add_library(rosmusicadapter SHARED base/ROSInPort.cpp)
include_directories(base/)


# Adapters
add_executable(ros_cont_adapter ros-adapters/ROSContAdapter.cpp)

target_link_libraries(ros_cont_adapter rosmusicadapter ${catkin_LIBRARIES} ${MUSICADAPTER_LIBRARIES} ${ZMQ_LIBRARIES} ${MUSIC_LIBRARIES} ${PTHREAD} ${MPI_LIBRARIES} ${JSONCPP_LIBRARY})


# INSTALL

install(TARGETS
    ros_cont_adapter
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib 
)

install(FILES
    base/ROSInPort.h
    DESTINATION include 
)




################################################################################
##################              Enable testing                ##################
################################################################################
enable_testing()
add_test(NAME TestZMQ WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/test_zmq_adapter COMMAND test.sh)
