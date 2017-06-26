//
// Created by whiMaggot on 2017/6/14.
//
#include <jni.h>
#ifndef FFMPEGTEST_FFMPEG_INFO_H
#define FFMPEGTEST_FFMPEG_INFO_H
#endif //FFMPEGTEST_FFMPEG_INFO_H

extern "C" jstring Java_com_whimaggot_os_ffmpegtest_FFmpegInfoActivity_urlprotocolinfo(JNIEnv *jniEnv,jobject);
extern "C" jstring Java_com_whimaggot_os_ffmpegtest_FFmpegInfoActivity_avformatinfo(JNIEnv *jniEnv,jobject);
extern "C" jstring Java_com_whimaggot_os_ffmpegtest_FFmpegInfoActivity_avcodecinfo(JNIEnv *jniEnv,jobject);
extern "C" jstring Java_com_whimaggot_os_ffmpegtest_FFmpegInfoActivity_avfilterinfo(JNIEnv *jniEnv,jobject);
extern "C" jstring Java_com_whimaggot_os_ffmpegtest_FFmpegInfoActivity_configurationinfo(JNIEnv *jniEnv,jobject);