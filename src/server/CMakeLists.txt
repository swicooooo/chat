aux_source_directory(. SRC_LIST)                     # 将指定目录下的源文件放入变量SRC_LIST中

add_executable(chatServer ${SRC_LIST})               # 指定生成可执行文件

target_link_libraries(chatServer mymuduo pthread)    # 指定可执行文件需要依赖的库