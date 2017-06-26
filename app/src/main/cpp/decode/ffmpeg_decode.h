//
// Created by whiMaggot on 2017/6/19.
//
#include <jni.h>

#ifndef FFMPEGTEST_FFMPEG_DECODE_H
#define FFMPEGTEST_FFMPEG_DECODE_H
#endif //FFMPEGTEST_FFMPEG_DECODE_H
extern "C" jint Java_com_whimaggot_os_ffmpegtest_FFmpegDecodeActivity_decode(JNIEnv *jniEnv, jobject,jstring j_input_str,jstring j_output_str);
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, "ffmpeg-decode", __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, "ffmpeg-decode", __VA_ARGS__)

extern "C" void custom_log(void *ptr,int level,const char *fmt,va_list vl);
extern "C" jint Java_com_whimaggot_os_ffmpegtest_FFmpegRtmpActivity_rtmp(JNIEnv *jniEnv,jobject,jstring j_input_str,jstring j_output_str);
extern "C" jboolean Java_com_whimaggot_os_ffmpegtest_FFmpegRtmpActivity_pause(JNIEnv *jniEnv,jobject obj,jboolean data);
extern "C" jboolean Java_com_whimaggot_os_ffmpegtest_FFmpegRtmpActivity_isPlay(JNIEnv *jniEnv,jobject obj);