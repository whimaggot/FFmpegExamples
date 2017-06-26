//
// Created by whiMaggot on 2017/6/26.
//

#include <jni.h>

#ifndef FFMPEGTEST_FFMPEG_CORE_H
#define FFMPEGTEST_FFMPEG_CORE_H

#endif //FFMPEGTEST_FFMPEG_CORE_H

extern "C" jint Java_com_whimaggot_os_ffmpegtest_FFmpegCoreActivity_core(JNIEnv *jniEnv,jobject obj,jint cmdnum,jobjectArray cmdline);

void custom_log(void *ptr,int level, const  char *fmt,va_list vl);
