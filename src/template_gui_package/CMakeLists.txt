# MIT License

# Copyright (c) 2022 Kristopher Krasnosky

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.


cmake_minimum_required(VERSION 3.1.0)

#get_filename_component(PACKAGE_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
#message("Creating Package: ${PACKAGE_NAME}")

project(template_gui_package VERSION 1.0.0 LANGUAGES CXX)  ## this package name is the name of the directory this cmake file is in



################################
##  CONFIGURE THIS FILE HERE  ##
################################

#find_package(Qt5 REQUIRED COMPONENTS Widgets

find_library(GL_LIBRARY NAMES GL PATHS /snap/gnome-3-38-2004/137/usr/lib/x86_64-linux-gnu)

find_package(OpenCV REQUIRED)
find_package(catkin REQUIRED COMPONENTS
  cv_bridge
  image_transport
)
find_package(libfreenect REQUIRED COMPONENTS)

set(ROS_DEPENDS
  roscpp
  std_msgs
  sensor_msgs
  cv_bridge
  image_transport
 # libfreenect
  )

include_directories(
  ${catkin_INCLUDE_DIRS}
  ${LIBFREENECT_INCLUDE_DIRS}
)
find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Core REQUIRED)

set(CMAKE_CXX_FLAGS_COVERAGE "${CMAKE_CXX_FLAGS_RELEASE} -fprofile-arcs -ftest-coverage")

set(RESOURCES res.qrc)
qt5_add_resources(RESOURCE_FILES ${RESOURCES})

set(EXTERNAL_DEPENDS
  Qt5Widgets
  Qt5PrintSupport
  OpenCV
  cv_bridge
  image_transport
  libfreenect
  )

set(EXTERNAL_DEPENDS_LIB
  Qt5::Widgets
  Qt5::PrintSupport
  Qt5::Core
  ${OpenCV_LIBS}
  ${libfreenect_LIBS}
  ${LIBFREENECT_INCLUDE_DIRS}
  )

set(INCLUDE_DIRECTORIES
  ${OpenCV_LIBS}
  ${libfreenect_LIBS}
  ${LIBFREENECT_INCLUDE_DIRS}
  )


##########################################
##  Be Carefull editing below this line ##
##########################################

## Compile as C++14
add_compile_options(-std=c++17)

## need this for qt auto generated headers to include!
set(CMAKE_INCLUDE_CURRENT_DIR ON)

###
###  Add Non ROS dependencies
###

foreach(DEPEND ${EXTERNAL_DEPENDS})
  find_package(${DEPEND} REQUIRED)
endforeach(DEPEND)

###
###  Add any required ros packages here
###
find_package(catkin REQUIRED COMPONENTS ${ROS_DEPENDS})

catkin_package(
  INCLUDE_DIRS
    include
  LIBRARIES
    ${PROJECT_NAME}
  CATKIN_DEPENDS
    ${ROS_DEPENDS}
  DEPENDS
    ${EXTERNAL_DEPENDS}
)

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${INCLUDE_DIRECTORIES}
)
include_directories(
 include
  ${OpenCV_INCLUDE_DIRS}
  ${libfreenect_INCLUDE_DIRS}
)


###########
## Build ##
###########

file(GLOB HDRS
  "include/${PROJECT_NAME}/*.h"
)
file(GLOB SRCS
  "src/*.cpp"
  "src/*.hpp"
)
file(GLOB NODES
  "nodes/*.cpp"
)

###
### QT stuff (required if you want a GUI)
###
set(CMAKE_AUTOMOC ON)  #This will autogenerate qt gui stuff
set(CMAKE_AUTORCC ON)  #this needs to be on so cmake will know what to do with QT resource Files

#find_package(Qt5Widgets)
#find_package(Qt5PrintSupport)
#find all the qt UI stuff
file(GLOB_RECURSE UI
    "include/${PROJECT_NAME}/*.ui"
)

message("Adding ${PROJECT_NAME} UI files: " )
foreach(source ${UI})
    message("  - " ${source})
endforeach(source)

#make them into headers
qt5_wrap_ui (UI_HDRS  ${UI})

message("Generating ${PROJECT_NAME} UI Headers: " )
foreach(source ${UI_HDRS})
    message("  - " ${source})
endforeach(source)

# find all resource files
file(GLOB QRC
    "src/*.qrc"
)

###
### compile
###

message("buliding ${PROJECT_NAME} node: ")
foreach(NODE_FILE ${NODES})
  get_filename_component(NODE_NAME ${NODE_FILE} NAME_WE)
  message("  - " ${NODE_NAME})

  add_executable(${NODE_NAME} ${NODE_FILE} ${HDRS} ${SRCS} ${UI} ${QRC})
  add_dependencies(${NODE_NAME} ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
  target_link_libraries (${NODE_NAME} ${catkin_LIBRARIES} ${OpenCV_LIBRARIES} ${FREENECT_LIBRARIES} ${LIBFREENECT_LIBRARIES} ${EXTERNAL_DEPENDS_LIB})
  target_include_directories(${NODE_NAME} PRIVATE "include/${PROJECT_NAME}/")

  list(APPEND NODE_LIST ${NODE_NAME})

endforeach(NODE_FILE)


install(TARGETS ${NODE_LIST}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

install(DIRECTORY launch/
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/launch
  )

