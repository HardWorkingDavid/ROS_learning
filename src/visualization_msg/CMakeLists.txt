cmake_minimum_required(VERSION 3.0.2)
project(visualization_msg)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  visualization_msgs
)

catkin_package(CATKIN_DEPENDS roscpp visualization_msgs)

include_directories(include
  ${catkin_INCLUDE_DIRS}
)

add_executable(shapes src/shapes.cpp)
target_link_libraries(shapes
   ${catkin_LIBRARIES}
)
add_executable(points_lines src/points_lines.cpp)
target_link_libraries(points_lines
   ${catkin_LIBRARIES}
)

#############
## Install ##
#############


install(TARGETS shapes points_lines
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION}
)

