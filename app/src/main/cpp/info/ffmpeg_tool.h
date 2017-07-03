//
// Created by whiMaggot on 2017/6/27.
//

#include <jni.h>

#ifndef FFMPEGTEST_FFMPEG_TOOL_H
#define FFMPEGTEST_FFMPEG_TOOL_H

#endif //FFMPEGTEST_FFMPEG_TOOL_H

#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, "ffmpeg-decode", __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, "ffmpeg-decode", __VA_ARGS__)


extern "C" jint Java_com_whimaggot_os_ffmpegtest_FFmpegToolsActivity_spiltYUV420(JNIEnv *jniEnv,jobject obj,jstring inputUrl,jint w,jint h,jint num);
extern "C" jint Java_com_whimaggot_os_ffmpegtest_FFmpegToolsActivity_spiltYUV444(JNIEnv *jniEnv,jobject obj,jstring inputUrl,jint w,jint h,jint num);
extern "C" jint Java_com_whimaggot_os_ffmpegtest_FFmpegToolsActivity_yuv420Gray(JNIEnv *jniEnv,jobject obj,jstring inputUrl,jint w,jint h,jint num);
extern "C" jint Java_com_whimaggot_os_ffmpegtest_FFmpegToolsActivity_yuv420HalfY(JNIEnv *jniEnv,jobject obj,jstring inputUrl,jint w,jint h,jint num);
extern "C" jint Java_com_whimaggot_os_ffmpegtest_FFmpegToolsActivity_yuv420GrayBar(JNIEnv *jniEnv,jobject obj,jint w,jint h,jint yMin,jint yMax,jint barNum,jstring url);
extern "C" jint Java_com_whimaggot_os_ffmpegtest_FFmpegToolsActivity_spiltPCM16(JNIEnv *jniEnv,jobject obj,jstring inputUrl);

