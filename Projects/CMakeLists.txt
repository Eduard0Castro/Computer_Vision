cmake_minimum_required(VERSION 3.5)
project( Projects )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

file(GLOB SOURCE_FILES "src/C++/*.cpp"
                        "src/C++/*.hpp")


 
add_executable(${PROJECT_NAME} ${SOURCE_FILES}) 
target_link_libraries( Projects ${OpenCV_LIBS} )
