aux_source_directory(. SRC_LIST)                     # 将指定目录下的源文件放入变量SRC_LIST中
aux_source_directory(../src/server/db DB_LIST)
add_executable(test ${SRC_LIST} ${DB_LIST})               # 指定生成可执行文件

# 指定可执行文件需要依赖的库
target_link_libraries(test mymuduo pthread mysqlclient hiredis)