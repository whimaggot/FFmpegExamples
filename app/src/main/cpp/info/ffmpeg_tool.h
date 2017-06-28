//
// Created by whiMaggot on 2017/6/27.
//

#include <jni.h>

#ifndef FFMPEGTEST_FFMPEG_TOOL_H
#define FFMPEGTEST_FFMPEG_TOOL_H

#endif //FFMPEGTEST_FFMPEG_TOOL_H

extern "C" jint Java_com_whimaggot_os_ffmpegtest_FFmpegToolsActivity_spiltYUV420(JNIEnv *jniEnv,jobject obj,jstring inputUrl,jint w,jint h,jint num);
extern "C" jint Java_com_whimaggot_os_ffmpegtest_FFmpegToolsActivity_spiltYUV444(JNIEnv *jniEnv,jobject obj,jstring inputUrl,jint w,jint h,jint num);
extern "C" jint Java_com_whimaggot_os_ffmpegtest_FFmpegToolsActivity_YUV420Gray(JNIEnv *jniEnv,jobject obj,jstring inputUrl,jint w,jint h,jint num);
extern "C" jint  Java_com_whimaggot_os_ffmpegtest_FFmpegToolsActivity_YUV420HalfY(JNIEnv *jniEnv,jobject obj,jstring inputUrl,jint w,jint h,jint num);


