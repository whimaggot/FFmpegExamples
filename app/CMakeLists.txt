cmake_minimum_required(VERSION 3.4.1)

include_directories(src/main/cpp/include)
    find_library(
    log-lib
    log)


ADD_SUBDIRECTORY(./src/main/cpp/info)
ADD_SUBDIRECTORY(./src/main/cpp/decode)



