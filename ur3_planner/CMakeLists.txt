cmake_minimum_required(VERSION 3.0.2)
project(ur3_planner)

find_package(catkin REQUIRED COMPONENTS
  rospy
  std_msgs
)

catkin_package(
  CATKIN_DEPENDS rospy std_msgs
)

install(PROGRAMS
  src/basic.py
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
