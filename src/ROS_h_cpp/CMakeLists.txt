cmake_minimum_required(VERSION 3.0.2)
project(ROS_h_cpp)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
)

## 声明C++库
add_library(david
            include/david.h
            src/david.cpp)   
add_dependencies(david ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(david ${catkin_LIBRARIES})

catkin_package()

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)


add_executable(use_david src/use_david.cpp)
add_dependencies(use_david ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(use_david
                      david
                      ${catkin_LIBRARIES})