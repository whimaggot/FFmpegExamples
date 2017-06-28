//
// Created by whiMaggot on 2017/6/27.
//

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "ffmpeg_tool.h"

extern "C" jint Java_com_whimaggot_os_ffmpegtest_FFmpegToolsActivity_spiltYUV420(JNIEnv *jniEnv,jobject obj,jstring inputUrl,jint w,jint h,jint num){
    const char *url = jniEnv->GetStringUTFChars(inputUrl, NULL);
    FILE *fp = fopen(url,"rb+");
    FILE *fp_y = fopen("/sdcard/output_420_y.yuv","wb+");
    FILE *fp_u = fopen("/sdcard/output_420_u.yuv","wb+");
    FILE *fp_v = fopen("/sdcard/output_420_v.yuv","wb+");

    unsigned char *pic = (unsigned char *) malloc(w * h * 3 / 2);

    for(int i=0;i<num;i++){
        fread(pic,1,w*h*3/2,fp);
        fwrite(pic,1,w*h,fp_y);
        fwrite(pic+w*h,1,w*h/4,fp_u);
        fwrite(pic+w*h*5/4,1,w*h/4,fp_v);
    }
    free(pic);
    fclose(fp);
    fclose(fp_y);
    fclose(fp_u);
    fclose(fp_v);
    return 0;
}

extern "C" jint Java_com_whimaggot_os_ffmpegtest_FFmpegToolsActivity_spiltYUV444(JNIEnv *jniEnv,jobject obj,jstring inputUrl,jint w,jint h,jint num){
    const char *url = jniEnv->GetStringUTFChars(inputUrl,NULL);
    FILE *fp = fopen(url,"rb+");
    FILE *fp_y = fopen("/sdcard/output_444_y.yuv","wb+");
    FILE *fp_u = fopen("/sdcard/output_444_u.yuv","wb+");
    FILE *fp_v = fopen("/sdcard/output_444_v.yuv","wb+");

    unsigned char *pic = (unsigned char *) malloc(w * h * 3);

    for(int i=0;i<num;i++){
        fread(pic,1,w*h*3,fp);
        fwrite(pic,1,w*h,fp_y);
        fwrite(pic+w*h,1,w*h,fp_u);
        fwrite(pic+w*h*2,1,w*h,fp_v);
    }
    free(pic);
    fclose(fp);
    fclose(fp_y);
    fclose(fp_u);
    fclose(fp_v);

    return 0;

}

extern "C" jint Java_com_whimaggot_os_ffmpegtest_FFmpegToolsActivity_YUV420Gray(JNIEnv *jniEnv,jobject obj,jstring inputUrl,jint w,jint h,jint num){
    const char *url = jniEnv->GetStringUTFChars(inputUrl,NULL);

    FILE *fp = fopen(url,"rb+");
    FILE *op = fopen("/sdcard/output_420_gray.yuv","wb+");

    unsigned char *pic = (unsigned char *) malloc(w * h * 3 / 2);

    for(int i=0;i<num;i++){
        fread(pic,1,w*h*3/2,fp);
        memset(pic+w*h,128,w*h/2);
        fwrite(pic,1,w*h*3/2,op);
    }
    free(pic);
    fclose(fp);
    fclose(op);

    return 0;
}

extern "C" jint  Java_com_whimaggot_os_ffmpegtest_FFmpegToolsActivity_YUV420HalfY(JNIEnv *jniEnv,jobject obj,jstring inputUrl,jint w,jint h,jint num){
    const  char *url = jniEnv->GetStringUTFChars(inputUrl,NULL);
    FILE *fp = fopen(url,"rb+");
    FILE *op = fopen("/sdcard/output_420_halfY.yuv","wb+");

    unsigned char *pic = (unsigned char *) malloc(w * h * 3 / 2);

    for(int i=0;i<num;i++){
        fread(pic,1,w*h*3/2,fp);
        for(int j=0;j<w*h;j++){
            unsigned char temp = pic[j]/2;
            pic[j] = temp;
        }
        fwrite(pic,1,w*h*3/2,op);
    }
    free(pic);
    fclose(fp);
    fclose(op);

    return 0;
}



