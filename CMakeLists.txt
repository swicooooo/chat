cmake_minimum_required(VERSION 3.0.0)
project(demo)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g)              # 配置编译选项

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)   # 设置可执行文件输出路径

# 配置头文件搜素路径
include_directories(${PROJECT_SOURCE_DIR}/include) 
include_directories(${PROJECT_SOURCE_DIR}/include/server) 
include_directories(${PROJECT_SOURCE_DIR}/include/server/db) 
include_directories(${PROJECT_SOURCE_DIR}/include/server/model) 
# link_directories()    # 配置库文件搜索路径

add_subdirectory(src)   # 指定搜索的子目录
add_subdirectory(test)