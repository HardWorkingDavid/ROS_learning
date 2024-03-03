cmake_minimum_required(VERSION 3.0.2)
project(pub_sub)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  message_generation
)
add_message_files(FILES Person.msg)
generate_messages(DEPENDENCIES std_msgs)

catkin_package(
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)




add_executable(talker src/talker.cpp)
target_link_libraries(talker ${catkin_LIBRARIES})
#add_dependencies(talker pub_sub_generate_messages_cpp)

add_executable(listener src/listener.cpp)
target_link_libraries(listener ${catkin_LIBRARIES})
#add_dependencies(listener pub_sub_generate_messages_cpp)

add_executable(class_listener src/class_listener.cpp)
target_link_libraries(class_listener ${catkin_LIBRARIES})

add_executable(person_publisher src/person_publisher.cpp)					#运行
target_link_libraries(person_publisher ${catkin_LIBRARIES})					#库连接
add_dependencies(person_publisher ${PROJECT_NAME}_generate_messages_cpp)	#连接依赖，与自定义消息连接
 
add_executable(person_subscriber src/person_subscriber.cpp)
target_link_libraries(person_subscriber ${catkin_LIBRARIES})
add_dependencies(person_subscriber ${PROJECT_NAME}_generate_messages_cpp)