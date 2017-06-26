cmake_minimum_required(VERSION 3.4.1)

add_library(
    ffmpeg-info
    SHARED
    ffmpeg_info.cpp)



target_link_libraries(
    ffmpeg-info
    swscale-4
    swresample-2
    postproc-54
    avcodec-57
    avfilter-6
    avformat-57
    avdevice-57
    avutil-55
    ${log-lib})

add_library(
    swscale-4
    SHARED
    IMPORTED)
    set_target_properties(
    swscale-4
    PROPERTIES IMPORTED_LOCATION
    ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libswscale-4.so)

add_library(
    avcodec-57
    SHARED
    IMPORTED)
    set_target_properties(
    avcodec-57
    PROPERTIES IMPORTED_LOCATION
    ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libavcodec-57.so)

add_library(
    avformat-57
    SHARED
    IMPORTED)
    set_target_properties(
    avformat-57
    PROPERTIES IMPORTED_LOCATION
    ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libavformat-57.so)

add_library(
    avdevice-57
    SHARED
    IMPORTED)
    set_target_properties(
    avdevice-57
    PROPERTIES IMPORTED_LOCATION
    ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libavdevice-57.so)

add_library(
    avfilter-6
    SHARED
    IMPORTED)
    set_target_properties(
    avfilter-6
    PROPERTIES IMPORTED_LOCATION
    ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libavfilter-6.so)

add_library(
    avutil-55
    SHARED
    IMPORTED)
    set_target_properties(
    avutil-55
    PROPERTIES IMPORTED_LOCATION
    ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libavutil-55.so)

add_library(
    postproc-54
    SHARED
    IMPORTED)
    set_target_properties(
    postproc-54
    PROPERTIES IMPORTED_LOCATION
    ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libpostproc-54.so)

add_library(
    swresample-2
    SHARED
    IMPORTED)
    set_target_properties(
    swresample-2
    PROPERTIES IMPORTED_LOCATION
    ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libswresample-2.so)
