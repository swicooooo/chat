aux_source_directory(. SRC_LIST)                     # 将指定目录下的源文件放入变量SRC_LIST中
aux_source_directory(./db DB_LIST)
aux_source_directory(./model MODEL_LIST)

add_executable(chatServer ${SRC_LIST} ${DB_LIST} ${MODEL_LIST})               # 指定生成可执行文件

target_link_libraries(chatServer mymuduo pthread mysqlclient hiredis tcmalloc)    # 指定可执行文件需要依赖的库